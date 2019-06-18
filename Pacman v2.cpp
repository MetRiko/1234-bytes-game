#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define Loop(i,m) for(int i=0;i<m;i++)
using namespace std;

//bool CHECK_KEY(int k){return GetAsyncKeyState(k);}
#define CHECK_KEY(k) GetAsyncKeyState(k)

struct CLASS_POSITION{int X,Y,DIR;};
#define GET_ID_FROM_POSITION(c) c.X+c.Y*23

char ORIGINAL_MAP[]="XJAJBACADAAADACABACADAAADACABGBAAABGBACAAIAACABEAAGAAEFAADADAAJADAAADAJAAIAAJAAACACAAAEHAEAH\
EAAAGAAAJAAIAAJAAAGAAAFJAJBACADAAADACABCAMACDAAAAAGAAAAADEADADAEBAHAAAHABUX";//Size=167
char CONVERTED_MAP[550];

int GAME_TIME=1,TEMP_1,REM_POINTS=1,MEMORY_DIR,BONUS_TIME;
CLASS_POSITION PLAYER,GHOSTS[5],MEM_POSITION,TEMP_POSITION;

float ENGINE_PREV,ENGINE_CURR,ENGINE_LAG;

CLASS_POSITION DO_MOVE(CLASS_POSITION &o,int d){if(d==0)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;return o;}

HANDLE CONSOLE_HANDLE=GetStdHandle(STD_OUTPUT_HANDLE);
void SET_COLOR(int c){SetConsoleTextAttribute(CONSOLE_HANDLE,(BONUS_TIME&&c-8?7:c));}

char GET_CHAR_FROM_MAP(CLASS_POSITION c){return CONVERTED_MAP[c.X+c.Y*23];}

int main()
{
    srand(time(0));
    GOTO_START:
        TEMP_1=0;
        Loop(i,167){memset(CONVERTED_MAP+TEMP_1,(i%2?'.':0),ORIGINAL_MAP[i]-64);TEMP_1+=ORIGINAL_MAP[i]-64;}
        CONVERTED_MAP[70]=42;
        CONVERTED_MAP[90]=42;
        CONVERTED_MAP[438]=42;
        CONVERTED_MAP[458]=42;
        PLAYER={5,5,0};Loop(i,5)GHOSTS[i]={11,11};
        BONUS_TIME=0;
        system("cls");
        if(!REM_POINTS)cout<<"\rCONGRATULATIONS!\n";cout<<"\rNEW GAME? [Y/N]";
        while(GAME_TIME)
        {
            if(CHECK_KEY(89))GAME_TIME=0;
            if(CHECK_KEY(78))exit(0);
        }
        ENGINE_PREV=clock();
        REM_POINTS=237;
    while(1)
    {
        ENGINE_CURR=clock();
        ENGINE_LAG+=ENGINE_CURR-ENGINE_PREV;;
        ENGINE_PREV=ENGINE_CURR;
/// ===================================== LOGIC

        Loop(i,4)if(CHECK_KEY(37+i))MEMORY_DIR=i;;

        while(ENGINE_LAG>=0.01)
        {
            GAME_TIME++;
            ENGINE_LAG-=0.01;

            char &TEMP_2=CONVERTED_MAP[PLAYER.X+PLAYER.Y*23];
            BONUS_TIME-=BONUS_TIME>0;
            if(TEMP_2==42)BONUS_TIME=500000;
            TEMP_2=(TEMP_2==42||TEMP_2==46?--REM_POINTS,32:TEMP_2);

            if(GAME_TIME%10000==0)
            if(MEM_POSITION=PLAYER,GET_CHAR_FROM_MAP(DO_MOVE(PLAYER,MEMORY_DIR)))PLAYER.DIR=MEMORY_DIR;
            else if(!GET_CHAR_FROM_MAP(DO_MOVE(PLAYER=MEM_POSITION,PLAYER.DIR)))if(abs(PLAYER.X-11)>11)PLAYER.X=PLAYER.X+1?0:22;
            else PLAYER=MEM_POSITION;

            Loop(i,5)
            {
                CLASS_POSITION &GHOST=GHOSTS[i];
                if(GET_ID_FROM_POSITION(PLAYER)==GET_ID_FROM_POSITION(GHOST))if(BONUS_TIME)GHOST={11,11};else goto GOTO_START;
                char TEMP_2[]="0000";
                while(TEMP_1=rand()%4,GAME_TIME%(4000*(i+2))==0)
                if(GHOST.DIR!=(TEMP_1+2)%4||TEMP_2[0]+TEMP_2[1]+TEMP_2[2]+TEMP_2[3]==48)
                if(TEMP_2[TEMP_1]=0,GET_CHAR_FROM_MAP(DO_MOVE(MEM_POSITION={GHOST.X,GHOST.Y,TEMP_1},TEMP_1))){GHOST=MEM_POSITION;break;}
            }
            if(!REM_POINTS)goto GOTO_START;
        }

/// ===================================== DRAW_MAP


        SetConsoleCursorPosition(CONSOLE_HANDLE,COORD{0,0});
        Loop(i,529)
        {
            TEMP_1=1;
            if(GET_ID_FROM_POSITION(PLAYER)==i){SET_COLOR(14);cout<<'O';TEMP_1=0;}
            Loop(j,5)if(SET_COLOR(10+j),GET_ID_FROM_POSITION(GHOSTS[j])==i){cout<<char(2-(BONUS_TIME>0));TEMP_1=0;break;}
            if(TEMP_1){SET_COLOR(8);cout<<char(CONVERTED_MAP[i]?CONVERTED_MAP[i]:(BONUS_TIME>150000?176:(BONUS_TIME?177:-37)));}
            if(i%23>21)cout<<'\n';
        }

    }
}

