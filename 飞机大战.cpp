#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
const int L=12;
const int H=16;
int cot=0;
int score=0;
char Map[H][L];
void Initial();
void Show();
void Move();
void Button();
void Score();
void Check_PBoard();
void Check_EBoard();
void Bullet_Move();
void Check_Bulletboard();
void P_Move();
void E_Move(); 
void Check_Bullet_n_Enemy();
void Check_Enemy_n_Plane();
const char L_wing='-';
const char R_wing='-';
const char Body='@';
const char Em='$';
struct aircraft
{
	int Lx,Ly;
	int Bx,By;
	int Rx,Ry;
}PL;
struct Enemy
{
	int Ex;
	int Ey;
}E;
struct Bullet
{
	int Bx;
	int By;
}B[30];
main()
{
	Initial();
	Show();
}
void Initial()
{
	int i,j; 
	system("title air war");
	memset(Map, '.', sizeof(Map));
	PL.Lx=H-1;
	PL.Ly=L/2-1;
	PL.Rx=H-1;
	PL.Ry=L/2+1;
	PL.Bx=H-1;
	PL.By=L/2;
	Map[H-1][L/2]=Body;
	Map[H-1][L/2-1]=L_wing;
	Map[H-1][L/2+1]=R_wing;
	srand(time(0));
	E.Ey=rand()%L;
	if(E.Ey==0)
     {
  	 	E.Ey+=1;
   	 }
    if(E.Ey==L-1)
    {
   	    E.Ey-=1;
    }
	E.Ex=0;
	Map[E.Ex][E.Ey]=Em;
	for(i=0;i<H;i++)
	 {for(j=0;j<L;j++)
	   printf("%c",Map[i][j]);
	  printf("\n");
	 }
	 printf("按任意键开始游戏\n");
	 getch();
}
void Button()
{ 
    int key;
	while(kbhit())
	{
	    key=getch();	
	}
	switch(key)
	{
		case 75:{PL.Ly-=1;
		         PL.Ry-=1;
                 PL.By-=1;
		         }break;
        case 77:{PL.Ly+=1;
		         PL.Ry+=1;
                 PL.By+=1;
		         }break;
        case ' ':{
        	       B[cot].By=PL.By;
        	       B[cot].Bx=H-2;
        	       Map[B[cot].Bx][B[cot].By]='*';
        	       cot++;
        	     }break;
	}
	
}
void P_Move()
{
	Map[H-1][PL.Ly]='.';
	Map[H-1][PL.Ry]='.';
	Map[H-1][PL.By]='.';
	Button();
	Check_PBoard();
	Map[H-1][PL.Ly]=L_wing;
	Map[H-1][PL.Ry]=R_wing;
	Map[H-1][PL.By]=Body;
}
void Check_PBoard()
{
     if(PL.Ry>L-1)
	  {PL.Ry=L-1;
	   PL.Ly=L-3;
	   PL.By=L-2;
	  }
	 if(PL.Ly<0)
	  {PL.Ry=2;
	   PL.Ly=0;
	   PL.By=1;
	  }
}
void E_Move()
{
	Map[E.Ex][E.Ey]='.';
	Check_EBoard();
	E.Ex+=1;
	Map[E.Ex][E.Ey]=Em;
}
void Bullet_Move()
{  
   int i;
   for(i=0;i<cot;i++)
   if(Map[B[i].Bx][B[i].By]=='*')
	{Map[B[i].Bx][B[i].By]='.';
	 B[i].Bx-=1;
	 Map[B[i].Bx][B[i].By]='*';
	}
   
}
void Check_EBoard()
{ 
	if(E.Ex >= H-1)
	{ 
      E.Ex=-1;
      E.Ey=rand()%L;
	}
}
void Check_Bulletboard()
{ 
    int i,j;
	for(i=0;i<cot;i++)
	 {
 		if(B[i].Bx<0)
 		 {for(j=i;j<cot-1;j++)
 		  {
 		 	B[j].Bx=B[j+1].Bx;
 		 	B[j].By=B[j+1].By;
 		  }
	      cot--;
 		 }
 	}
}
void Check_Bullet_n_Enemy()
{
	 int i,a,b;
     for(i=0;i<=cot;i++)
      {
      	if(B[i].Bx==E.Ex&&B[i].By==E.Ey)
      	 {
 	      	a=E.Ex,b=E.Ey;
		    Map[a][b]=='.';
		    E.Ex=0;
 	      	E.Ey=rand()%L;
 	      	score+=10;
 	      	if(E.Ey==0)
 	      	 {
 	      	 	E.Ey+=1;
 	      	 }
    	    if(E.Ey==L-1)
    	     {
     	    	E.Ey-=1;
     	    }
 	      }
      }
}
void Check_Enemy_n_Plane()
{
	if(E.Ex==PL.Lx&&E.Ey==PL.Ly||E.Ex==PL.Rx&&E.Ey==PL.Ry||E.Ex==PL.Bx&&E.Ey==PL.By)
	 {
 		printf("                            游戏失败/(ㄒoㄒ)/~~");
 		getch();
 	}
}
void Show()
{
   int i,j,b;
	while(1)
   {
	Sleep(500);
	system("cls");
	P_Move();
    E_Move();
    Bullet_Move();
    Check_Bullet_n_Enemy();
	for(i=0;i<H;i++)
	 {for(j=0;j<L;j++)
	   printf("%c",Map[i][j]);
	  printf("\n");
	 } 
	 printf("小键盘方向键移动\n");
     printf("空格键发射子弹\n");
     printf("                               您目前得分:%d\n",score);
     Check_Bulletboard();
    Check_Enemy_n_Plane();
	}
}
