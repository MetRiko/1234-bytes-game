#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define Loop(i,m) for(int i=0;i<m;i++)

using namespace std;

struct CLASS_POSITION{int X,Y,DIR;};
#define GET_ID_FROM_POSITION(c,m) c.X+c.Y*m

char ORIGINAL_MAP[]="XJAJBACADAAADACABACADAAADACABGBAAABGBACAAIAACABEAAGAAEFAADADAAJADAAADAJAAIAAJAAACACAAAEHAEAH\
EAAAGAAAJAAIAAJAAAGAAAFJAJBACADAAADACABCAMACDAAAAAGAAAAADEADADAEBAHAAAHABUX";
char CONVERTED_MAP[550],DRAW_MAP[550];//529

int GAME_TIME=1,TEMP_1,REM_POINTS=1,MEMORY_DIR,BONUS_TIME,TIME_TICK;
CLASS_POSITION PLAYER,GHOSTS[5],MEM_POSITION;

float ENGINE_PREV,ENGINE_CURR,ENGINE_LAG;

int DO_MOVE(CLASS_POSITION &o,int d,int a=0)
{
    MEM_POSITION=o;
    if(d==0)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;
    if(a&&(o.X==-1||o.X==23))return 1;
    if(CONVERTED_MAP[GET_ID_FROM_POSITION(o,23)]==-37) {o=MEM_POSITION; return 0;} else return 1;
}

char GET_CHAR_FROM_MAP(CLASS_POSITION c){return CONVERTED_MAP[c.X+c.Y*23];}

int main()
{
    //system("COLOR 08");
    srand(time(0));
        TEMP_1=0;
        Loop(i,167){memset(CONVERTED_MAP+TEMP_1,(i%2?'.':-37),ORIGINAL_MAP[i]-64);TEMP_1+=ORIGINAL_MAP[i]-64;}
        CONVERTED_MAP[70]=42;CONVERTED_MAP[90]=42;CONVERTED_MAP[438]=42;CONVERTED_MAP[458]=42;
        PLAYER={5,5,0};Loop(i,5)GHOSTS[i]={11,11};
        REM_POINTS=237;
    while(1)
    {
        ENGINE_CURR=clock();
        ENGINE_LAG+=ENGINE_CURR-ENGINE_PREV;;
        ENGINE_PREV=ENGINE_CURR;
/// ===================================== LOGIC

        Loop(i,4)if(GetAsyncKeyState(37+i))MEMORY_DIR=i;;

        while(ENGINE_LAG>=0.05)
        {
            ENGINE_LAG-=0.2;
            GAME_TIME++;

            char &TEMP_CHAR=CONVERTED_MAP[GET_ID_FROM_POSITION(PLAYER,23)];
            if(TEMP_CHAR=='.'||TEMP_CHAR=='*'){REM_POINTS--;BONUS_TIME=TEMP_CHAR=='*'?27000:BONUS_TIME;TEMP_CHAR=' ';}
            BONUS_TIME-=BONUS_TIME>0;

            if(GAME_TIME%600==0)if(DO_MOVE(PLAYER,MEMORY_DIR,1))PLAYER.DIR=MEMORY_DIR;else DO_MOVE(PLAYER,PLAYER.DIR,1);
            if(abs(PLAYER.X-11)>11)PLAYER.X=PLAYER.X+1?0:22;

            Loop(i,5)
            {
                if(GET_ID_FROM_POSITION(PLAYER,23)==GET_ID_FROM_POSITION(GHOSTS[i],23))if(BONUS_TIME)GHOSTS[i]={11,11}; else return 0;
                char TEMP_TAB[]="0000",TEMP_2=1;
                while(GAME_TIME%(400*(i+1))==0)
                {
                    TEMP_1=rand()%4;
                    ENGINE_CURR=(TEMP_1+2)%4!=GHOSTS[i].DIR;
                    if((ENGINE_CURR||!TEMP_2)&&DO_MOVE(GHOSTS[i],TEMP_1)){GHOSTS[i].DIR=TEMP_1;break;}
                    if(ENGINE_CURR)TEMP_TAB[TEMP_1]=0;
                    TEMP_1=0;Loop(j,4)TEMP_1+=TEMP_TAB[j];
                    TEMP_2=TEMP_1!='0';
                }
            }
        }
        if(!REM_POINTS)return 0;

/// ===================================== DRAW_MAP

        TEMP_1=(BONUS_TIME?177-(BONUS_TIME>8000):-37);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),COORD{0,0});
        Loop(i,530)DRAW_MAP[i+i/23]=(CONVERTED_MAP[i]==-37?TEMP_1:CONVERTED_MAP[i]);
        Loop(i,23)DRAW_MAP[(i+1)*24-1]='\n';
        DRAW_MAP[GET_ID_FROM_POSITION(PLAYER,24)]='O';
        Loop(i,5)DRAW_MAP[GET_ID_FROM_POSITION(GHOSTS[i],24)]=2-(BONUS_TIME>0);
        cout<<DRAW_MAP;
    }
}

