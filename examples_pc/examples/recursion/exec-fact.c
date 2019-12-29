/* 用递归方式计算阶乘的函数实现 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 用基本递归方式计算阶乘的函数实现
 *
 * @param  n 需要计算阶乘的目标数
 * @return   返回计算结果
 */
int fact_basic(int n) {

   if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (n == 1) {
        return 1;
    } else {
        return n * fact_basic(n - 1);
    }
}


/**
 * 用尾递归方式计算阶乘的函数实现
 *
 * @param  n 需要计算阶乘的目标数
 * @param  1 因子
 * @return   返回计算结果
 */
int fact_tail(int n, int a) {

    if (n < 0) {
        return 0;
    } else if (n == 0) {
        return 1;
    } else if (n == 1) {
        return a;
    } else {
        return fact_tail(n-1, n*a);
    }
}


int main(int argc, char **argv) {
    int n, a = 1, res_b = 0, res_t = 0;

    printf("请输入要计算的整数:\n");
    scanf("%d", &n);

    // 1.调用基本递归阶乘函数
    res_b = fact_basic(n);

    // 2.调用尾递归阶乘函数
    res_t = fact_tail(n, a);

    printf("基本递归方式计算 %d 的阶乘: %d\n", n, res_b);

    printf("尾递归方式计算 %d 的阶乘: %d\n", n, res_t);

    return 0;
}
