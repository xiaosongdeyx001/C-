#include<stdio.h>
int main()
{
	int a,b,c,n;
	long int d;
	scanf("%d",&n);
	if(n>=1&&n<=20)
	{
		for(a=1;a<=n;a++)
		{
			d=1;
			for(b=1;b<=a;b++)
			{
				printf("%ld ",d);
				d=d*(a-b)/b;
			}
			printf("\n");
		}
	}
	else
	printf("error");
	return 0;
}
