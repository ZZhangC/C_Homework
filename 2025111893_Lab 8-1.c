/*
 * 2025111893_Lab 8-1.c
 * 使用get_new_node()函数获取新节点而不是直接malloc
 * 这有利于内存安全
 * Author: ZZhangC
 * Date: 15/12/2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node* next;
    char* data;
} Node;

Node* get_new_node() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    memset(new_node, 0, sizeof(Node));
    return new_node;
}

void append_empty(Node* start) {
    Node* new_node = get_new_node();
    Node* chain = start;
    while (chain->next != NULL) {
        chain = chain->next;
    }
    chain->next = new_node;
}

void append_existing(Node* start, Node* node) {
    Node* chain = start;
    while (chain->next != NULL) {
        chain = chain->next;
    }
    chain->next = node;
}

void set_data(Node* node, const char* str) {
    free(node->data);
    char* data = NULL;
    if (strlen(str) > 50) {
        data = malloc(51);
        memcpy(data, str, 50);
        data[50] = '\0';
    }
    else {
        data = malloc(strlen(str) + 1);
        memcpy(data, str, strlen(str));
        data[strlen(str)] = '\0';
    }
    node->data = data;
}

char* get_input() {
    char* input = NULL;
    int len = 0;
    char c = getchar();
    while (c != '\n' && c != '\r' && c != EOF) {
        char* new_input = malloc(len + 2);
        new_input[len] = c;
        new_input[len + 1] = '\0';
        memcpy(new_input, input, len);
        free(input);
        input = new_input;
        len++;
        c = getchar();
    }
    return input;
}

int main() {
    Node* start = get_new_node();
    char* input0 = get_input();
    if (input0 == NULL) {
        printf("[Error]Empty input or memory running out.\n");
        return -1;
    }
    set_data(start, input0);
    if(start->data == NULL) {
        printf("[Error]An error occurred at %x when setting data. Check if your memory is running out.\n", start);
        return -1;
    }
    while (1) {
        char* input = get_input();
        if (input == NULL) {
            printf("[Error]Empty input or memory running out.\n");
            return -1;
        }
        if (strlen(input) == 6) {
            int end_flag = 1;
            for (int i = 0; i < 6; i++) {
                if (input[i] != '*')
                    end_flag = 0;
            }
            if (end_flag)
                break;    
        }
        Node* new_node = get_new_node();
        set_data(new_node, input);
        if(new_node->data == NULL) {
            printf("[Error]An error occurred at %x when setting data. Check if your memory is running out.\n", new_node);
            return -1;
        }
        append_existing(start, new_node);
    }

    Node* iterator;
    //Task 1
    int res_len = 0, res_pos = 0, index = 0;
    iterator = start;
    while (iterator != NULL) {
        if (strlen(iterator->data) > res_len) {
            res_len = strlen(iterator->data);
            res_pos = index;
        }
        iterator = iterator->next;
        index++;
    }
    iterator = start;
    for (int i = 0; i < res_pos; i++) {
        iterator = iterator->next;
    }
    printf("%s\n", iterator->data);

    //Task 2
    FILE* file = fopen("Input.txt", "a");
    iterator = start;
    while (iterator != NULL) {
        int status = fputs(iterator->data, file);
        status = fputs("\n", file);
        if (status == EOF) {
            printf("[Error]An error occurred when writing to Input.txt.\n");
            return -1;
        }
        iterator = iterator->next;
    }
    int status = fclose(file);
    if (status == EOF) {
        printf("[Error]An error occurred when closing Input.txt.\n");
        return -1;
    }
    
    return 0;
}
