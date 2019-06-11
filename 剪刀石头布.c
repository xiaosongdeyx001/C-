#include<stdio.h>
#include<stdlib.h> 
#include<conio.h> 
#include<time.h>
#include<math.h>
void welcome(){
	/*puts("╔╦╦╦╦╦╦╦╦╦╦╦╦╗");
	puts("╠     欢迎进入游戏       ╣");
	puts("╠       1->剪刀          ╣");
	puts("╠       2->石头          ╣");
	puts("╠       3->布            ╣");
	puts("╠       0->退出          ╣");
	puts("╚╩╩╩╩╩╩╩╩╩╩╩╩╝");
	*/
	puts("┏━━━━━━━━━━━━┓");
	puts("┃     欢迎进入游戏       ┃");
	puts("┃       1->剪刀          ┃");
	puts("┃       2->石头          ┃");
	puts("┃       3->布            ┃");
	puts("┃       0->退出          ┃");
	puts("┗━━━━━━━━━━━━┛");
	
}
int main(){
	int money=0;
	srand((unsigned)time(NULL));
	char s[3][5]={{"剪刀"},{"石头"},{"布"}};
	int a;
	int b;
	welcome();
	while(1){
		printf("你出:");
		a=getch()-49;
		if(a==-1){
			break;
		}
		puts(s[a]);
		b=rand()%3;
		printf("我出:%s",s[b]); 
		if(a==b){
			printf("平局!\n");
		}
		else{
			if(a==2){
				a=-1;
			}
			if(a+1==b){
				printf("\n很遗憾你输了!金币-50!\n");
				money-=50;
			}
			else{
				printf("\n你赢了!金币+75!\n");
				money+=75;
			}
		} 
	}
	puts("\nThank You For Your Use!\n");
	return 0;
}
