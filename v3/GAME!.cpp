#define _WIN32_WINNT 0x0500
#include <windows.h>
#include <ctime>
#include <iostream>
#define A(i,m) for(int i=0;i<m;i++)
#define B return
#define C(c,m) c.X+c.Y*(m+15)
struct D{int X,Y,W;};char E[]="PFAFBADAAABAAABAADABAAAABAAABABAACBKFAAAAACAAAADCCAD",R[550],S[550];int F=1,G,H=109,I,J;D K,L[3],M;float N,O,P;int Q(D &o,int d,int a=1){M=o;if(!d)o.X--;if(d==1)o.Y--;if(d==2)o.X++;if(d==3)o.Y++;if(a&&(o.X==-1||o.X==15))B 1;if(R[C(o,0)]==-37){o=M;B 0;}else B 1;}int main(){A(i,52){memset(R+G,(i%2?46:-37),E[i]-64);G+=E[i]-64;}A(i,105)R[120+i]=R[104-i];R[178]=42;R[31]=42;R[151]=42;R[43]=42;K={5,5};A(i,5)L[i]={8,8};while(1){O=clock();P+=O-N;;N=O;A(i,4)if(GetAsyncKeyState(37+i))I=i;;while(P>=0.5){P-=2;F++;char &T=R[C(K,0)];if(T==46||T==42){H--;J=T==42?1300:J;T=32;}J-=J>0;if(F%60==0)if(Q(K,I))K.W=I;else Q(K,K.W);if(abs(K.X-7)>7)K.X=K.X+1?0:14;A(i,3){if(C(K,0)==C(L[i],0))if(J)L[i]={11,11}; else B 0;char U[]="0000",V=1;while(F%(60*(i+1))==0){G=rand()%4;O=(G+2)%4!=L[i].W;if((O||!V)&&Q(L[i],G,0)){L[i].W=G;break;}if(O)U[G]=0;G=0;A(j,4)G+=U[j];V=G!='0';}}}if(!H)B 0;system("cls");G=(J?177-(J>400):-37);A(i,225)S[i+i/15]=(R[i]==-37?G:R[i]);A(i,16)S[(i+1)*16-1]=10;S[C(K,1)]='O';A(i,3)S[C(L[i],1)]=2-(J>0);std::cout<<S;}}