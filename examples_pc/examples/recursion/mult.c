#include<stdio.h>
#include<string.h>

#define MAX 1000    // 大数的最大位数


/*
  大数乘法
  参数：
  num1为第一个因数，用字符数组保存
  num2为第二个因数
  sum数组保存相乘的结果  即：num1*num2=sum
  返回值：返回数组sum的有效长度，即计算结果的位数
 */
int Multiplication(char num1[],char num2[], int sum[])
{
    int i, j, len, len1, len2;
    int a[MAX+10] = {0};
    int b[MAX+10] = {0};
    int c[MAX*2+10] = {0};

    len1 = strlen(num1);
    for(j = 0, i = len1-1; i >= 0; i--) //把数字字符转换为整型数
        a[j++] = num1[i]-'0';
    len2 = strlen(num2);
    for(j = 0, i = len2-1; i >= 0; i--)
        b[j++] = num2[i]-'0';

    for(i = 0; i < len2; i++)//用第二个数乘以第一个数,每次一位
    {
        for(j = 0; j < len1; j++)
        {
            c[i+j] += b[i] * a[j]; //先乘起来,后面统一进位
        }
    }

    for(i=0; i<MAX*2; i++) //循环统一处理进位问题
    {
        if(c[i]>=10)
        {
            c[i+1]+=c[i]/10;
            c[i]%=10;
        }
    }

    for(i = MAX*2; c[i]==0 && i>=0; i--); //跳过高位的0
    len = i+1; // 记录结果的长度
    for(; i>=0; i--)
        sum[i]=c[i];
    return len;
}

int main()
{
    int i, len;
    int sum[MAX*2+10] = {0}; // 存放计算的结果，低位在前，高位在后，即sum[0]是低位
    char num1[] = "123456789123456789"; // 第一个大数
    char num2[] = "123456789123456789"; // 第二个大数
    len = Multiplication(num1, num2, sum);
    // 输出结果
    printf("%s\n  *\n%s\n  =\n", num1, num2);
    for(i = len-1; i>=0; i--)
        printf("%d", sum[i]);
    printf("\n");
    return 0;
}
