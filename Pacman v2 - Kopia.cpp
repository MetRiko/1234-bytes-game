#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define Loop(i,m) for(int i=0;i<m;i++)
using namespace std;

bool CHECK_KEY(int k){return GetAsyncKeyState(k);}

struct CLASS_POSITION{int X,Y,DIR;};
int GET_ID_FROM_POSITION(CLASS_POSITION c){return c.X+c.Y*23;}

char ORIGINAL_MAP[]="XJAJBACADAAADACABACADAAADACABGBAAABGBACAAIAACABEAAGAAEFAADADAAJADAAADAJAAIAAJAAACACAAAEHAEAH\
EAAAGAAAJAAIAAJAAAGAAAFJAJBACADAAADACABCAMACDAAAAAGAAAAADEADADAEBAHAAAHABUX";//Size=167
char CONVERTED_MAP[550];

int GAME_TIME=1,TEMP_1,REM_POINTS=1,MEMORY_DIR,BONUS_TIME;
CLASS_POSITION PLAYER, GHOSTS[5];

float ENGINE_PREV,ENGINE_CURR,ENGINE_LAG;

CLASS_POSITION DO_MOVE(CLASS_POSITION &o,int d){if(d==0)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;return o;}

HANDLE CONSOLE_HANDLE=GetStdHandle(STD_OUTPUT_HANDLE);
void SET_COLOR(int c){SetConsoleTextAttribute(CONSOLE_HANDLE,(BONUS_TIME&&c-8?7:c));}

int main()
{
    srand(time(0));
    GOTO_START:
        TEMP_1=0;
        Loop(i,167){memset(CONVERTED_MAP+TEMP_1,(i%2?'.':0),ORIGINAL_MAP[i]-64);TEMP_1+=ORIGINAL_MAP[i]-64;}
        CONVERTED_MAP[23*3+1]='*';
        CONVERTED_MAP[23*3+21]='*';
        CONVERTED_MAP[23*19+1]='*';
        CONVERTED_MAP[23*19+21]='*';
        PLAYER={5,5,0};Loop(i,5)GHOSTS[i]={11,11};
        BONUS_TIME=0;
        system("cls");
        if(!REM_POINTS)cout<<"\rCONGRATULATIONS!\n";
        cout<<"\rNEW GAME? [Y/N]";
        while(GAME_TIME)
        {
            if(CHECK_KEY(89))GAME_TIME=0;
            if(CHECK_KEY(78))exit(0);
        }
        ENGINE_CURR=clock();
        ENGINE_PREV=ENGINE_CURR;
        ENGINE_LAG=0;
        REM_POINTS=237;
    while(true)
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

            char &TEMP_2=CONVERTED_MAP[GET_ID_FROM_POSITION(PLAYER)];
            if(TEMP_2=='*')BONUS_TIME=500000;
            BONUS_TIME-=BONUS_TIME>0;
            if(TEMP_2=='*'||TEMP_2=='.'){TEMP_2=' ';REM_POINTS--;}

            if(GAME_TIME%10000==0)
            {
                if(CONVERTED_MAP[GET_ID_FROM_POSITION(DO_MOVE(PLAYER,MEMORY_DIR))]!=0)PLAYER.DIR=MEMORY_DIR;
                else
                {
                    DO_MOVE(PLAYER,(MEMORY_DIR+2)%4);
                    if(!CONVERTED_MAP[GET_ID_FROM_POSITION(DO_MOVE(PLAYER,PLAYER.DIR))]){if(PLAYER.X<0||PLAYER.X>22)PLAYER.X=(PLAYER.X+1?0:22);else DO_MOVE(PLAYER,(PLAYER.DIR+2)%4);}
                }
            }

            Loop(i,5)
            {
                if(GET_ID_FROM_POSITION(PLAYER)==GET_ID_FROM_POSITION(GHOSTS[i]))if(BONUS_TIME)GHOSTS[i]={11,11};else goto GOTO_START;
                char TEMP_2[]="0000";
                CLASS_POSITION &GHOST=GHOSTS[i];
                if(GAME_TIME%(4000*(i+2))==0)
                {
                    while(true)
                    {
                        TEMP_1=rand()%4;
                        if(GHOST.DIR!=(TEMP_1+2)%4||TEMP_2[0]+TEMP_2[1]+TEMP_2[2]+TEMP_2[3]==48)
                        {
                            TEMP_2[TEMP_1]=0;
                            if(CONVERTED_MAP[GET_ID_FROM_POSITION(DO_MOVE(GHOST,TEMP_1))]==0)DO_MOVE(GHOST,(TEMP_1+2)%4);
                            else{GHOST.DIR=TEMP_1;break;}
                        }
                    }
                }
            }
            if(!REM_POINTS){goto GOTO_START;}
        }

/// ===================================== DRAW_MAP

        SetConsoleCursorPosition(CONSOLE_HANDLE,COORD{0,0});
        Loop(i,529)
        {
            TEMP_1=1;
            if(GET_ID_FROM_POSITION(PLAYER)==i){SET_COLOR(14);cout<<'O';TEMP_1=0;}
            else Loop(j,5){SET_COLOR(10+j);if(GET_ID_FROM_POSITION(GHOSTS[j])==i){cout<<char(2-(BONUS_TIME>0));TEMP_1=0;break;}}
            if(TEMP_1){SET_COLOR(8);cout<<(CONVERTED_MAP[i]?CONVERTED_MAP[i]:(BONUS_TIME>150000?char(176):(BONUS_TIME?char(177):char(-37))));}
            if(i%23==22)cout<<'\n';
        }
    }
}

