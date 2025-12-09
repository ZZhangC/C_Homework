/* 
 * 2025111893_Lab 6-1.c
 * 实现了泛型的功能
 * Author: ZZhangC
 * Date: 24/11/2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//For task 2
void swap(void* _pa, void* _pb, int _size) {
    void* pc = (void*)malloc(_size);
    //这里假定内存没有重叠，这对一般的情况适用
    memcpy(pc, _pb, _size);
    memcpy(_pb, _pa, _size);
    memcpy(_pa, pc, _size);
    free(pc);
}

int main() {
    int a = 0, b = 1;
    int* pa = &a;
    int* pb = &b;
    printf("%d %d\n", *pa, *pb);
    //task1
    //假设a和b不能被通过变量名访问
    void* tmp;
    tmp = (void*)pb;//可以看作强制类型转换
    pb = pa;
    pa = (int*)tmp;
    printf("%d %d\n", *pa, *pb);
    //task2
    swap(pa, pb, sizeof(int));
    printf("%d %d\n", *pa, *pb);
    return 0;
}