#define _WIN32_WINNT 0x0500
#define Loop(i,m) for(int i=0;i<m;i++)
#include <windows.h>
#include <iostream>
#include <vector>
#include <ctime>
using namespace std; void HideCursor(){HANDLE consoleHandle=GetStdHandle(STD_OUTPUT_HANDLE);CONSOLE_CURSOR_INFO info;info.dwSize=100;info.bVisible = false;SetConsoleCursorInfo(consoleHandle,&info);}
void SetPos(int X, int Y){static HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);SetConsoleCursorPosition(H,{X,Y});} int Check(int Key){return GetAsyncKeyState(Key);}

size_t CT;
bool Time(float &T, float D){return(1.0*(clock()-T)>D*CLOCKS_PER_SEC)?T=clock(),true:false;} struct Vec2{float X,Y,N; Vec2(float X, float Y):X(X),Y(Y),N(0){;}};
bool Time(size_t Delta){return !(CT%Delta);}
struct Pos{float x,y,d,md; Pos(float x,float y):x(x),y(y),d(0),md(0){;}Pos():x(11),y(11),d(0),md(0){;}};
void Color(char id){SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),id);}

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
22221011110101111012222\
22221010000000001012222\
11111010111011101011111\
00000000100000100000000\
11111010111111101011111\
22221010000000001012222\
11111010111111101011111\
10000000000100000000001\
10111011110101111011101\
10001000000000000010001\
11101010111111101010111\
13000010000100001000031\
10111111110101111111101\
10000000000000000000001\
11111111111111111111111"
},Map=Map_c;

//bool GetMap(int x,int y){return Map[y*23+x]-'0';}
bool GetMap(int x,int y){if(Map[y*23+x]=='1') return true;else return false;}

Pos Player(1,1), Ghosts[5];
size_t Bonus=0;

void DrawEntity()
{
    Color(14);
    if(Bonus)Color(15);
    SetPos(Player.x,Player.y);cout<<'O';
    Loop(i,5){Color(10+i);if(Bonus)Color(15);SetPos(Ghosts[i].x,Ghosts[i].y);cout<<(Bonus?char(001):char(002));}
    Color(7);

}

int CheckColl(Pos &P,int d)
{
    if(d==2&&!GetMap(P.x-1,P.y)) return 3;
    else if(d==3&&!GetMap(P.x+1,P.y)) return 4;
    else if(d==0&&!GetMap(P.x,P.y-1)) return 1;
    else if(d==1&&!GetMap(P.x,P.y+1)) return 2;
    return 0;
}

#define MD(L,X,Y) (md==L&&!GetMap(x+X,y+Y))
void SomeMove(Pos &P,int Del)
{
    static float T=clock();
    float &x=P.x,&y=P.y,&d=P.d,&md=P.md;

    if(MD(2,-1,0)||MD(3,1,0)||MD(0,0,-1)||MD(1,0,1)) d=md;

    //if(Time(T,0.1))
    if(Time(Del))
    {
        if(d==2&&x==0) x=22; else if(d==3&&x==22) x=0;
        else switch(CheckColl(P,d)){case 1:--y;break;case 2:++y;break;case 3:--x;break;case 4:++x;break;}
    }
}

#define CH(K,M) if(Check(VK_ ## K)) Player.md=M;
int GS;
void MoveEntity()
{
    if(Bonus)Bonus--;

    CH(LEFT,2) CH(RIGHT,3) CH(UP,0) CH(DOWN,1)
    SomeMove(Player,10000);

    if(Map[Player.x+Player.y*23]=='3') Bonus=500000;
    Map[Player.x+Player.y*23]='2';


    Loop(i,5)
    {
        Pos &Ghost=Ghosts[i];
        if(Bonus&&Player.x==Ghost.x&&Player.y==Ghost.y) Ghost=Pos(11,11);
        if(!Bonus&&Player.x==Ghost.x&&Player.y==Ghost.y) GS=2;
        int m=Ghost.md;
        vector<int> Dir;
        if(CheckColl(Ghost,0)&&m!=1) Dir.push_back(0);
        if(CheckColl(Ghost,1)&&m!=0) Dir.push_back(1);
        if(CheckColl(Ghost,2)&&m!=3) Dir.push_back(2);
        if(CheckColl(Ghost,3)&&m!=2) Dir.push_back(3);
        if(Dir.empty()) Ghost.md=(m+1)%2+m/2*2;
        else Ghost.md=Dir[rand()%Dir.size()];

        SomeMove(Ghosts[i],30000);
    }
}

string DMap;

void SetMap_K()
{
    DMap="";
    Loop(i,23)Loop(j,23)
    {

        if(Map[i*23+j]=='1') DMap+=(Bonus>150000?char(176):(Bonus?char(177):char(219)));
        if(Map[i*23+j]=='0') DMap+='.';
        if(Map[i*23+j]=='2') DMap+=' ';
        if(Map[i*23+j]=='3') DMap+=char(254);
        if(j==22)DMap+='\n';
    }
}

vector<int> VecBon;
void SetMap()
{
    VecBon.clear();
    DMap="";
    Loop(i,23)Loop(j,23)
    {
        if(Map[i*23+j]=='1') DMap+=(Bonus>150000?char(176):(Bonus?char(177):char(219)));
        if(Map[i*23+j]=='0') DMap+='.';
        if(Map[i*23+j]=='2') DMap+=' ';
        if(Map[i*23+j]=='3') {DMap+=char(254);VecBon.push_back(i*23+j);}
        if(j==22)DMap+='\n';
    }
}


void DrawMap()
{
    SetPos(0,0);

    Color(8);
    cout<<DMap;

    Color(15);
    Loop(i,VecBon.size())
    {
        SetPos(VecBon[i]%23,VecBon[i]/23);
        cout<<char(254);
    }

    Color(11);
    SetPos(25,0); cout<<"           ";
    SetPos(25,0); cout<<"Bonus: "<<Bonus/100;
    size_t Count=0;
    Loop(i,Map.size())if(Map[i]=='0'||Map[i]=='3')Count++;
    SetPos(25,1); cout<<"              ";
    SetPos(25,1); cout<<"Points: "<<Count;
    if(!Count) GS=1;
    Color(7);
}

int main()
{
    srand(time(NULL));
    HWND Hwnd=GetConsoleWindow();HideCursor();
    SetMap();

    float Clock=clock(),Clock2=clock();

    double previous=clock(),lag=0.0;
    while(!GS)
    {
        double current=clock();
        double elapsed=current-previous;
        previous=current;
        lag+=elapsed;

        while(lag>=0.01)
        {
            MoveEntity();
            CT++;
            lag-=0.01;
        }

        if(Time(Clock2,0.05)){SetMap();DrawMap();}
        DrawEntity();

        if(GS==1||GS==2)
        {
            system("cls");
            cout<<(GS==1?"CONGRATULATIONS!!!\nDo you wanna try again? [Y/N]\n":"GAME OVER.. :(\nDo you wanna try again? [Y/N]\n");
            while(true)if(Check(0x59)){cout<<"Loading...";current=clock();previous=clock();lag=0.0;Map=Map_c;GS=0;Player=Pos(1,1);Loop(i,5)Ghosts[i]=Pos();CT=1;break;}else if(Check(0x4E)){return 0;}
            system("cls");
        }
    }
}
