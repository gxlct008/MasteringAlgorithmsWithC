/* 用尾递归方式计算阶乘的函数实现 */

#include <stdio.h>
#include <stdlib.h>

#include "../../source/facttail.c"

int main(int argc, char **argv) {
    int n, a = 1, res = 0;

    printf("请输入要计算的整数:\n");
    scanf("%d", &n);

    // 调用尾递归阶乘函数
    res = facttail(n, a);

    printf("尾递归方式计算 %d 的阶乘: %d\n", n, res);

    return 0;
}
