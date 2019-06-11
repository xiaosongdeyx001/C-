#include<stdio.h>
#include<math.h>
int judge(int a)
{
    int i,f;
    f=0;
    for(i=2;i<=sqrt(a);i++)
    {
        if(a%i==0)
        {
            f=1;
            break;
        }
    }
    return f;
}
int main()
{
    int a,b,c,d;
    scanf("%d",&c);
    if(c%2)
    c++;
    for(d=4;d<=c;d+=2)
    {
    	for(a=2;a<c;a++)
    	{
       	 	b=d-a;
       	 	if(judge(a)==0&&judge(b)==0)
        	{
        		printf("%3d+%3d=%3d \n",a,b,d);
       		 	break;
        	}
    	}
    }
    return 0;
}

