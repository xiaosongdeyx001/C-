/*
   ���ܣ�ѧ������ϵͳ������ʵ�֡�
*/

# include <stdio.h>
# include <malloc.h>   
void Input(struct Student * , int );
void Output(struct Student * , int );      
void Sort(struct Student * , int );
struct Student        
{
   int ID;
   char name[100];
   float score;
};

int main(void)
{
    int len;
	struct Student  * Pst;
	printf("��������뱣���ѧ���ɼ�������\n");
	printf("Len = ");
	scanf("%d",&len);
	printf("\n\n");

	Pst = (struct Student *)malloc(sizeof(struct Student) * len);  
	Input(Pst, len);       
    Output(Pst, len);     

	printf("�����밴Enter����");
	getchar();
	printf("��������:\n");
	Sort(Pst, len);        
	Output(Pst, len);

	return 0;
}

void Input(struct Student * Pst,int len)
{
	for( int i=0; i<len; ++i)
	{
		printf("��%d��ѧ����Ϣ��\n",i+1);
	    printf("ID = ");
		scanf("%d",  &Pst[i].ID);
		printf("Name :");
		scanf("%s", Pst[i].name);
		printf("Score = ");
		scanf("%f", &Pst[i].score);
		putchar('\n');
	}
	getchar();
	printf("\n\n");
}

void Output(struct Student * Pst,int len)
{
	for( int i=0; i<len; ++i)
	{
		printf("��%d��ѧ����Ϣ���£�\n",i+1);
	    printf("ID: %d\n", Pst[i].ID);
		printf("Name��%s\n", Pst[i].name);
		printf("Score: %.1f\n", Pst[i].score);
		putchar('\n');
	}
	printf("\n\n");
}

void Sort(struct Student * Pst, int len)
{
   struct Student t;        
		
   for(int i=0; i<len-1; ++i)
	{
		for(int j=0; j<len-1-i; ++j)
		{
			if(Pst[j].score < Pst[j+1].score)    
			{
				t = Pst[j];
				Pst[j] = Pst[j+1];             
				Pst[j+1] = t;
			}
		}
   }
}