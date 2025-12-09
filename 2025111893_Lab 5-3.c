/*
 * 2025111893_Lab 5-3.c
 * 对几个基础排序算法的实现+计时
 * 默认从小到大排
 * Author: ZZhangC
 * Date: 18/11/2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//归并排序
void merge_sort(int* _arr, int _len) {
    printf("merge\n");
    if (_len <= 2) {
        if (_len == 2) {
            if (_arr[0] > _arr[1]) {
                _arr[0] ^= _arr[1];
                _arr[1] ^= _arr[0];
                _arr[0] ^= _arr[1];
            }
        }
        return;
    }
    merge_sort(_arr, _len / 2);
    merge_sort(_arr + _len / 2, _len - _len / 2);
    int* arr_a = (int*)malloc((_len / 2) * sizeof(int));
    memcpy(arr_a, _arr, (_len / 2) * sizeof(int));
    int* arr_b = (int*)malloc((_len - _len / 2) * sizeof(int));
    memcpy(arr_b, _arr + _len / 2, (_len - _len / 2) * sizeof(int));
    int arr_a_len = _len / 2;
    int arr_b_len = _len - _len / 2;
    int i = 0;
    while (arr_a_len + arr_b_len > 0) {
        if (arr_b_len > 0) {
            if (arr_a_len != 0 && *(arr_a) < *(arr_b)) {
                _arr[i] = *(arr_a);
                int* new_arr = (int*)malloc((arr_a_len - 1) * sizeof(int));
                memcpy(new_arr, arr_a + 1, (arr_a_len - 1) * sizeof(int));
                free(arr_a);
                arr_a = new_arr;
                arr_a_len--;
                i++;
            }
        }
        else {
            _arr[i] = *(arr_a);
            int* new_arr = (int*)malloc((arr_a_len - 1) * sizeof(int));
            memcpy(new_arr, arr_a + 1, (arr_a_len - 1) * sizeof(int));
            free(arr_a);
            arr_a = new_arr;
            arr_a_len--;
            i++;
        }
        if (arr_a_len > 0) {
            if (arr_b_len != 0 && *(arr_b) < *(arr_a)) {
                _arr[i] = *(arr_b);
                int* new_arr = (int*)malloc((arr_b_len - 1) * sizeof(int));
                memcpy(new_arr, arr_b + 1, (arr_b_len - 1) * sizeof(int));
                free(arr_b);
                arr_b = new_arr;
                arr_b_len--;
                i++;
            }
        }
        else {
            _arr[i] = *(arr_b);
            int* new_arr = (int*)malloc((arr_b_len - 1) * sizeof(int));
            memcpy(new_arr, arr_b + 1, (arr_b_len - 1) * sizeof(int));
            free(arr_b);
            arr_b = new_arr;
            arr_b_len--;
            i++;
        }
    }
    free(arr_a);
    free(arr_b);
}

//堆排序
void heap_sort(int* _arr, int _len) {
    for (int i = _len / 2 - 1; i >= 0; i--) {
        int index_parent = i;
        int index_child = index_parent * 2 + 1;
        while (index_child <= _len - 1) {
            if (index_child + 1 <= _len - 1 && _arr[index_child] < _arr[index_child + 1])
                index_child++;
            if (_arr[index_parent] > _arr[index_child])
                break;
            else {
                _arr[index_parent] ^= _arr[index_child];
                _arr[index_child] ^= _arr[index_parent];
                _arr[index_parent] ^= _arr[index_child];
                index_parent = index_child;
                index_child = index_parent * 2 + 1;
            }
        }
    }
    for (int i = _len - 1; i > 0; i--) {
        _arr[0] ^= _arr[i];
        _arr[i] ^= _arr[0];
        _arr[0] ^= _arr[i];
        int index_parent = 0;
        int index_child = index_parent * 2 + 1;
        while (index_child <= i - 1) {
            if (index_child + 1 <= i - 1 && _arr[index_child] < _arr[index_child + 1])
                index_child++;
            if (_arr[index_parent] > _arr[index_child])
                break;
            else {
                _arr[index_parent] ^= _arr[index_child];
                _arr[index_child] ^= _arr[index_parent];
                _arr[index_parent] ^= _arr[index_child];
                index_parent = index_child;
                index_child = index_parent * 2 + 1;
            }
        }
    }
}

int main() {
    //生成100000-200000个200000以内非负整数
    srand(time(NULL));
    int num = 100000 + (rand() % 100000);
    int* arr = NULL;
    int len = 0;
    for (int i = 0; i < num; i++) {
        int* new_arr = (int*)malloc((len + 1) * sizeof(int));
        if (arr != NULL) {
            memcpy(new_arr, arr, len * sizeof(int));
            free(arr);
        }
        arr = new_arr;
        *(arr + len) = rand() % 200000;
        len++;
    }

    void (*sort_algo[])(int*, int) = { heap_sort, merge_sort };
    const char* name[] = { "heapSort", "mergeSort" };

    //计时
    clock_t start_t, end_t;

    for (int i = 0; i < 2; i++) {

        start_t = clock();

        sort_algo[i](arr, len);

        end_t = clock();

        printf("%s uses %d clocks!\n", name[i], end_t - start_t);
    }
    return 0;
}