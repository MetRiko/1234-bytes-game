#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define A(i,m) for(int i=0;i<m;i++)
#define C(c,m) c.X+c.Y*m
using namespace std;struct B{int X,Y,V;};char D[]="XJAJBACADAAADACABACADAAADACABGBAAABGBACAAIAACABEAAGAAEFAADADAAJADAAADAJAAIAAJAAACACAAAEHAEAHEAAAGAAAJAAIAAJAAAGAAAFJAJBACADAAADACABCAMACDAAAAAGAAAAADEADADAEBAHAAAHABUX";char E[550],F[550];int G=1,H,I=1,J,K;B L,M[5],N;float O,P,Q;int R(B &o,int d,int a=0){N=o;if(d==0)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;if(a&&(o.X==-1||o.X==23))return 1;if(E[C(o,23)]==-37) {o=N; return 0;} else return 1;}
int main(){srand(time(0));H=0;A(i,167){memset(E+H,(i%2?'.':-37),D[i]-64);H+=D[i]-64;}E[70]=42;E[90]=42;E[438]=42;E[458]=42;L={5,5,0};A(i,5)M[i]={11,11};I=237;while(1){P=clock();Q+=P-O;O=P;A(i,4)if(GetAsyncKeyState(37+i))J=i;while(Q>=0.05){Q-=0.2;G++;char &S=E[C(L,23)];if(S=='.'||S=='*'){I--;K=S=='*'?27000:K;S=' ';}K-=K>0;if(G%600==0)if(R(L,J,1))L.V=J;else R(L,L.V,1);if(abs(L.X-11)>11)L.X=L.X+1?0:22;A(i,5){
if(C(L,23)==C(M[i],23))if(K)M[i]={11,11}; else return 0;char U[]="0000",T=1;while(G%(400*(i+1))==0){H=rand()%4;P=(H+2)%4!=M[i].V;if((P||!T)&&R(M[i],H)){M[i].V=H;break;}if(P)U[H]=0;H=0;A(j,4)H+=U[j];T=H!='0';}}}if(!I)return 0;H=(K?177-(K>8000):-37);SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),COORD{0,0});A(i,530)F[i+i/23]=(E[i]==-37?H:E[i]);A(i,23)F[(i+1)*24-1]='\n';F[C(L,24)]='O';A(i,5)F[C(M[i],24)]=2-(K>0);cout<<F;}}