#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <iostream>
#include <vector>
#include <ctime>

#define Loop(i,m) for(int i=0;i<m;i++)
#define M(V,X,Y) if(j== V && Map[(y+ Y )*23+x+ X ]!='1')
#define CH(K,M) if(Check(VK_ ## K)) PL.j=M;

using namespace std;

string Map_c=
{
"11111111111111111111111\
10000000000100000000001\
10111011110101111011101\
13111011110101111011131\
10000000110101100000001\
10111010000000001011101\
10000010111111101000001\
11111010000100001011111\
11111011110101111011111\
11111010000000001011111\
11111010111011101011111\
00000000100000100000000\
11111010111111101011111\
11111010000000001011111\
11111010111111101011111\
10000000000100000000001\
10111011110101111011101\
10001000000000000010001\
11101010111111101010111\
13000010000100001000031\
10111111110101111111101\
10000000000000000000001\
11111111111111111111111"
},Map=Map_c,DMap;

/// ======================================================= Structs
struct Pos{float x=11,y=11,d=0,j=0;Pos(float X=11,float Y=11){x=X;y=Y;}};

/// ======================================================= All variables
int M,MEM2,GS,Bonus=0,CT;
Pos PL(1,1),Ghosts[5];
vector<int> Dir;

HANDLE Handle=GetStdHandle(STD_OUTPUT_HANDLE);

/// ======================================================= Timers + Engine timers
float Cl=clock(),previous=Cl,current,elapsed,lag=0.0;

/// ======================================================= Helping functions

void SP(int X,int Y){SetConsoleCursorPosition(Handle,{X,Y});}
void SP(Pos &P){SP(P.x,P.y);}
int Check(int A){return GetAsyncKeyState(A);}
bool Time(float &T, float D){return(1.0*(clock()-T)>D*CLOCKS_PER_SEC)?T=clock(),true:false;}
bool Time(int d){return !(CT%d);}
void Color(int d){SetConsoleTextAttribute(Handle,d);}
int CheckColl(Pos &P,int j){float x=P.x,y=P.y;M(2,-1,0)return 3;M(3,1,0)return 4;M(0,0,-1)return 1;M(1,0,1)return 2;return 0;}
void SomeMove(Pos &P,int D)
{
    float &x=P.x,&y=P.y,&d=P.d,&j=P.j;M(2,-1,0)d=j;M(3,1,0)d=j;M(0,0,-1)d=j;M(1,0,1)d=j;
    if(Time(D)){if(d==2&&x==0)x=22;else if(d==3&&x==22)x=0;else{D=CheckColl(P,d);if(D==1)--y;if(D==2)++y;if(D==3)--x;if(D==4)++x;}}
}
/// ======================================================= Main functions

void DrawEntity(){Color(14);if(Bonus)Color(15);SP(PL);cout<<'O';Loop(i,5){if(!Bonus)Color(10+i);SP(Ghosts[i]);cout<<(Bonus?char(1):char(2));}}

#define PS(A,B,C) if(CheckColl(G,A)&&M!=B) Dir.push_back(C);

void MoveEntity()
{
    Bonus-=Bonus>0;CH(LEFT,2)CH(RIGHT,3)CH(UP,0)CH(DOWN,1)SomeMove(PL,10000);char&K=Map[PL.x+PL.y*23];if(K==51)Bonus=500000;K=50;

    Loop(i,5)
    {
        Dir.clear();Pos &G=Ghosts[i];if(PL.x==G.x&&PL.y==G.y)if(Bonus)G=Pos(11,11);else GS=2;M=G.j;
        PS(0,1,0)PS(1,0,1)PS(2,3,2)PS(3,2,3)if(Dir.empty())G.j=M+1%2+M;else G.j=Dir[rand()%Dir.size()];SomeMove(G,(i+1)*5000);
    }
}

void DrawMap()
{
    Dir.clear();DMap="";MEM2=0;
    Loop(i,23)Loop(j,23)
    {
        M=Map[i*23+j];if(M==49)DMap+=(Bonus>150000?176:(Bonus?177:219));
        if(M==48){DMap+='.';MEM2++;}if(M==50)DMap+=' ';if(M==51){DMap+=254;MEM2++;}
        if(j==22)DMap+='\n';
    }
    SP(0,0);Color(8);
    cout<<DMap<<"\t\t\t\t\r"<<"Bonus: "<<Bonus/100<<"\tPoints: "<<MEM2;
    GS=!MEM2;
}



int main()
{
///Start
    srand(time(NULL));
    CONSOLE_CURSOR_INFO c;c.bVisible=0;SetConsoleCursorInfo(Handle,&c);
///Game loop
    while(!GS)
    {
///Engine
        current=clock();
        elapsed=current-previous;
        previous=current;
        lag+=elapsed;

///Logic
        while(lag>=0.01)
        {
            MoveEntity();
            CT++;
            lag-=0.01;
        }

///Render
    //Draw map
        Color(7);
        if(Time(Cl,0.05))
        {
            DrawMap();
        }
    //Draw entity
        DrawEntity();

///End game
        if(GS==1||GS==2)
        {
            system("cls");
            cout<<(GS==1?"CONGRATULATIONS!!!\nDo you wanna try again? [Y/N]\n":"GAME OVER.. :(\nDo you wanna try again? [Y/N]\n");
            while(true)if(Check(0x59)){cout<<"Loading...";current=clock();previous=clock();lag=0.0;Map=Map_c;GS=0;PL=Pos(1,1);Loop(i,5)Ghosts[i]=Pos();CT=1;break;}else if(Check(0x4E)){return 0;}
            system("cls");
        }
    }
}
