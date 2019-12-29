/*
 * 问题描述： 求 n! 的二进制表示中最低位 1 的位置。
 * 例如 3！= 6，6 的二进制为 1010，所以最低位 1 的位置在倒数第二位。
 *
 * 问题分析：
 * (1) 求二进制末尾有多少个 0，0 的个数加上1就是最低位1的位置了。
 * (2) 由于是二进制，所以每次乘以 2 末尾就会产生一个 0。
 *
 * 问题转化：n! 含有多少个 2 ？
 *
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 求 n! 中能够被 2 整除的个数
 * 应用 sum = n/2 + n/(2^2) + n/(2^3) + ... 规律
 *
 * @param  n 需要计算的整数
 * @return   小于等于 n 的整数中可以被 2 整除的个数
 */
int fun1(int n) {
    int sum = 0;
    while (n != 0) {
        sum += n / 2;
        n = n / 2;
    }

    return sum;
}

/**
 * 采用位运算进行优化
 * @param  n 需要计算的整数
 * @return   小于等于 n 的整数中可以被 2 整除的个数
 */
int fun2(int n) {
    int sum = 0;
    while (n != 0) {
        n >>= 1;
        sum += n;
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

    printf("1 ~ %d 这些数中可以被 2 整除的个数计算结果如下：\n", n);

    printf("fun1 的结果为: %d\n", res1);

    printf("fun2 的结果为: %d\n", res2);

    printf("n! 的二进制表示法，最低位1的位置在倒数第 %d 位\n", res2+1);

    return 0;
}
