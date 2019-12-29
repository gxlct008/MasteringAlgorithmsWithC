#include<stdio.h>
#include<string.h>

#define N 1000    // 大数的最大位数



string mul(int *a, int b, int *c) { // b int i, tmp, carry = 0;
    for (i = N - 1; i >=0; i--) {
        tmp = a[i] * b + carry;
        c[i] = tmp % 10000;
        carry = tmp / 10000;
    }

    return c;
}


int main()
{
    int i;
    char res[];
    // int sum[MAX*2+10] = {0}; // 存放计算的结果，低位在前，高位在后，即sum[0]是低位
    char num1[] = "123456789123456789"; // 第一个大数
    char num2[] = "123456789123456789"; // 第二个大数
    res = mul(num1, num2, res);
    // 输出结果
    // printf("%s\n  *\n%s\n  =\n", num1, num2);
    // for(i = len-1; i>=0; i--)
    //     printf("%d", sum[i]);
        printf("%s", res);
    printf("\n");

    return 0;
}
