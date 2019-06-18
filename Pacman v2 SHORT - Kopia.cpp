#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define Q(i,m) for(int i=0;i<m;i++)
using namespace std;

//S T U V W X Y Z
//_E _F _G _H _I _J _K _M _N _O _P _Q _R _S _T _U _V _W _X _Y _Z


bool A(int k){return GetAsyncKeyState(k);}

struct B{int X,Y,DIR;};
int C(B c){return c.X+c.Y*23;}

char _A[]="XJAJBACADAAADACABACADAAADACABGBAAABGBACAAIAACABEAAGAAEFAADADAAJADAAADAJAAIAAJAAACACAAAEHAEAH\
EAAAGAAAJAAIAAJAAAGAAAFJAJBACADAAADACABCAMACDAAAAAGAAAAADEADADAEBAHAAAHABUX";//Size=167
char D[550];

int E=1,F,G=1,H,I;
B L, M[5];

float J,K,_B;

B N(B &o,int d){if(d==0)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;return o;}

HANDLE _C=GetStdHandle(STD_OUTPUT_HANDLE);
void O(int c){SetConsoleTextAttribute(_C,(I&&c-8?7:c));}

int main()
{
    srand(time(0));
    _D:
        F=0;
        Q(i,167){memset(D+F,(i%2?'.':0),_A[i]-64);F+=_A[i]-64;}
        D[23*3+1]='*';
        D[23*3+21]='*';
        D[23*19+1]='*';
        D[23*19+21]='*';
        L={5,5,0};Q(i,5)M[i]={11,11};
        I=0;
        system("cls");
        if(!G)cout<<"\rCONGRATULATIONS!\n";
        cout<<"\rNEW GAME? [Y/N]";
        while(E)
        {
            if(A(89))E=0;
            if(A(78))exit(0);
        }
        K=clock();
        J=K;
        _B=0;
        G=237;
    while(true)
    {
        K=clock();
        _B+=K-J;;
        J=K;
/// ===================================== LOGIC

        Q(i,4)if(A(37+i))H=i;;

        while(_B>=0.01)
        {
            E++;
            _B-=0.01;

            char &P=D[C(L)];
            if(P=='*')I=500000;
            I-=I>0;
            if(P=='*'||P=='.'){P=' ';G--;}

            if(E%10000==0)
            {
                if(D[C(N(L,H))]!=0)L.DIR=H;
                else
                {
                    N(L,(H+2)%4);
                    if(!D[C(N(L,L.DIR))]){if(L.X<0||L.X>22)L.X=(L.X+1?0:22);else N(L,(L.DIR+2)%4);}
                }
            }

            Q(i,5)
            {
                if(C(L)==C(M[i]))if(I)M[i]={11,11};else goto _D;
                char P[]="0000";
                B &R=M[i];
                if(E%(4000*(i+2))==0)
                {
                    while(true)
                    {
                        F=rand()%4;
                        if(R.DIR!=(F+2)%4||P[0]+P[1]+P[2]+P[3]==48)
                        {
                            P[F]=0;
                            if(D[C(N(R,F))]==0)N(R,(F+2)%4);
                            else{R.DIR=F;break;}
                        }
                    }
                }
            }
            if(!G){goto _D;}
        }

/// ===================================== DRAW_MAP

        SetConsoleCursorPosition(_C,COORD{0,0});
        Q(i,529)
        {
            F=1;
            if(C(L)==i){O(14);cout<<'O';F=0;}
            else Q(j,5){O(10+j);if(C(M[j])==i){cout<<char(2-(I>0));F=0;break;}}
            if(F){O(8);cout<<(D[i]?D[i]:(I>150000?char(176):(I?char(177):char(-37))));}
            if(i%23==22)cout<<'\n';
        }
    }
}

