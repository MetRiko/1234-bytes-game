#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define Loop(i,m) for(int i=0;i<m;i++)
#define MY_RETURN return
#define GET_ID_FROM_POSITION(c,m) c.X+c.Y*(m+15)

struct CLASS_POSITION{int X,Y,DIR;};

char ORIGINAL_MAP[]="PFAFBADAAABAAABAADABAAAABAAABABAACBKFAAAAACAAAADCCAD",CONVERTED_MAP[550],DRAW_MAP[550];

int GAME_TIME=1,TEMP_1,REM_POINTS=109,MEMORY_DIR,BONUS_TIME,TIME_TICK;
CLASS_POSITION PLAYER,GHOSTS[3],MEM_POSITION;

float ENGINE_PREV,ENGINE_CURR,ENGINE_LAG;

int DO_MOVE(CLASS_POSITION &o,int d,int a=1)
{
    MEM_POSITION=o;
    if(!d)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;
    if(a&&(o.X==-1||o.X==15))MY_RETURN 1;
    if(CONVERTED_MAP[GET_ID_FROM_POSITION(o,0)]==-37){o=MEM_POSITION;MY_RETURN 0;}else MY_RETURN 1;
}

int main()
{
        Loop(i,52){memset(CONVERTED_MAP+TEMP_1,(i%2?46:-37),ORIGINAL_MAP[i]-64);TEMP_1+=ORIGINAL_MAP[i]-64;}
        Loop(i,105)CONVERTED_MAP[120+i]=CONVERTED_MAP[104-i];
        CONVERTED_MAP[178]=42;CONVERTED_MAP[31]=42;CONVERTED_MAP[151]=42;CONVERTED_MAP[43]=42;
        PLAYER={5,5};Loop(i,5)GHOSTS[i]={8,8};
    while(1)
    {
        ENGINE_CURR=clock();
        ENGINE_LAG+=ENGINE_CURR-ENGINE_PREV;;
        ENGINE_PREV=ENGINE_CURR;

        Loop(i,4)if(GetAsyncKeyState(37+i))MEMORY_DIR=i;;

        while(ENGINE_LAG>=0.5)
        {
            ENGINE_LAG-=2;
            GAME_TIME++;

            char &TEMP_CHAR=CONVERTED_MAP[GET_ID_FROM_POSITION(PLAYER,0)];
            if(TEMP_CHAR==46||TEMP_CHAR==42){REM_POINTS--;BONUS_TIME=TEMP_CHAR==42?2000:BONUS_TIME;TEMP_CHAR=32;}
            BONUS_TIME-=BONUS_TIME>0;

            if(GAME_TIME%60==0)if(DO_MOVE(PLAYER,MEMORY_DIR))PLAYER.DIR=MEMORY_DIR;else DO_MOVE(PLAYER,PLAYER.DIR);
            if(abs(PLAYER.X-7)>7)PLAYER.X=PLAYER.X+1?0:14;

            Loop(i,3)
            {
                if(GET_ID_FROM_POSITION(PLAYER,0)==GET_ID_FROM_POSITION(GHOSTS[i],0))if(BONUS_TIME)GHOSTS[i]={11,11}; else MY_RETURN 0;
                char TEMP_TAB[]="0000",TEMP_2=1;
                while(GAME_TIME%(60*(i+1))==0)
                {
                    TEMP_1=rand()%4;
                    ENGINE_CURR=(TEMP_1+2)%4!=GHOSTS[i].DIR;
                    if((ENGINE_CURR||!TEMP_2)&&DO_MOVE(GHOSTS[i],TEMP_1,0)){GHOSTS[i].DIR=TEMP_1;break;}
                    if(ENGINE_CURR)TEMP_TAB[TEMP_1]=0;
                    TEMP_1=0;Loop(j,4)TEMP_1+=TEMP_TAB[j];
                    TEMP_2=TEMP_1!='0';
                }
            }

        }
        if(!REM_POINTS)MY_RETURN 0;
        system("cls");
        TEMP_1=(BONUS_TIME?177-(BONUS_TIME>800):-37);
        Loop(i,225)DRAW_MAP[i+i/15]=(CONVERTED_MAP[i]==-37?TEMP_1:CONVERTED_MAP[i]);
        Loop(i,16)DRAW_MAP[(i+1)*16-1]=10;
        DRAW_MAP[GET_ID_FROM_POSITION(PLAYER,1)]='O';
        Loop(i,3)DRAW_MAP[GET_ID_FROM_POSITION(GHOSTS[i],1)]=2-(BONUS_TIME>0);
        std::cout<<DRAW_MAP;
    }
}

