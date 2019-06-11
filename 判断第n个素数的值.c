#include<stdio.h>
#include<math.h>
int main()
{
	long int a,b,i,f,c=0;
	scanf("%ld",&a);
	for(i=2;;i++)
	{
		f=0;
		for(b=2;b<=sqrt(i);b++)
		{
			if(i%b==0)
			{
				f=1;
				break;
			}
		}
		if(f==0)
		{
			c++;
			if(c==a)
			{
				printf("第%ld个素数是%ld.\n",c,i);
				break;
			}
		}
	}
	return 0;
}
