// 指针函数
//#include<stdio.h>
//#include<stdlib.h>
//
//// 该函数的功能为：通过指针函数，让指针指向 p 指向 a[1]，也就是获取a[1]的地址
//int* getAddress(int *p)// 指针函数定义格式：type * f(可变参数列表)
//{
//    return p + 1; // <==> a + 1;
//}
//
//int main()
//{
//    int a[5] = {1, 2, 3, 4, 5};
//    int *p = getAddress(a);
//    printf("p = %p, &a[1] = %p\n", p, a + 1);
//    return 0;
//}


// 函数指针
#include<stdio.h>
#include<stdlib.h>
// 指针pf可以操作他能够操作的子函数对象，子函数的名字是调用子函数的入口地址
int (* pf)(int a, int b); // 函数指针定义格式：type (* pf)(可变参数列表)

int Sum(int a, int b)
{
    return a + b;
}
int Sub(int a, int b)
{
    return a - b;
}
int Mul(int a, int b)
{
    return a * b;
}

int Div(int a, int b, int *result)
{
    if(b == 0) return 0;
    *result = a / b;
    return 1;
}

int main()
{
    int op, a, b;
    int result;
    while(scanf("%d%d%d", &op, &a, &b) != EOF)
    {
        if(op == 1)
        {
            pf = Sum; // 把子函数的地址给pf，让pf可以调用子函数Sum，完成a + b，下同
            result = (*pf)(a, b);// 调用 pf 指向的子函数对象
        }
        else if(op == 2)
        {
            pf = Sub;
            result = (*pf)(a, b);
        }
        else if(op == 3)
        {
            pf = Mul;
            result = (*pf)(a, b);
        }
        else
        {
            int flag = Div(a, b, &result);
            if(!flag)
            {
                puts("除数不能为0");
                continue;
            }
        }
        printf("%d\n", result);
    }
    return 0;
}
