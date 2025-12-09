/*
 * 2025111893_Lab 7-1.c
 * Author: ZZhangC
 * Date: 07/12/2025
 */
#include <stdio.h>

//那么，test1去哪了呢……？
struct test2 {
    char a;
    float c;
    double d;
    int e;
    char f;
};

struct test3 {
    char c;
    int* p1;
    int t;
    double* p2;
};

struct S1 {
    char c1;
    int i;
};

//那么，s3又去哪了呢……？
struct S3 {
    char c2;
    struct S1 s;
    char c3;
};

struct S4 {
    char c2;
    char c1;
    int i;
    char c3;
};

int main() {
    printf("%d\n", sizeof(struct test2));
    printf("%d\n", sizeof(struct test3));
    printf("%d\n", sizeof(struct S1));
    printf("%d\n", sizeof(struct S3));
    printf("%d\n", sizeof(struct S4));
    printf("%d\n", sizeof(char));
    printf("%d\n", sizeof(int));
    printf("%d\n", sizeof(float));
    printf("%d\n", sizeof(double));
    return 0;
}