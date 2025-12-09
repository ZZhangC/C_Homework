/*
 * -README-
 * File: 2025111893_Lab 4-2.c
 * Author: ZZhangC
 * Date: 11/10/2025
 */

#include <stdio.h>
#include <math.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))

int Gcd(int a, int b);

int main() {
    int a, b;
    printf("Input a,b:\n");
    scanf("%d, %d", &a, &b);
    if (a > 0 && b > 0)
        printf("Greatest Common Divisor of %d and %d is %d\n", a, b, Gcd(a, b));
    else
        printf("Input number should be positive!\n");
    return 0;
}

int Gcd(int a, int b) {
    int m = min(a, b);
    int M = a + b - m;
    if (M % m == 0) {
        return m;
    }
    return Gcd(m, M % m);
}