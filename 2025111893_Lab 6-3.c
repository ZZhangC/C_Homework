/*
 * 2025111893_Lab 6-3.c
 * 这题好像在哪里做过
 * Author: ZZhangC
 * Date: 24/11/2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* str = malloc(0);
    int len = 0;
    char c;
    while ((c = getchar()) != '\n') {
        char* tmp = malloc((len + 1) * sizeof(char));//啰嗦了，但是能明确意思
        memcpy(tmp, str, len);
        tmp[len] = c;
        free(str);
        str = tmp;
        len++;
    }

    char tmp_char = str[0];
    int tmp_count = 0;
    for (int i = 0; i < len; i++) {
        if (tmp_char != str[i]) {
            printf("%d%c", tmp_count, tmp_char);
            tmp_count = 0;
            tmp_char = str[i];
        }
        if (tmp_char == str[i]) {
            tmp_count++;
        }
        if (i + 1 == len){
            printf("%d%c\n", tmp_count, tmp_char);
        }
    }
    return 0;
}