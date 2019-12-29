/* 用递归方式计算阶乘的函数实现 */

#include <stdio.h>
#include <stdlib.h>

#include "../../source/fact.c"

int main(int argc, char **argv) {
    int n = 4, res = 0;

    // 调用阶乘函数
    res = fact(n);

    printf("普通递归方式计算 4 的阶乘: %d\n", res);

    return 0;
}
