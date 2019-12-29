/* 给定一个整数 n，求 1~n 这些数中可以被 5 整除的个数 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 求 1~n 这 n 个数中能够被 5 整除的个数
 *
 * @param  n 需要计算的整数
 * @return   小于等于 n 的整数中可以被 5 整除的个数
 */
int fun1(int n) {
    int i, j, sum = 0;
    for (i = 1; i <= n; i++)
    {
        j = i;
        while ((j % 5) == 0) {
            sum++;
            j = j / 5;
        }
    }

    return sum;
}

/**
 * 根据 sum = n/5 + n/(5^2) + n/(5^3) + ... 规律给出的优化方案
 *
 * @param  n 需要计算的整数
 * @return   小于等于 n 的整数中可以被 5 整除的个数
 */
int fun2(int n) {
    int sum = 0;
    while (n != 0) {
        sum += n / 5;
        n = n / 5;
    }

    return sum;
}

int main() {
    int n, res1 = 0, res2 = 0;

    printf("请输入要计算的整数:\n");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("n必须为大于 1 的整除\n");
        return 1;
    }

    res1 = fun1(n);
    res2 = fun2(n);

    printf("1 ~ %d 这些数中可以被 5 整除的个数计算结果如下：\n", n);

    printf("fun1 的结果为: %d\n", res1);

    printf("fun2 的结果为: %d\n", res2);

    return 0;
}
