#include<stdio.h>
#include<stdlib.h> 
#include<conio.h> 
#include<time.h>
#include<math.h>
void welcome(){
	/*puts("�X�j�j�j�j�j�j�j�j�j�j�j�j�[");
	puts("�d     ��ӭ������Ϸ       �g");
	puts("�d       1->����          �g");
	puts("�d       2->ʯͷ          �g");
	puts("�d       3->��            �g");
	puts("�d       0->�˳�          �g");
	puts("�^�m�m�m�m�m�m�m�m�m�m�m�m�a");
	*/
	puts("����������������������������");
	puts("��     ��ӭ������Ϸ       ��");
	puts("��       1->����          ��");
	puts("��       2->ʯͷ          ��");
	puts("��       3->��            ��");
	puts("��       0->�˳�          ��");
	puts("����������������������������");
	
}
int main(){
	int money=0;
	srand((unsigned)time(NULL));
	char s[3][5]={{"����"},{"ʯͷ"},{"��"}};
	int a;
	int b;
	welcome();
	while(1){
		printf("���:");
		a=getch()-49;
		if(a==-1){
			break;
		}
		puts(s[a]);
		b=rand()%3;
		printf("�ҳ�:%s",s[b]); 
		if(a==b){
			printf("ƽ��!\n");
		}
		else{
			if(a==2){
				a=-1;
			}
			if(a+1==b){
				printf("\n���ź�������!���-50!\n");
				money-=50;
			}
			else{
				printf("\n��Ӯ��!���+75!\n");
				money+=75;
			}
		} 
	}
	puts("\nThank You For Your Use!\n");
	return 0;
}
