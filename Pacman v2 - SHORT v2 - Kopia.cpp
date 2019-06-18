#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define Loop(i,m) for(int i=0;i<m;i++)
using namespace std;

//A B C D E F G H I J K L M N O P Q R S T U V W X Y Z

#define A(k) GetAsyncKeyState(k)

struct J{int X,Y,Z;};
#define B(c) c.X+c.Y*23

char C[]="XJAJBACADAAADACABACADAAADACABGBAAABGBACAAIAACABEAAGAAEFAADADAAJADAAADAJAAIAAJAAACACAAAEHAEAH\
EAAAGAAAJAAIAAJAAAGAAAFJAJBACADAAADACABCAMACDAAAAAGAAAAADEADADAEBAHAAAHABUX";//Size=167
char D[550];

int E=1,W,G=1,H,I;
J K,L[5],M;

float N,O,P;

J Q(J &o,int d){if(d==0)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;return o;}

HANDLE R=GetStdHandle(STD_OUTPUT_HANDLE);
void S(int c){SetConsoleTextAttribute(R,(I&&c-8?7:c));}

char T(J c){return D[c.X+c.Y*23];}

int main()
{
    srand(time(0));
    U:
        W=0;
        Loop(i,167){memset(D+W,(i%2?'.':0),C[i]-64);W+=C[i]-64;}
        D[70]=42;
        D[90]=42;
        D[438]=42;
        D[458]=42;
        K={5,5,0};Loop(i,5)L[i]={11,11};
        I=0;
        system("cls");
        if(!G)cout<<"\rCONGRATULATIONS!\n";cout<<"\rNEW GAME? [Y/N]";
        while(E)
        {
            if(A(89))E=0;
            if(A(78))exit(0);
        }
        N=clock();
        G=237;
    while(1)
    {
        O=clock();
        P+=O-N;;
        N=O;
/// ===================================== LOGIC

        Loop(i,4)if(A(37+i))H=i;;

        while(P>=0.01)
        {
            E++;
            P-=0.01;

            char &X=D[K.X+K.Y*23];
            I-=I>0;
            if(X==42)I=500000;
            X=(X==42||X==46?--G,32:X);

            if(E%10000==0)
            if(M=K,T(Q(K,H)))K.Z=H;
            else if(!T(Q(K=M,K.Z)))if(abs(K.X-11)>11)K.X=K.X+1?0:22;else K=M;

            Loop(i,5)
            {
                J &GHOST=L[i];
                if(B(K)==B(Y))if(I)Y={11,11};else goto U;
                char X[]="0000";
                while(W=rand()%4,E%(4000*(i+2))==0)
                if(Y.Z!=(W+2)%4||X[0]+X[1]+X[2]+X[3]==48)
                if(X[W]=0,T(Q(M={Y.X,Y.Y,W},W))){Y=M;break;}
            }
            if(!G)goto U;
        }

/// ===================================== DRAW_MAP


        SetConsoleCursorPosition(R,COORD{0,0});
        Loop(i,529)
        {
            W=1;
            if(B(K)==i){S(14);cout<<'O';W=0;}
            Loop(j,5)if(S(10+j),B(L[j])==i){cout<<char(2-(I>0));W=0;break;}
            if(W){S(8);cout<<char(D[i]?D[i]:(I>150000?176:(I?177:-37)));}
            if(i%23>21)cout<<'\n';
        }

    }
}

