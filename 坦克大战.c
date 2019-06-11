#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<process.h>

struct Tank//创建一个结构体，放坐标
{
	int i; 
	int j;
};
struct
{
	int i;
	int j;
}tank1 = {3,2};
int sha[40][40] = { 0 };
int score = 0;
int n = 1,m=1,N=3;
char c = 'w';
int k,k1;
char key;
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x - 1; c.Y = y - 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void prinmap()
{
	int I, J;
	for (I = 1; I <= 39; I += 2)
	{
		for (J = 1; J <= 20; J++)
		{
			if (I == 1 || I == 39 || J == 1 || J == 20)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				gotoxy(I, J);
				printf("■");
			}
			else printf("  ");
		}
		printf("\n");
	}
}


unsigned __stdcall fight(void *t)
{
	struct Tank tank = *(struct Tank *)t;
	while (m)
	{
		key = _getch();
		switch (key)
		{
		case 'a':
			tank.i -= 2;
			if (tank.i == 1){ tank.i = 3; gotoxy(tank.i, tank.j); printf("■"); sha[tank.i][tank.j] = 3; c = 'a'; break; }
			if (sha[tank.i][tank.j] == 1 || sha[tank.i][tank.j] == 2){ tank.i += 2; gotoxy(tank.i, tank.j); printf("■"); sha[tank.i][tank.j] = 3; c = 'a'; break; }
			gotoxy(tank.i, tank.j); printf("■"); gotoxy(tank.i + 2, tank.j); printf("  "); sha[tank.i][tank.j] = 3; sha[tank.i + 2][tank.j] = 0;
			Sleep(100);
			c = 'a';
			break;

		case 'd':
			tank.i += 2;
			if (tank.i == 39){ tank.i = 37; gotoxy(tank.i, tank.j); printf("■"); sha[tank.i][tank.j] = 3; c = 'd'; break; }
			if (sha[tank.i][tank.j] == 1 || sha[tank.i][tank.j] == 2){ tank.i -= 2; gotoxy(tank.i, tank.j); printf("■"); sha[tank.i][tank.j] = 3; c = 'd'; break; }
			gotoxy(tank.i, tank.j); printf("■"); gotoxy(tank.i - 2, tank.j); printf("  "); sha[tank.i][tank.j] = 3; sha[tank.i - 2][tank.j] = 0;
			Sleep(100);
			c = 'd';
			break;
		case 'w':
			tank.j -= 1;
			if (tank.j == 1){ tank.j = 2; gotoxy(tank.i, tank.j); printf("■"); sha[tank.i][tank.j] = 3; c = 'w'; break; }
			if (sha[tank.i][tank.j] == 1 || sha[tank.i][tank.j] == 2){ tank.j += 1; gotoxy(tank.i, tank.j); printf("■"); sha[tank.i][tank.j] = 3; c = 'w'; break; }
			gotoxy(tank.i, tank.j); printf("■"); gotoxy(tank.i, tank.j + 1); printf("  "); sha[tank.i][tank.j] = 3; sha[tank.i][tank.j+1] = 0;
			Sleep(100);
			c = 'w';
			break;
		case 's':
			tank.j += 1;
			if (tank.j == 20){ tank.j = 19; gotoxy(tank.i, tank.j); printf("■"); sha[tank.i][tank.j] = 3; c = 's'; break; }
			if (sha[tank.i][tank.j] == 1 || sha[tank.i][tank.j] == 2){ tank.j -= 1; gotoxy(tank.i, tank.j); printf("■"); sha[tank.i][tank.j] = 3; c = 's'; break; }
			gotoxy(tank.i, tank.j); printf("■"); gotoxy(tank.i, tank.j - 1); printf("  "); sha[tank.i][tank.j] = 3; sha[tank.i][tank.j-1] = 0;
			Sleep(100);
			c = 's';
			break;
		case 'j':
			if (c == 'w')
			{
				for (k = tank.j; k>3; k--)
				{
					gotoxy(tank.i, k - 2); printf("*"); gotoxy(tank.i, k - 1); printf("  "); Sleep(100);
					if (sha[tank.i][k - 2] == 1 || sha[tank.i][k - 1] == 1)
					{
						gotoxy(tank.i, k - 2);  printf("  ");  sha[tank.i][k - 2] = 0;  sha[tank.i][k - 1] = 0;  score++; break;
					}
					if (sha[tank.i][k-2]==2)
					{
						score += 100;
						n = 0;
						N--;
						gotoxy(tank.i, k - 2);
						printf("  ");
						sha[tank.i][k - 2] =0;
						if (N > 0){ n = 1; tank1.i = 3; tank1.j = 2; }
						break;		
					}
					if (k == 4)
					{
						gotoxy(tank.i, k - 2); printf("  ");
					}
				}
			}
			else if (c == 'a')
			{
				for (k = tank.i; k>4; k--)
				{
					gotoxy(k - 2, tank.j); printf("*"); gotoxy(k - 1, tank.j); printf(" "); Sleep(100);
					if (sha[k - 2][tank.j] == 1 || sha[k - 1][tank.j] == 1)
					{
						gotoxy(k - 2, tank.j);  printf("  ");  sha[k - 2][tank.j] = 0;  sha[k - 1][tank.j] = 0;  score++; break;
					}
					if (sha[k-2][tank.j]==2)
					{
						score += 100;
						n = 0;
						gotoxy(k-2, tank.j);
						printf("  ");
						N--;
						sha[k - 2][tank.j] = 0;
						if (N > 0){ n = 1; tank1.i = 3; tank1.j = 2; }
						break;
					}
					if (k == 5)
					{
						gotoxy(k - 2, tank.j); printf("  ");
					}
				}
			}
			else if (c == 'd')
			{
				for (k = tank.i; k<36; k++)
				{
					gotoxy(k + 3, tank.j);
					printf("*");
					gotoxy(k + 2, tank.j);
					printf(" ");
					Sleep(100);
					if (sha[k + 3][tank.j] == 1 || sha[k + 2][tank.j] == 1 || sha[k + 1][tank.j] == 1)
					{
						gotoxy(k + 3, tank.j);
						printf("  ");
						sha[k + 3][tank.j] = 0;
						sha[k + 2][tank.j] = 0;
						sha[k + 1][tank.j] = 0;
						score++;
						break;
					}
					if (sha[k+3][tank.j]==2)
					{
						score += 100;
						n = 0;
						N--;
						gotoxy(k + 3, tank.j);
						printf("  ");
						sha[k + 3][tank.j] = 0;
						if (N > 0){ n = 1; tank1.i = 3; tank1.j = 2; }
						break;
					}
					if (k == 35)
					{
						gotoxy(k + 3, tank.j);
						printf(" ");
					}
				}
			}
			else if (c == 's')
			{
				for (k = tank.j; k<18; k++)
				{
					gotoxy(tank.i, k + 2);
					printf("*");
					gotoxy(tank.i, k + 1);
					printf(" ");
					Sleep(100);
					if (sha[tank.i][k + 2] == 1 || sha[tank.i][k + 1] == 1)
					{
						gotoxy(tank.i, k + 2);
						printf("  ");
						sha[tank.i][k + 2] = 0;
						sha[tank.i][k + 1] = 0;
						score++;
						break;
					}
					if (sha[tank.i][k+2]==2)
					{
						score += 100;
						n = 0;
						N--;
						gotoxy(tank.i, k+2);
						printf("  ");
						sha[tank.i][k + 2] =0;
						if (N > 0){ n = 1; tank1.i = 3; tank1.j = 2; }
						break;
					}
					if (k == 17)
					{
						gotoxy(tank.i, k + 2);
						printf("  ");
					}
				}
			}
			 
		}
		gotoxy(50, 10);
		printf("score:%d", score);
		if (score > 300)
		{
			gotoxy(50, 5); printf("YOU WIN");
			m = 0;
		} 
	}
}
unsigned __stdcall diren(void *t)
{
	struct Tank tank = *(struct Tank *)t;
	int o;
	int p;
	

	while (n){
		
		srand((unsigned)time(NULL));
		o = rand() % 4;
		switch (o)
		{
		case 0:/* diren tank turn left*/
			for (p = 4; p > 0; p--)
			{
				tank1.i -= 2;
				if (tank1.i == 1){ tank1.i = 3; gotoxy(tank1.i, tank1.j); printf("■"); sha[tank1.i][tank1.j] = 2; break; } 
				if (sha[tank1.i][tank1.j] == 1 || sha[tank1.i][tank1.j] == 3){ tank1.i += 2; gotoxy(tank1.i, tank1.j); printf("■"); sha[tank1.i][tank1.j] = 2; break; }
				gotoxy(tank1.i, tank1.j); printf("■"); gotoxy(tank1.i + 2, tank1.j); printf("  "); sha[tank1.i][tank1.j] = 2; sha[tank1.i + 2][tank1.j] = 0;
				Sleep(100);
			}
				for (k1 = tank1.i; k1>4; k1--)
				{
					gotoxy(k1 - 2, tank1.j); printf("*"); gotoxy(k1 - 1, tank1.j); printf(" "); Sleep(100);
					if (sha[k1 - 2][tank1.j] == 1 || sha[k1 - 1][tank1.j] == 1)
					{
						gotoxy(k1 - 2, tank1.j);  printf("  ");  sha[k1 - 2][tank1.j] = 0;  sha[k1 - 1][tank1.j] = 0;  score++; break;
					}
					if (sha[k1-2][tank1.j]==3)
					{
						gotoxy(50, 5); printf("GAME OVER");
						m = 0;
						sha[k1 - 2][tank1.j] = 0;
						break;
					}
					if (k1 == 5)
					{
						gotoxy(k1 - 2, tank1.j); printf("  ");
					}
				}
			break;
		case 1:/*diren tank turn right*/
			for (p = 4; p > 0; p--)
			{
				tank1.i += 2;
				if (tank1.i == 39){ tank1.i = 37; gotoxy(tank1.i, tank1.j); printf("■"); sha[tank1.i][tank1.j] = 2; break; }
				if (sha[tank1.i][tank1.j] == 1 || sha[tank1.i][tank1.j] == 3){ tank1.i -= 2; gotoxy(tank1.i, tank1.j); printf("■"); sha[tank1.i][tank1.j] = 2; break; }
				gotoxy(tank1.i, tank1.j); printf("■"); gotoxy(tank1.i - 2, tank1.j); printf("  "); sha[tank1.i][tank1.j] = 2; sha[tank1.i - 2][tank1.j] = 0;
				Sleep(100);
			}
				for (k1 = tank1.i; k1<36; k1++)
				{
					gotoxy(k1 + 3, tank1.j);
					printf("*");
					gotoxy(k1 + 2, tank1.j);
					printf(" ");
					Sleep(100);
					if (sha[k1 + 3][tank1.j] == 1 || sha[k1 + 2][tank1.j] == 1 || sha[k1 + 1][tank1.j] == 1)
					{
						gotoxy(k1 + 3, tank1.j);
						printf("  ");
						sha[k1 + 3][tank1.j] = 0;
						sha[k1 + 2][tank1.j] = 0;
						sha[k1 + 1][tank1.j] = 0;
						score++;
						break;
					}
					if (sha[k1+3][tank1.j]==3)
					{
						gotoxy(50, 5); printf("GAME OVER");
						m = 0;
						sha[k1 + 3][tank1.j] = 0;
						break;
					}
					if (k1 == 35)
					{
						gotoxy(k1 + 3, tank1.j);
						printf(" ");
					}
				}
				break;
				
			
		case 2:
			for (p = 4; p > 0; p--)
			{
				tank1.j -= 1;
				if (tank1.j == 1){ tank1.j = 2; gotoxy(tank1.i, tank1.j); printf("■"); sha[tank1.i][tank1.j] = 2; break; }
				if (sha[tank1.i][tank1.j] == 1 || sha[tank1.i][tank1.j] == 3){ tank1.j += 1; gotoxy(tank1.i, tank1.j); printf("■"); sha[tank1.i][tank1.j] = 2; break; }
				gotoxy(tank1.i, tank1.j); printf("■"); gotoxy(tank1.i, tank1.j + 1); printf("  "); sha[tank1.i][tank1.j] = 2; sha[tank1.i][tank1.j+1] = 0;
				Sleep(100);
			}
			for (k1 = tank1.j; k1>3; k1--)
			{
				gotoxy(tank1.i, k1 - 2); printf("*"); gotoxy(tank1.i, k1 - 1); printf("  "); Sleep(100);
				if (sha[tank1.i][k1 - 2] == 1 || sha[tank1.i][k1 - 1] == 1)
				{
					gotoxy(tank1.i, k1 - 2);  printf("  ");  sha[tank1.i][k1 - 2] = 0;  sha[tank1.i][k1 - 1] = 0;  score++; break;
				}
				if (sha[tank1.i][k1-2]==3)
				{
					gotoxy(50, 5); printf("GAME OVER");
					m = 0;
					sha[tank1.i][k1 - 2] = 0;
					break;
				}
				if (k1 == 4)
				{
					gotoxy(tank1.i, k1 - 2); printf("  ");
				}
			}
			break;
		case 3:
			for (p = 4; p > 0; p--)
			{
				tank1.j += 1;
				if (tank1.j == 20){ tank1.j = 19; gotoxy(tank1.i, tank1.j); printf("■"); sha[tank1.i][tank1.j] = 2; break; }
				if (sha[tank1.i][tank1.j] == 1 || sha[tank1.i][tank1.j] == 3){ tank1.j -= 1; gotoxy(tank1.i, tank1.j); printf("■"); sha[tank1.i][tank1.j] = 2; break; }
				gotoxy(tank1.i, tank1.j); printf("■"); gotoxy(tank1.i, tank1.j - 1); printf("  ");  sha[tank1.i][tank1.j] = 2; sha[tank1.i][tank1.j - 1] = 0;
				Sleep(100);
			}    
			for (k1 = tank1.j; k1<18; k1++)
			{
				gotoxy(tank1.i, k1 + 2);
				printf("*");
				gotoxy(tank1.i, k1 + 1);
				printf(" ");
				Sleep(100);
				if (sha[tank1.i][k1 + 2] == 1 || sha[tank1.i][k1 + 1] == 1)
				{
					gotoxy(tank1.i, k1 + 2);
					printf("  ");
					sha[tank1.i][k1 + 2] = 0;
					sha[tank1.i][k1 + 1] = 0;
					score++;
					break;
				}
				if (sha[tank1.i][k1+2]==3)
				{
					gotoxy(50, 5); printf("GAME OVER");
					m = 0;
					sha[tank1.i][k1 + 2] = 0;
					break;
				}
				if (k1 == 17)
				{
					gotoxy(tank1.i, k1 + 2);
					printf("  ");
				}
			}
			break;

		}
		gotoxy(50, 10);
		printf("score:%d", score);		
		Sleep(500);
		}
	}

int main(void)
{
	struct Tank tank = { 0 };
	prinmap();
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN);
	for (tank.i = 3; tank.i<34; tank.i += 2)//方块的坐标
	{
		for (tank.j = 7; tank.j<16; tank.j += 8)
		{
			sha[tank.i][tank.j] = 1;
			gotoxy(tank.i, tank.j);
			printf("□");
		}
	}
	for (tank.i = 5; tank.i<38; tank.i += 2)
	{
		for (tank.j = 4; tank.j<16; tank.j += 8)
		{
			sha[tank.i][tank.j] = 1;
			gotoxy(tank.i, tank.j);
			printf("□");
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);
	tank.i = 9; tank.j = 19;//我方坦克初始坐标
	gotoxy(tank.i, tank.j);
	printf("■");
	gotoxy(tank1.i, tank1.j);
	printf("■");
	_beginthreadex(NULL, 0, fight, &tank, 0, NULL);
	_beginthreadex(NULL, 0, diren, &tank, 0, NULL);
	Sleep(INFINITE);
	return 0;
}
