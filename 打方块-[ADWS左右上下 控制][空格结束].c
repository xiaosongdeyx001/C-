// itruirui_outlook_com_dfk.cpp : �������̨Ӧ�ó������ڵ㡣
//itruirui@outlook.com
#include <stdio.h>
#include <Windows.h>
#include <process.h>

#define FPS 200	//ˢ��Ƶ�� = 1000 / FPS,FPSֵ����С��10
#define MAX_X 17	//�����
#define MAX_Y 22	//����� 
#define MAX_Z 7	//�����˳���
#define SQUARE 1
#define SPACE 0
#define BALL 2
/*ȫ�ֱ����Ķ���*/
char GameData[MAX_Y][MAX_X];	//�洢����
static short home = 0;	//��¼��ǰ������ͷλ��
static short cur_x = 0, cur_y = 0;	//�洢��ǰ BALL λ��
static short cache_x = 0, cache_y = 0;	//�洢��ǰ BALL λ�� Ĭ�ϸ� BALL ָ�����ϴ�λ��
static char update = 0;	// �洢���²�����0��ʾ�޸��£�1��ʾ�и��£�
static playgame = 0;	//0��ʾ��Ϸ���Խ��У�1��ʾ��Ϸ����
static int number = 0;	//��¼��ײ������
static char top = 0, base = 0, left = 0, right = 0;	//��¼ BALL �������� �Ƿ���� SQUARE
static char lefttop = 0, leftbase = 0, righttop = 0,rightbase = 0;	//��¼�ĸ������Ƿ����� 
static char fangxiang = 0;	//��¼��ǰ BALL �˶�����0�����ϣ�1�����ϣ�2�����£�3������
static short sleepfangxiang = 0;	//�ӳٷ���ı䡣
static char sleepupdate = 0;	//�洢�Ƿ�ִ���ӳٷ���ı䣬0��ִ�У�1ִ�� 

/*��������*/
void print_squere();
void print_space();
void print_ball();
void GotoXY(int x, int y);
void PrintGame();
int NewGame();
void UpdateGame();
void PlayGame(void *p);
void DetectionGame(void *p);
void DetectioBoundary(void *p);
void UpdateInterface(void *p);
void print_periphery(const char position);
void DetectionZhuangJi(void *p);

/*��ӡ����*/
void print_squere()
{
	printf("��");
}
/*��ӡ�տ�*/
void print_space()
{
	printf("��");
}
/*��ӡ С��*/
void print_ball()
{
	printf("��");
}

/*
* ���ã��жϲ���ӡ���� BALL ��Χ������
* position ��1���ϣ�2�ϣ�3���ϣ�4��5�ң�6���£�7�£�8���£����������ȫ����ӡ����
*/
void print_periphery(const char position)
{
	switch(position)
	{
		case 1:	/*����*/
		{
			/*�������Ͻ�*/
			{
				GotoXY(2 * (cur_x), cur_y);	//��λ����ǰ BALL ���ϵ�λ��
				if(SQUARE == GameData[cur_y - 1][cur_x - 1])	//�ж�����
				{
					print_squere();	//��ӡ����
					lefttop = 1;
				}else{
						print_space();	//��ӡ�տ�
						lefttop = 0;
					}
			}
		}break;
		case 2:	/*��*/
		{
			/*������*/
			{
				GotoXY(2 * (cur_x + 1), cur_y);	//��λ����ǰ BALL �ϱߵ�λ��
				if (SQUARE == GameData[cur_y - 1][cur_x])	//�ж� BALL �ϱ��Ƿ��з���
				{
					print_squere();	//��ӡ����
					top = 1;	//��¼����
				}else{
						print_space();	//��ӡ�տ�
						top = 0;	//��¼����
					}
			}
		}break;
		case 3:	/*����*/
		{
			/*�������Ͻ�*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y);	//��λ����ǰ BALL ���ϵ�λ��
				if(SQUARE == GameData[cur_y - 1][cur_x + 1])	//�ж�����
				{
					print_squere();	//��ӡ����
					righttop = 1;
				}else{
						print_space();	//��ӡ�տ�
						righttop = 0;
					}
			}
		
		}break;
		case 4:	/*��*/
		{
			/*������*/
			{
				GotoXY(2 * cur_x, cur_y + 1);	//��λ����ǰ BALL ��ߵ�λ��
				if (SQUARE == GameData[cur_y][cur_x - 1])	//�ж� BALL ����Ƿ��з���
				{
					print_squere();	//��ӡ����
					left = 1;	//��¼����
				}else{
						print_space();	//��ӡ�տ�
						left = 0;	//��¼����
					}
			}
			
		}break;
		case 5:	/*��*/
		{
			/*������*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y + 1);	//��λ����ǰ BALL �ұߵ�λ��
				if (SQUARE == GameData[cur_y][cur_x + 1])	//�ж� BALL �ұ��Ƿ��з���
				{
					print_squere();	//��ӡ����
					right = 1; 	//��¼����
				}else{
						print_space();	//��ӡ�տ�
						right = 0;	//��¼����
					}
			}
			
		}break;
		case 6:	/*����*/
		{
			/*�������½�*/
			{
				GotoXY(2 * (cur_x), cur_y + 1 + 1);	//��λ����ǰ BALL ���µ�λ��
				if(SQUARE == GameData[cur_y + 1][cur_x - 1])	//�ж����� 
				{
					print_squere();	//��ӡ����
					leftbase = 1;
				}else{
						print_space();	//��ӡ�տ�
						leftbase = 0;
					}
			}
				
		}break;
		case 7:	/*��*/
		{
			/*������*/
			{
				GotoXY(2 * (cur_x + 1), cur_y + 1 + 1);	//��λ����ǰ BALL �±ߵ�λ��
				if (SQUARE == GameData[cur_y + 1][cur_x])	//�ж� BALL �±��Ƿ��з���
				{
					print_squere();	//��ӡ����
					base = 1;	//��¼����
				}else{
						print_space();	//��ӡ�տ�
						base = 0;	//��¼����
					}
			}
			
		}break;
		case 8:	/*����*/
		{
			/*�������½�*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y + 1 + 1);	//��λ����ǰ BALL ���µ�λ��
				if(SQUARE == GameData[cur_y + 1][cur_x + 1])	//�ж������� 
				{
					print_squere();	//��ӡ����
					rightbase = 1;
				}else{
						print_space();	//��ӡ�տ�
						rightbase = 0;
					}
			}
			
		}break;
		default:
		{
			/*������*/
			{
				GotoXY(2 * cur_x, cur_y + 1);	//��λ����ǰ BALL ��ߵ�λ��
				if (SQUARE == GameData[cur_y][cur_x - 1])	//�ж� BALL ����Ƿ��з���
				{
					print_squere();	//��ӡ����
					left = 1;	//��¼����
				}else{
						print_space();	//��ӡ�տ�
						left = 0;	//��¼����
					}
			}
			
			/*������*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y + 1);	//��λ����ǰ BALL �ұߵ�λ��
				if (SQUARE == GameData[cur_y][cur_x + 1])	//�ж� BALL �ұ��Ƿ��з���
				{
					print_squere();	//��ӡ����
					right = 1; 	//��¼����
				}else{
						print_space();	//��ӡ�տ�
						right = 0;	//��¼����
					}
			}
			
			/*������*/
			{
				GotoXY(2 * (cur_x + 1), cur_y);	//��λ����ǰ BALL �ϱߵ�λ��
				if (SQUARE == GameData[cur_y - 1][cur_x])	//�ж� BALL �ϱ��Ƿ��з���
				{
					print_squere();	//��ӡ����
					top = 1;	//��¼����
				}else{
						print_space();	//��ӡ�տ�
						top = 0;	//��¼����
					}
			}
			
			/*������*/
			{
				GotoXY(2 * (cur_x + 1), cur_y + 1 + 1);	//��λ����ǰ BALL �±ߵ�λ��
				if (SQUARE == GameData[cur_y + 1][cur_x])	//�ж� BALL �±��Ƿ��з���
				{
					print_squere();	//��ӡ����
					base = 1;	//��¼����
				}else{
						print_space();	//��ӡ�տ�
						base = 0;	//��¼����
					}
			}
			
			/*�������Ͻ�*/
			{
				GotoXY(2 * (cur_x), cur_y);	//��λ����ǰ BALL ���ϵ�λ��
				if(SQUARE == GameData[cur_y - 1][cur_x - 1])	//�ж�����
				{
					print_squere();	//��ӡ����
					lefttop = 1;
				}else{
						print_space();	//��ӡ�տ�
						lefttop = 0;
					}
			}
		
			/*�������½�*/
			{
				GotoXY(2 * (cur_x), cur_y + 1 + 1);	//��λ����ǰ BALL ���µ�λ��
				if(SQUARE == GameData[cur_y + 1][cur_x - 1])	//�ж����� 
				{
					print_squere();	//��ӡ����
					leftbase = 1;
				}else{
						print_space();	//��ӡ�տ�
						leftbase = 0;
					}
			}
					
			/*�������½�*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y + 1 + 1);	//��λ����ǰ BALL ���µ�λ��
				if(SQUARE == GameData[cur_y + 1][cur_x + 1])	//�ж������� 
				{
					print_squere();	//��ӡ����
					rightbase = 1;
				}else{
						print_space();	//��ӡ�տ�
						rightbase = 0;
					}
			}
			
			/*�������Ͻ�*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y);	//��λ����ǰ BALL ���ϵ�λ��
				if(SQUARE == GameData[cur_y - 1][cur_x + 1])	//�ж�����
				{
					print_squere();	//��ӡ����
					righttop = 1;
				}else{
						print_space();	//��ӡ�տ�
						righttop = 0;
					}
			}
		
		}
	}
}

/*
* ���ã����´�ӡ���� GAME ����
* ����ֵ���޷���ֵ
*/
void PrintGame()
{
	int i = 0, j = 0;

	/*��ӡ����װ��*/
	printf("�X");
	for (i = 0; i < MAX_X; i++)
	{
		printf("�T");
	}
	printf("�[\n");

	/*��ӡ�м� GAME ����*/
	for (i = 0; i < MAX_Y; i++)
	{
		printf("�U");
		for (j = 0; j < MAX_X; j++)
		{
			if (SQUARE == GameData[i][j])
			{
				print_squere();	//��ӡ����
				continue;
			}
			if (SPACE == GameData[i][j])
			{
				print_space();	//��ӡ�տ�
				continue;
			}
			if (BALL == GameData[i][j])
			{
				print_ball();	//��ӡС��
				continue;
			}
		}
		printf("�U%2d\n",i+1);
	}

	/*��ӡ����װ��*/
	printf("�^");
	for (i = 0; i < MAX_X; i++)
	{
		printf("�T");
	}
	printf("�a\n");

	/*����*/
}

/*
* ���ã��趨���λ��
* int x��������
* int y��������
*/
void GotoXY(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

/*
* ���ã�����һ���µ� GAME ����
* ����ֵ��0�����ɹ���1����ʧ��
*/
int NewGame()
{
	int i = 0, j = 0;
	system("cls");	//�����Ѵ�ӡ������
	system("title itruirui@outlook.com");
	/*�������漸���趨Ϊ SQUARE */
	for (i = 0; i < (MAX_Y / 5); i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			GameData[i][j] = SQUARE;
		}
	}

	/*ʣ���м䲿������Ϊ SPACE */
	for (i = (MAX_Y) / 5; i < MAX_Y - 2; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			GameData[i][j] = SPACE;
		}
	}

	/*�趨���һ�в�����*/
	for (j = 0; j < (MAX_X - MAX_Z) / 2; j++)
	{
		GameData[MAX_Y - 1][j] = SPACE;
	}
	home = j;	//�洢������ͷλ��
	for (i = 0; i < MAX_Z; i++)
	{
		GameData[MAX_Y - 1][j++] = SQUARE;
	}
	for (; j < MAX_X; j++)
	{
		GameData[MAX_Y - 1][j] = SPACE;
	}
	/*�趨���һ�в����˽���*/

	/*��ʼ�� BALL λ��*/
	cur_y = MAX_Y - 2;
	cur_x = MAX_X / 2 - 1;
	cache_x = cur_x;
	cache_y = cur_y;
	GameData[cur_y][cur_x] = BALL;

	fangxiang = 1;	//Ĭ�ϴ������˶���ʼ
	/*��ӡ�½��� GAMEDATE ����*/
	PrintGame();
	return 0;
}

/*
* ���ã����� GAME BALL �˶�����
* ����ֵ���޷���ֵ
*/
void UpdateGame()
{
	switch (fangxiang)	//�˶�����0�����ϣ�1�����ϣ�2�����£�3������
	{
		case 0:
		{
			GameData[--cur_y][--cur_x] = BALL;
		}break;
		case 1:
		{
			GameData[--cur_y][++cur_x] = BALL;
		}break;
		case 2:
		{
			GameData[++cur_y][--cur_x] = BALL;
		}break;
		case 3:
		{
			GameData[++cur_y][++cur_x] = BALL;
		}break;
		default:
		{
			return;
		}break;
	}
	if(sleepupdate)
	{
		fangxiang = sleepfangxiang;
		sleepupdate = 0;
		return;
	}
	update = 1;
}

/*
* ���ã���������
* ����ֵ���޷���ֵ
*/
void PlayGame(void *p)
{
	while (1)
	{
		kbhit();	//�жϼ���
		switch (getch())
		{
			case 'A':
			case 'a':
			case 75:	/*����� ��*/
			{
				if (0 >= home)
				{
					home = 0;
					continue;
				}
				GameData[MAX_Y - 1][home + MAX_Z - 1] = SPACE;
				GameData[MAX_Y - 1][--home] = SQUARE;
				update = 2;	//�����и��²���

			}break;

			case 'D':
			case 'd':
			case 77:	/*����� ��*/
			{
				if (MAX_X <= home + MAX_Z)
				{
					home = MAX_X - MAX_Z;
					continue;
				}
				GameData[MAX_Y - 1][home] = SPACE;
				GameData[MAX_Y - 1][++home + MAX_Z - 1] = SQUARE;
				update = 2;	//�����и��²���
			}break;
			
			case 'W':
			case 'w':
			case 72:	/*����� ��*/
			{
				if(MAX_Y - 3 >= cur_y)
				{
					cur_y++;
				}
				update = 1;	//�����и��²���
			}break;
			
			case 'S':
			case 's':
			case 80:	/*����� ��*/
			{
				if(MAX_X - 2 >= cur_x)
				{
					cur_x++;
				}
				update = 1;	//�����и��²���
			}break;
			case ' ':	/*�ո��*/
			{
				playgame = 1;
			}break;
			default:
			break;
		}
		if (playgame) break;	//�ж���Ϸ�Ƿ����
	}
}

/*
* ���ã�����Ƿ�ﵽ��������
* ����ֵ���޷���ֵ
*/
void DetectionGame(void *p)
{
	;
}

/*
* ���ã���� BALL ײ�����飬���������� 
* ����ֵ���޷���ֵ
*/
void DetectionZhuangJi(void *p)
{
	while (1)
	{
		Sleep(10);
		switch (fangxiang)	//�˶�����0�����ϣ�1�����ϣ�2�����£�3������
		{
			case 0:	//0������
			{
				if( 1 == top && 1 == left)
				{
					GameData[cur_y - 1][cur_x] = SPACE;
					GameData[cur_y][cur_x - 1] = SPACE;
					fangxiang = 3;
					update = 1;
					continue;	
				}
				if(1 == top)
				{
					GameData[cur_y - 1][cur_x] = SPACE;
					fangxiang = 2;
					update = 1;
					continue;
				}
				if(1 == left)
				{
					GameData[cur_y][cur_x - 1] = SPACE;
					fangxiang = 1;
					continue;
				}
				if(1 == lefttop)
				{
					sleepfangxiang = 2;
					sleepupdate = 1; 
				}
			} break;
			case 1:	//1������
			{
				if(1 == top && 1 == right)
				{
					GameData[cur_y - 1][cur_x] = SPACE;
					GameData[cur_y][cur_x + 1] = SPACE;
					fangxiang = 2;
					update = 1;
					continue;
				}
				if(1 == top)
				{
					GameData[cur_y - 1][cur_x] = SPACE;
					fangxiang = 3;
					update = 1;
					continue;
				}
				if(1 == right)
				{
					GameData[cur_y][cur_x + 1] = SPACE;
					fangxiang = 0;
					continue;
				}
				if(1 == righttop)
				{
					sleepfangxiang = 3;
					sleepupdate = 1; 
				}
			} break;
			case 2:	//2������
			{
				if(cur_y < MAX_Y - 3)
				{
					if(1 == base && 1 == left)
					{
						GameData[cur_y + 1][cur_x] = SPACE;
						GameData[cur_y][cur_x - 1] = SPACE;
						fangxiang = 1;
						update = 1;
						continue;
					}
					if(1 == base)
					{
						GameData[cur_y + 1][cur_x] = SPACE;
						fangxiang = 0;
						update = 1;
						continue;
					}
					if(1 == left)
					{
						GameData[cur_y][cur_x - 1] = SPACE;
						fangxiang = 3;
						continue;
					}
					if(1 == leftbase)
					{
						sleepfangxiang = 0;
						sleepupdate = 1; 
					}
				}	
			} break;
			case 3:	//3������
			{
				if(cur_y < MAX_Y - 3)
				{
					if(1 == base && 1 == right)
					{
						GameData[cur_y + 1][cur_x] = SPACE;
						GameData[cur_y][cur_x + 1] = SPACE;
						fangxiang = 0;
						update = 1;
						continue;
					}
					if(1 == base)
					{
						GameData[cur_y + 1][cur_x] = SPACE;
						fangxiang = 1;
						update = 1;
						continue;
					}
					if(1 == right)
					{
						GameData[cur_y][cur_x + 1] = SPACE;
						fangxiang = 2;
						continue;
					}
					if(1 == rightbase)
					{
						sleepfangxiang = 1;
						sleepupdate = 1; 
					}
				}
			} break;
			default:break;
		}
		if (playgame) break;	//�ж���Ϸ�Ƿ����
	}
}

/*
* ���ã����߽磬�����д���
* ����ֵ���޷���ֵ
*/
void DetectioBoundary(void *p)
{
	while (1)
	{
		Sleep(10);
		switch (fangxiang)	//�˶�����0�����ϣ�1�����ϣ�2�����£�3������
		{
			case 0:	//�˶�����0������
			{
				/*���ϱ߽��ж�*/
				{
					if (0 == cur_x)	//�ж��Ƿ���߽�
					{
						fangxiang = 1;
						continue;
					}
					if (0 == cur_y)	//�ж��Ƿ��ϱ߽�
					{
						fangxiang = 2;
						continue;
					}
				}
			}break;
			case 1:	//�˶�����1������
			{
				/*�ң��ϱ߽��ж�*/
				{
					if (MAX_X - 1 == cur_x)	//�ж��Ƿ��ұ߽�
					{
						fangxiang = 0;
						continue;
					}
					if (0 == cur_y)	//�ж��Ƿ��ϱ߽�
					{
						fangxiang = 3;
						continue;
					}
				}
				
			}break;
			case 2:	//�˶�����2������
			{
				/*��߽磬�����������ж�*/
				{
					if (0 == cur_x) //�ж��Ƿ���߽�
					{
						fangxiang = 3;
						continue;
					}
					if (SQUARE == GameData[MAX_Y - 1][cur_x] && MAX_Y - 2 == cur_y) //������ �����ж�
					{
						fangxiang = 0;
						continue;
					}
				}
				
			}break;
			case 3:	//�˶�����3������
			{
				/*�ұ߽磬�����������ж�*/
				{
					if (MAX_X - 1 == cur_x)	//�ұ߽��ж�
					{
						fangxiang = 2;
						continue;
					}
					if (SQUARE == GameData[MAX_Y - 1][cur_x] && MAX_Y - 2 == cur_y)	/*�����������ж�*/
					{
						fangxiang = 1;
						continue;
					}
				}
				
			}break;
			default:
			{
				return; 
			} 
			break;
		}
		if (playgame) break;	//�ж���Ϸ�Ƿ����
	}
}

/*
* ���ã��������
* ����ֵ���޷���ֵ
*/
void UpdateInterface(void *p)
{
	int i = 0, j = 0;
	while (1)
	{
		Sleep(10);
		if (!update)	continue;	//�ж��Ƿ��и��²���
		/*���²�����λ��*/
		{
			GotoXY(0, MAX_Y);
			printf("�U");
			for (i = 0; i < MAX_X; i++)
			{
				GotoXY(2 * (i + 1), MAX_Y);
				GameData[MAX_Y - 1][i] == SQUARE ? print_squere() : print_space();
			}
		}
		/*���� BALL ��λ��*/
		{
			GotoXY(2 * (cache_x + 1), cache_y + 1);	//��λ���ϴ� BALL ��λ��
			printf("��");
			GameData[cache_y][cache_x] = SPACE;
			cache_x = cur_x;
			cache_y = cur_y;
			GotoXY(2 * (cur_x + 1), cur_y + 1);	//��λ����ǰ BALL ��λ��
			printf("��");
			GameData[cur_y][cur_x] = SQUARE;
		}

		/*���� BALL ����˷� ������*/
		{
			/*�ж� BALL �����Ƿ���ڷ���*/
			if (0 != cur_x)	print_periphery(4);
			
			/*�ж� BALL �����Ƿ���ڷ���*/
			if (MAX_X-1 != cur_x) print_periphery(5);
			
			/*�ж� BALL �����Ƿ���ڷ���*/
			if (0 != cur_y) print_periphery(2);
			
			/*�ж� BALL �����Ƿ���ڷ���*/
			if( MAX_Y - 2 != cur_y && MAX_Y - 1 != cur_y)	print_periphery(7);
			
			if(0 == cur_x || MAX_X - 1 == cur_x || 0 == cur_y )
			{
				/*�ж��Ƿ���� ���Ͻǣ����½�*/
				if(0 == cur_x)	//�ж� BALL �Ƿ�����߽�
				{
					/*BALL ���Ͻǵ�ʱ��ֻ�������½ǣ����򣬸������Ͻǣ����½�*/
					if(0 == cur_y)	//�ж� BALL �Ƿ��ڶ���
					{
						/*�������½�*/
						print_periphery(8);
					}else{
							/*�������½�*/
							print_periphery(8);
							/*�������Ͻ�*/
							print_periphery(3);
						}
				}	//end of if(0 == cur_x)
				
				/*�ж��Ƿ���� ���Ͻǣ����½�*/
				if(MAX_X - 1 == cur_x)	//�ж� BALL �Ƿ����ұ߽�
				{
					/*BALL ���Ͻǵ�ʱ��ֻ�������½ǣ����򣬸������Ͻǣ����½�*/
					if(0 == cur_y)	//�ж� BALL �Ƿ��ڶ���
					{
						/*�������½�*/
						print_periphery(6);
					}else{
							/*�������Ͻ�*/
							print_periphery(1);
							
							/*�������½�*/
							print_periphery(6);
						}
				}	//end of if(MAX_X - 1 == cur_x)
				
				/*�ж��Ƿ���� ���½ǣ����½�*/
				if(0 == cur_y && 0 != cur_x && MAX_X - 1 == cur_x)
				{
					/*�������½�*/
					print_periphery(6);
						
					/*�������½�*/
					print_periphery(8);
				}
			}	//end of if(0 == cur_x || MAX_X - 1 == cur_x || 0 == cur_y )
			/*���� ȫ���������*/
			else{
				print_periphery(1);	/*����*/
				print_periphery(3);	/*����*/
				print_periphery(6);	/*����*/
				print_periphery(8);	/*����*/
			}	//end of if(0 == cur_x || MAX_X - 1 == cur_x || 0 == cur_y ) else
		}
		
		
		
		/*���ݸ���������¶��ƹ��λ�ò����²���������Ļ���*/
		GotoXY(MAX_X - 4, MAX_Y + 2);
		printf("[%2d]&&[%2d]", cur_x + 1, cur_y + 1);
		update = 0;	//���ø��²���
		if (playgame)	break;	//�ж���Ϸ�Ƿ����
	}
}

int main()
{
	NewGame();
	_beginthread(PlayGame, 0, NULL);	//���� ���� �߳�
	_beginthread(DetectionZhuangJi, 1, NULL);	//���� BALL ײ�����鲢���� �߳�
	_beginthread(DetectioBoundary, 2, NULL);	//���� �߽��� �߳� top,left,right
	_beginthread(UpdateInterface, 3, NULL);	//���� ������� �߳�

	/*���� GAME ѭ��*/
	while (1)
	{
		Sleep(FPS);	//�趨ˢ��Ƶ��
		UpdateGame();
		if (MAX_Y - 1 == cur_y || playgame)
		{
			break;
		}
	}
	/*���� GAME ѭ��*/

	/*���������*/
	system("cls & color 4f");
	printf("GAME OVER!\n");
	system("pause");
	return 0;
}

