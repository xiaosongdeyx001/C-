// ָ�뺯��
//#include<stdio.h>
//#include<stdlib.h>
//
//// �ú����Ĺ���Ϊ��ͨ��ָ�뺯������ָ��ָ�� p ָ�� a[1]��Ҳ���ǻ�ȡa[1]�ĵ�ַ
//int* getAddress(int *p)// ָ�뺯�������ʽ��type * f(�ɱ�����б�)
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


// ����ָ��
#include<stdio.h>
#include<stdlib.h>
// ָ��pf���Բ������ܹ��������Ӻ��������Ӻ����������ǵ����Ӻ�������ڵ�ַ
int (* pf)(int a, int b); // ����ָ�붨���ʽ��type (* pf)(�ɱ�����б�)

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
            pf = Sum; // ���Ӻ����ĵ�ַ��pf����pf���Ե����Ӻ���Sum�����a + b����ͬ
            result = (*pf)(a, b);// ���� pf ָ����Ӻ�������
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
                puts("��������Ϊ0");
                continue;
            }
        }
        printf("%d\n", result);
    }
    return 0;
}
