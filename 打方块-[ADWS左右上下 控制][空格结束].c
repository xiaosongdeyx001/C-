// itruirui_outlook_com_dfk.cpp : 定义控制台应用程序的入口点。
//itruirui@outlook.com
#include <stdio.h>
#include <Windows.h>
#include <process.h>

#define FPS 200	//刷新频率 = 1000 / FPS,FPS值不能小于10
#define MAX_X 17	//最大列
#define MAX_Y 22	//最大行 
#define MAX_Z 7	//操作杆长度
#define SQUARE 1
#define SPACE 0
#define BALL 2
/*全局变量的定义*/
char GameData[MAX_Y][MAX_X];	//存储数据
static short home = 0;	//记录当前操作杆头位置
static short cur_x = 0, cur_y = 0;	//存储当前 BALL 位置
static short cache_x = 0, cache_y = 0;	//存储当前 BALL 位置 默认给 BALL 指定个上次位置
static char update = 0;	// 存储更新操作，0表示无更新，1表示有更新；
static playgame = 0;	//0表示游戏可以进行，1表示游戏结束
static int number = 0;	//记录球撞击次数
static char top = 0, base = 0, left = 0, right = 0;	//记录 BALL 上下左右 是否存在 SQUARE
static char lefttop = 0, leftbase = 0, righttop = 0,rightbase = 0;	//记录四个角落是否有球 
static char fangxiang = 0;	//记录当前 BALL 运动方向，0：左上，1：右上，2：左下，3：右下
static short sleepfangxiang = 0;	//延迟方向改变。
static char sleepupdate = 0;	//存储是否执行延迟方向改变，0不执行，1执行 

/*函数声明*/
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

/*打印方块*/
void print_squere()
{
	printf("■");
}
/*打印空块*/
void print_space()
{
	printf("　");
}
/*打印 小球*/
void print_ball()
{
	printf("●");
}

/*
* 作用：判断并打印更新 BALL 周围的数据
* position ：1左上，2上，3右上，4左，5右，6左下，7下，8右下，其它情况，全部打印更新
*/
void print_periphery(const char position)
{
	switch(position)
	{
		case 1:	/*左上*/
		{
			/*更新左上角*/
			{
				GotoXY(2 * (cur_x), cur_y);	//定位到当前 BALL 左上的位置
				if(SQUARE == GameData[cur_y - 1][cur_x - 1])	//判断左上
				{
					print_squere();	//打印方块
					lefttop = 1;
				}else{
						print_space();	//打印空块
						lefttop = 0;
					}
			}
		}break;
		case 2:	/*上*/
		{
			/*更新上*/
			{
				GotoXY(2 * (cur_x + 1), cur_y);	//定位到当前 BALL 上边的位置
				if (SQUARE == GameData[cur_y - 1][cur_x])	//判断 BALL 上边是否有方块
				{
					print_squere();	//打印方块
					top = 1;	//记录下来
				}else{
						print_space();	//打印空块
						top = 0;	//记录下来
					}
			}
		}break;
		case 3:	/*右上*/
		{
			/*更新右上角*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y);	//定位到当前 BALL 右上的位置
				if(SQUARE == GameData[cur_y - 1][cur_x + 1])	//判断右上
				{
					print_squere();	//打印方块
					righttop = 1;
				}else{
						print_space();	//打印空块
						righttop = 0;
					}
			}
		
		}break;
		case 4:	/*左*/
		{
			/*更新左*/
			{
				GotoXY(2 * cur_x, cur_y + 1);	//定位到当前 BALL 左边的位置
				if (SQUARE == GameData[cur_y][cur_x - 1])	//判断 BALL 左边是否有方块
				{
					print_squere();	//打印方块
					left = 1;	//记录下来
				}else{
						print_space();	//打印空块
						left = 0;	//记录下来
					}
			}
			
		}break;
		case 5:	/*右*/
		{
			/*更新右*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y + 1);	//定位到当前 BALL 右边的位置
				if (SQUARE == GameData[cur_y][cur_x + 1])	//判断 BALL 右边是否有方块
				{
					print_squere();	//打印方块
					right = 1; 	//记录下来
				}else{
						print_space();	//打印空块
						right = 0;	//记录下来
					}
			}
			
		}break;
		case 6:	/*左下*/
		{
			/*更新左下角*/
			{
				GotoXY(2 * (cur_x), cur_y + 1 + 1);	//定位到当前 BALL 左下的位置
				if(SQUARE == GameData[cur_y + 1][cur_x - 1])	//判断左下 
				{
					print_squere();	//打印方块
					leftbase = 1;
				}else{
						print_space();	//打印空块
						leftbase = 0;
					}
			}
				
		}break;
		case 7:	/*下*/
		{
			/*更新下*/
			{
				GotoXY(2 * (cur_x + 1), cur_y + 1 + 1);	//定位到当前 BALL 下边的位置
				if (SQUARE == GameData[cur_y + 1][cur_x])	//判断 BALL 下边是否有方块
				{
					print_squere();	//打印方块
					base = 1;	//记录下来
				}else{
						print_space();	//打印空块
						base = 0;	//记录下来
					}
			}
			
		}break;
		case 8:	/*右下*/
		{
			/*更新右下角*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y + 1 + 1);	//定位到当前 BALL 右下的位置
				if(SQUARE == GameData[cur_y + 1][cur_x + 1])	//判断右下下 
				{
					print_squere();	//打印方块
					rightbase = 1;
				}else{
						print_space();	//打印空块
						rightbase = 0;
					}
			}
			
		}break;
		default:
		{
			/*更新左*/
			{
				GotoXY(2 * cur_x, cur_y + 1);	//定位到当前 BALL 左边的位置
				if (SQUARE == GameData[cur_y][cur_x - 1])	//判断 BALL 左边是否有方块
				{
					print_squere();	//打印方块
					left = 1;	//记录下来
				}else{
						print_space();	//打印空块
						left = 0;	//记录下来
					}
			}
			
			/*更新右*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y + 1);	//定位到当前 BALL 右边的位置
				if (SQUARE == GameData[cur_y][cur_x + 1])	//判断 BALL 右边是否有方块
				{
					print_squere();	//打印方块
					right = 1; 	//记录下来
				}else{
						print_space();	//打印空块
						right = 0;	//记录下来
					}
			}
			
			/*更新上*/
			{
				GotoXY(2 * (cur_x + 1), cur_y);	//定位到当前 BALL 上边的位置
				if (SQUARE == GameData[cur_y - 1][cur_x])	//判断 BALL 上边是否有方块
				{
					print_squere();	//打印方块
					top = 1;	//记录下来
				}else{
						print_space();	//打印空块
						top = 0;	//记录下来
					}
			}
			
			/*更新下*/
			{
				GotoXY(2 * (cur_x + 1), cur_y + 1 + 1);	//定位到当前 BALL 下边的位置
				if (SQUARE == GameData[cur_y + 1][cur_x])	//判断 BALL 下边是否有方块
				{
					print_squere();	//打印方块
					base = 1;	//记录下来
				}else{
						print_space();	//打印空块
						base = 0;	//记录下来
					}
			}
			
			/*更新左上角*/
			{
				GotoXY(2 * (cur_x), cur_y);	//定位到当前 BALL 左上的位置
				if(SQUARE == GameData[cur_y - 1][cur_x - 1])	//判断左上
				{
					print_squere();	//打印方块
					lefttop = 1;
				}else{
						print_space();	//打印空块
						lefttop = 0;
					}
			}
		
			/*更新左下角*/
			{
				GotoXY(2 * (cur_x), cur_y + 1 + 1);	//定位到当前 BALL 左下的位置
				if(SQUARE == GameData[cur_y + 1][cur_x - 1])	//判断左下 
				{
					print_squere();	//打印方块
					leftbase = 1;
				}else{
						print_space();	//打印空块
						leftbase = 0;
					}
			}
					
			/*更新右下角*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y + 1 + 1);	//定位到当前 BALL 右下的位置
				if(SQUARE == GameData[cur_y + 1][cur_x + 1])	//判断右下下 
				{
					print_squere();	//打印方块
					rightbase = 1;
				}else{
						print_space();	//打印空块
						rightbase = 0;
					}
			}
			
			/*更新右上角*/
			{
				GotoXY(2 * (cur_x + 1 + 1), cur_y);	//定位到当前 BALL 右上的位置
				if(SQUARE == GameData[cur_y - 1][cur_x + 1])	//判断右上
				{
					print_squere();	//打印方块
					righttop = 1;
				}else{
						print_space();	//打印空块
						righttop = 0;
					}
			}
		
		}
	}
}

/*
* 作用：重新打印所有 GAME 数据
* 返回值：无返回值
*/
void PrintGame()
{
	int i = 0, j = 0;

	/*打印顶栏装饰*/
	printf("╔");
	for (i = 0; i < MAX_X; i++)
	{
		printf("═");
	}
	printf("╗\n");

	/*打印中间 GAME 数据*/
	for (i = 0; i < MAX_Y; i++)
	{
		printf("║");
		for (j = 0; j < MAX_X; j++)
		{
			if (SQUARE == GameData[i][j])
			{
				print_squere();	//打印方块
				continue;
			}
			if (SPACE == GameData[i][j])
			{
				print_space();	//打印空块
				continue;
			}
			if (BALL == GameData[i][j])
			{
				print_ball();	//打印小球
				continue;
			}
		}
		printf("║%2d\n",i+1);
	}

	/*打印底栏装饰*/
	printf("╚");
	for (i = 0; i < MAX_X; i++)
	{
		printf("═");
	}
	printf("╝\n");

	/*结束*/
}

/*
* 作用：设定光标位置
* int x：行坐标
* int y：列坐标
*/
void GotoXY(int x, int y)
{
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

/*
* 作用：创建一个新的 GAME 数据
* 返回值：0创建成功，1创建失败
*/
int NewGame()
{
	int i = 0, j = 0;
	system("cls");	//清理已打印的数据
	system("title itruirui@outlook.com");
	/*将最上面几行设定为 SQUARE */
	for (i = 0; i < (MAX_Y / 5); i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			GameData[i][j] = SQUARE;
		}
	}

	/*剩余中间部分设置为 SPACE */
	for (i = (MAX_Y) / 5; i < MAX_Y - 2; i++)
	{
		for (j = 0; j < MAX_X; j++)
		{
			GameData[i][j] = SPACE;
		}
	}

	/*设定最后一行操作杆*/
	for (j = 0; j < (MAX_X - MAX_Z) / 2; j++)
	{
		GameData[MAX_Y - 1][j] = SPACE;
	}
	home = j;	//存储操作杆头位置
	for (i = 0; i < MAX_Z; i++)
	{
		GameData[MAX_Y - 1][j++] = SQUARE;
	}
	for (; j < MAX_X; j++)
	{
		GameData[MAX_Y - 1][j] = SPACE;
	}
	/*设定最后一行操作杆结束*/

	/*初始化 BALL 位置*/
	cur_y = MAX_Y - 2;
	cur_x = MAX_X / 2 - 1;
	cache_x = cur_x;
	cache_y = cur_y;
	GameData[cur_y][cur_x] = BALL;

	fangxiang = 1;	//默认从右上运动开始
	/*打印新建的 GAMEDATE 数据*/
	PrintGame();
	return 0;
}

/*
* 作用：更新 GAME BALL 运动数据
* 返回值：无返回值
*/
void UpdateGame()
{
	switch (fangxiang)	//运动方向，0：左上，1：右上，2：左下，3：右下
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
* 作用：操作控制
* 返回值：无返回值
*/
void PlayGame(void *p)
{
	while (1)
	{
		kbhit();	//判断键盘
		switch (getch())
		{
			case 'A':
			case 'a':
			case 75:	/*方向键 左*/
			{
				if (0 >= home)
				{
					home = 0;
					continue;
				}
				GameData[MAX_Y - 1][home + MAX_Z - 1] = SPACE;
				GameData[MAX_Y - 1][--home] = SQUARE;
				update = 2;	//设置有更新操作

			}break;

			case 'D':
			case 'd':
			case 77:	/*方向键 右*/
			{
				if (MAX_X <= home + MAX_Z)
				{
					home = MAX_X - MAX_Z;
					continue;
				}
				GameData[MAX_Y - 1][home] = SPACE;
				GameData[MAX_Y - 1][++home + MAX_Z - 1] = SQUARE;
				update = 2;	//设置有更新操作
			}break;
			
			case 'W':
			case 'w':
			case 72:	/*方向键 上*/
			{
				if(MAX_Y - 3 >= cur_y)
				{
					cur_y++;
				}
				update = 1;	//设置有更新操作
			}break;
			
			case 'S':
			case 's':
			case 80:	/*方向键 下*/
			{
				if(MAX_X - 2 >= cur_x)
				{
					cur_x++;
				}
				update = 1;	//设置有更新操作
			}break;
			case ' ':	/*空格键*/
			{
				playgame = 1;
			}break;
			default:
			break;
		}
		if (playgame) break;	//判断游戏是否结束
	}
}

/*
* 作用：检测是否达到过关数据
* 返回值：无返回值
*/
void DetectionGame(void *p)
{
	;
}

/*
* 作用：检测 BALL 撞击方块，并处理及反弹 
* 返回值：无返回值
*/
void DetectionZhuangJi(void *p)
{
	while (1)
	{
		Sleep(10);
		switch (fangxiang)	//运动方向，0：左上，1：右上，2：左下，3：右下
		{
			case 0:	//0：左上
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
			case 1:	//1：右上
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
			case 2:	//2：左下
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
			case 3:	//3：右下
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
		if (playgame) break;	//判断游戏是否结束
	}
}

/*
* 作用：检测边界，并自行处理
* 返回值：无返回值
*/
void DetectioBoundary(void *p)
{
	while (1)
	{
		Sleep(10);
		switch (fangxiang)	//运动方向，0：左上，1：右上，2：左下，3：右下
		{
			case 0:	//运动方向，0：左上
			{
				/*左，上边界判断*/
				{
					if (0 == cur_x)	//判断是否到左边界
					{
						fangxiang = 1;
						continue;
					}
					if (0 == cur_y)	//判断是否到上边界
					{
						fangxiang = 2;
						continue;
					}
				}
			}break;
			case 1:	//运动方向，1：右上
			{
				/*右，上边界判断*/
				{
					if (MAX_X - 1 == cur_x)	//判断是否到右边界
					{
						fangxiang = 0;
						continue;
					}
					if (0 == cur_y)	//判断是否到上边界
					{
						fangxiang = 3;
						continue;
					}
				}
				
			}break;
			case 2:	//运动方向，2：左下
			{
				/*左边界，操作杆那行判断*/
				{
					if (0 == cur_x) //判断是否左边界
					{
						fangxiang = 3;
						continue;
					}
					if (SQUARE == GameData[MAX_Y - 1][cur_x] && MAX_Y - 2 == cur_y) //操作杆 那行判断
					{
						fangxiang = 0;
						continue;
					}
				}
				
			}break;
			case 3:	//运动方向，3：右下
			{
				/*右边界，操作杆那行判断*/
				{
					if (MAX_X - 1 == cur_x)	//右边界判断
					{
						fangxiang = 2;
						continue;
					}
					if (SQUARE == GameData[MAX_Y - 1][cur_x] && MAX_Y - 2 == cur_y)	/*操作杆那行判断*/
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
		if (playgame) break;	//判断游戏是否结束
	}
}

/*
* 作用：画面更新
* 返回值：无返回值
*/
void UpdateInterface(void *p)
{
	int i = 0, j = 0;
	while (1)
	{
		Sleep(10);
		if (!update)	continue;	//判断是否有更新操作
		/*更新操作杆位置*/
		{
			GotoXY(0, MAX_Y);
			printf("║");
			for (i = 0; i < MAX_X; i++)
			{
				GotoXY(2 * (i + 1), MAX_Y);
				GameData[MAX_Y - 1][i] == SQUARE ? print_squere() : print_space();
			}
		}
		/*更新 BALL 的位置*/
		{
			GotoXY(2 * (cache_x + 1), cache_y + 1);	//定位到上次 BALL 的位置
			printf("　");
			GameData[cache_y][cache_x] = SPACE;
			cache_x = cur_x;
			cache_y = cur_y;
			GotoXY(2 * (cur_x + 1), cur_y + 1);	//定位到当前 BALL 的位置
			printf("●");
			GameData[cur_y][cur_x] = SQUARE;
		}

		/*更新 BALL 四面八方 的数据*/
		{
			/*判断 BALL 左面是否存在方块*/
			if (0 != cur_x)	print_periphery(4);
			
			/*判断 BALL 右面是否存在方块*/
			if (MAX_X-1 != cur_x) print_periphery(5);
			
			/*判断 BALL 上面是否存在方块*/
			if (0 != cur_y) print_periphery(2);
			
			/*判断 BALL 下面是否存在方块*/
			if( MAX_Y - 2 != cur_y && MAX_Y - 1 != cur_y)	print_periphery(7);
			
			if(0 == cur_x || MAX_X - 1 == cur_x || 0 == cur_y )
			{
				/*判断是否更新 右上角，右下角*/
				if(0 == cur_x)	//判断 BALL 是否在左边界
				{
					/*BALL 左上角的时候，只更新右下角，否则，更新右上角，右下角*/
					if(0 == cur_y)	//判断 BALL 是否在顶栏
					{
						/*更新右下角*/
						print_periphery(8);
					}else{
							/*更新右下角*/
							print_periphery(8);
							/*更新右上角*/
							print_periphery(3);
						}
				}	//end of if(0 == cur_x)
				
				/*判断是否更新 左上角，左下角*/
				if(MAX_X - 1 == cur_x)	//判断 BALL 是否在右边界
				{
					/*BALL 右上角的时候，只更新左下角，否则，更新左上角，左下角*/
					if(0 == cur_y)	//判断 BALL 是否在顶栏
					{
						/*更新左下角*/
						print_periphery(6);
					}else{
							/*更新左上角*/
							print_periphery(1);
							
							/*更新左下角*/
							print_periphery(6);
						}
				}	//end of if(MAX_X - 1 == cur_x)
				
				/*判断是否更新 左下角，右下角*/
				if(0 == cur_y && 0 != cur_x && MAX_X - 1 == cur_x)
				{
					/*更新左下角*/
					print_periphery(6);
						
					/*更新右下角*/
					print_periphery(8);
				}
			}	//end of if(0 == cur_x || MAX_X - 1 == cur_x || 0 == cur_y )
			/*否则 全部角落更新*/
			else{
				print_periphery(1);	/*左上*/
				print_periphery(3);	/*右上*/
				print_periphery(6);	/*左下*/
				print_periphery(8);	/*右下*/
			}	//end of if(0 == cur_x || MAX_X - 1 == cur_x || 0 == cur_y ) else
		}
		
		
		
		/*数据更新完后，重新定制光标位置并更新操作杆下面的滑块*/
		GotoXY(MAX_X - 4, MAX_Y + 2);
		printf("[%2d]&&[%2d]", cur_x + 1, cur_y + 1);
		update = 0;	//重置更新操作
		if (playgame)	break;	//判断游戏是否结束
	}
}

int main()
{
	NewGame();
	_beginthread(PlayGame, 0, NULL);	//启动 操作 线程
	_beginthread(DetectionZhuangJi, 1, NULL);	//启动 BALL 撞击方块并处理 线程
	_beginthread(DetectioBoundary, 2, NULL);	//启动 边界检测 线程 top,left,right
	_beginthread(UpdateInterface, 3, NULL);	//启动 画面更新 线程

	/*进入 GAME 循环*/
	while (1)
	{
		Sleep(FPS);	//设定刷新频率
		UpdateGame();
		if (MAX_Y - 1 == cur_y || playgame)
		{
			break;
		}
	}
	/*结束 GAME 循环*/

	/*输出结束语*/
	system("cls & color 4f");
	printf("GAME OVER!\n");
	system("pause");
	return 0;
}

