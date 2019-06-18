#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define A(i,m) for(int i=0;i<m;i++)
#define B return
#define C(c,m) c.X+c.Y*(m+23)
using namespace std;struct D{int X,Y,DIR;};char E[]="XJAJBACADAAADACABACADAAADACABGBAAABGBACAAIAACABEAAGAAEFAADADAAJADAAADAJAAIAAJAAACACAAAEHAEAHEAAAGAAAJAAIAAJAAAGAAAFJAJBACADAAADACABCAMACDAAAAAGAAAAADEADADAEBAHAAAHABUX",F[550],G[550];int H=1,I,J=237,K,L;D M,N[5],O;float P,Q,R;int S(D &o,int d,int a=0){O=o;if(!d)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;if(a&&(o.X==-1||o.X==23))B 1;if(F[C(o,0)]==-37){o=O;B 0;}else B 1;}int main(){A(i,167){memset(F+I,(i%2?'.':-37),E[i]-64);I+=E[i]-64;}F[70]=42;F[90]=42;F[438]=42;F[458]=42;M={5,5};A(i,5)N[i]={11,11};while(1){Q=clock();R+=Q-P;P=Q;A(i,4)if(GetAsyncKeyState(37+i))K=i;while(R>=0.5){R-=2;H++;char &T=F[C(M,0)];if(T=='.'||T=='*'){J--;L=T=='*'?2700:L;T=' ';}L-=L>0;if(H%60==0)if(S(M,K,1))M.DIR=K;else S(M,M.DIR,1);if(abs(M.X-11)>11)M.X=M.X+1?0:22;A(i,5){if(C(M,0)==C(N[i],0))if(L)N[i]={11,11};else B 0;char U[]="0000",W=1;while(H%(40*(i+1))==0){I=rand()%4;Q=(I+2)%4!=N[i].DIR;if((Q||!W)&&S(N[i],I)){N[i].DIR=I;break;}if(Q)U[I]=0;I=0;A(j,4)I+=U[j];W=I!='0';}}}if(!J)B 0;system("cls");I=(L?177-(L>800):-37);A(i,530)G[i+i/23]=(F[i]==-37?I:F[i]);A(i,23)G[(i+1)*24-1]=10;G[C(M,1)]='O';A(i,5)G[C(N[i],1)]=2-(L>0);cout<<G;}}