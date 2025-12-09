/*
 * -README-
 * File: 2025111893_Lab 4-3.c
 * Author: ZZhangC
 * Date: 11/10/2025
 */

#include <stdio.h>

int getPeachNumber(int n) {
    int tmp = n;
    int i = 10;
    while (1) {
        if (tmp == 1)
            break;
        else {
            i--;
            tmp /= 2;
            tmp--;
        }
    }
    printf("第%d天所剩桃子%d个\n", i, n);
    if (i == 1) {
        return n;
    }
    else {
        return getPeachNumber(2 * (n + 1));
    }
}

int main() {
    int num = getPeachNumber(1);
    printf("猴子第一天摘了:%d个桃子。\n", num);
    return 0;
}