/*
 * 2025111893_Lab 5-1.c
 * 对几个基础排序算法的实现
 * 默认从小到大排
 * Author: ZZhangC
 * Date: 18/11/2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//选择排序
void selection_sort(int* _arr, int _len) {
    for (int i = 0; i < _len - 1; i++) {
        for (int j = i + 1; j < _len; j++) {
            if (_arr[i] > _arr[j]) {
                _arr[i] ^= _arr[j];
                _arr[j] ^= _arr[i];
                _arr[i] ^= _arr[j];
            }
        }
    }
}

//冒泡排序
void bubble_sort(int* _arr, int _len) {
    for (int i = _len - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (_arr[j] > _arr[j + 1]) {
                _arr[j + 1] ^= _arr[j];
                _arr[j] ^= _arr[j + 1];
                _arr[j + 1] ^= _arr[j];
            }
        }
    }
}

//插入排序
void insertion_sort(int* _arr, int _len) {
    int* arr2 = (int*)malloc(_len * sizeof(int));
    arr2[0] = _arr[0];
    for (int i = 1; i < _len; i++) {
        for (int j = 0; j < i; j++) {
            if (_arr[i] < arr2[j]) {
                memmove((void*)(arr2 + j + 1), (void*)(arr2 + j), (_len - j - 1) * sizeof(int));
                arr2[j] = _arr[i];
                break;
            }
            else if (j == i - 1) {
                arr2[j + 1] = _arr[i];
            }
        }
    }
}

//快速排序（无递归版）
void quick_sort_non_recursion(int* _arr, int _len) {
    int ranges_index = 0;
    int ranges_unsorted_num = 1;
    int* ranges = (int*)malloc(2 * sizeof(int));
    *(ranges) = 0;
    *(ranges + 1) = _len;
    int begin_index = 0;
    int len = _len;
    while (ranges_index < ranges_unsorted_num) {

        begin_index = *(ranges + (2 * ranges_index));
        len = *(ranges + (2 * ranges_index) + 1);

        int mid_num = _arr[begin_index + (len - 1) / 2];
        int head = 0;
        int foot = len - 1;
        while (head < foot) {
            if (_arr[begin_index + head] <= mid_num)
                head++;
            if (_arr[begin_index + foot] >= mid_num)
                foot--;
            if (_arr[begin_index + head] > mid_num && _arr[begin_index + foot] < mid_num) {
                _arr[begin_index + head] ^= _arr[begin_index + foot];
                _arr[begin_index + foot] ^= _arr[begin_index + head];
                _arr[begin_index + head] ^= _arr[begin_index + foot];
            }
        }
        if (head != (len - 1) / 2) {
            _arr[begin_index + head] ^= _arr[begin_index + (len - 1) / 2];
            _arr[begin_index + (len - 1) / 2] ^= _arr[begin_index + head];
            _arr[begin_index + head] ^= _arr[begin_index + (len - 1) / 2];
        }
        if (head > 1) {
            int* new_ranges = (int*)malloc((ranges_unsorted_num + 1) * 2 * sizeof(int));
            memcpy(new_ranges, ranges, ranges_unsorted_num * 2 * sizeof(int));
            free(ranges);
            ranges = new_ranges;
            *(ranges + (ranges_unsorted_num * 2)) = begin_index;
            *(ranges + (ranges_unsorted_num * 2) + 1) = head;
            ranges_unsorted_num++;
        }
        if (len - foot > 1) {
            int* new_ranges = (int*)malloc((ranges_unsorted_num + 1) * 2 * sizeof(int));
            memcpy(new_ranges, ranges, ranges_unsorted_num * 2 * sizeof(int));
            free(ranges);
            ranges = new_ranges;
            *(ranges + (ranges_unsorted_num * 2)) = begin_index;
            *(ranges + (ranges_unsorted_num * 2) + 1) = head;
            ranges_unsorted_num++;
        }
        ranges_index++;
    }
}

//这个不知道为什么炸了
/*
//快速排序（有递归版）
void quick_sort_recursion(int* _arr, int _len) {
    if (_len == 1)
        return;
    int head = 0;
    int foot = _len - 1;
    int mid_num = _arr[(_len - 1) / 2];
    while (head < foot) {
        if (_arr[head] <= mid_num)
            head++;
        if (_arr[foot] >= mid_num)
            foot--;
        if (_arr[head] > mid_num && _arr[foot] < mid_num) {
            _arr[head] ^= _arr[foot];
            _arr[foot] ^= _arr[head];
            _arr[head] ^= _arr[foot];
        }
    }
    if (head != (_len - 1) / 2) {
        _arr[head] ^= _arr[(_len - 1) / 2];
        _arr[(_len - 1) / 2] ^= _arr[head];
        _arr[head] ^= _arr[(_len - 1) / 2];
    }
    quick_sort_recursion(_arr, head);
    quick_sort_recursion(_arr + foot, _len - foot);
    return;
}
*/

int main() {
    void (*sort_algo[])(int*, int) = { selection_sort, bubble_sort, insertion_sort, quick_sort_non_recursion };
    for (int i = 0; i < 4; i++) {
        int arr[] = { 85, 60, 73, 84, 55, 70, 65 };
        int len = sizeof(arr) / sizeof(arr[0]);

        printf("Before Sort: ");
        for (int i = 0; i < len; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        sort_algo[i](arr, len);

        printf("After Sort: ");
        for (int i = 0; i < len; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    return 0;
}