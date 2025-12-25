#include "my_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    if (input == NULL)
        input = "\0";
    return input;
}

Input_Data* get_arg(char* _buf, int len) {
    Input_Data* res = (Input_Data*)malloc(sizeof(Input_Data));
    memset(res, 0, sizeof(Input_Data));
    res->flag_type = TYPE_NUL;
    int index = 0;

    while (_buf[index] == ' ' && index < len) {
        index++;
    }

    if (index >= len) {
        return res;
    }

    int is_digit = 1;
    int tmp_index = index;
    while (_buf[tmp_index] != ' ' && tmp_index < len) {
        if(tmp_index == index) {
            if ((_buf[index] < '0' || _buf[index] > '9') && _buf[index] != '-') {
                is_digit = 0;
                break;
            }
        }
        else if (_buf[tmp_index] < '0' || _buf[tmp_index] > '9') {
            is_digit = 0;
            break;
        }
        tmp_index++;
    }

    char* new_str = NULL;
    if (is_digit) {
        res->flag_type = TYPE_INT;
        tmp_index = index;
        int sign = _buf[tmp_index] == '-' ? -1 : 1;
        while (_buf[tmp_index] >= '0' && _buf[tmp_index] <= '9') {
            res->integer *= 10;
            res->integer += (int)(_buf[tmp_index]) - (int)'0';
            tmp_index++;
        }
        res->integer *= sign;
    }
    else {
        res->flag_type = TYPE_STR;
    }
    while (_buf[index] != ' ' && index < len) {
        new_str = (char*)malloc(res->str_len + 1);
        memcpy(new_str, res->string, res->str_len);
        new_str[res->str_len] = _buf[index];
        free(res->string);
        res->string = new_str;
        _buf[index] = ' ';
        index++;
        res->str_len++;
    }
    new_str = (char*)malloc(res->str_len + 1);
    memcpy(new_str, res->string, res->str_len);
    new_str[res->str_len] = '\0';
    free(res->string);
    res->string = new_str;

    return res;
}

void swap(void* ptr1, void* ptr2, unsigned int len) {
    for (int i = 0; i < len; i++) {
        *((char*)(ptr1)+i) ^= *((char*)(ptr2)+i);
        *((char*)(ptr2)+i) ^= *((char*)(ptr1)+i);
        *((char*)(ptr1)+i) ^= *((char*)(ptr2)+i);
    }
}


Node* node_get_new() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    memset(new_node, 0, sizeof(Node));
    return new_node;
}
void* node_set_data(Node* _node, const char* _str) {
    free(_node->data);
    _node->data = malloc(strlen(_str) + 1);
    memcpy(_node->data, _str, strlen(_str));
    _node->data[strlen(_str)] = '\0';
    return _node->data;
}
void node_destructor(Node** _node) {
    free((*_node)->data);
    free(*_node);
}
int list_insert(Node** _start, int _pos, const char* _str) {
    if (_pos == 0) {
        Node* new_node = node_get_new();
        node_set_data(new_node, _str);
        new_node->next = *_start;
        if (*_start != NULL) {
            (*_start)->previous = new_node;
        }
        *_start = new_node;
        return 0;
    }
    Node* iterator = list_find_by_index(*_start, _pos - 1);
    if (iterator == NULL)
        return -1;
    Node* new_node = node_get_new();
    node_set_data(new_node, _str);
    if (iterator->next == NULL) {
        iterator->next = new_node;
        new_node->previous = iterator;
    }
    else {
        Node* tmp = iterator->next;
        iterator->next = new_node;
        new_node->previous = iterator;
        new_node->next = tmp;
        tmp->previous = new_node;
    }
    return 0;
}
int list_delete(Node** _start, const char* _str) {
    Node* iterator = list_find(*_start, _str);
    if (iterator == NULL)
        return -1;
    if (iterator->previous == NULL) {
        if(iterator->next != NULL) {
            *_start = iterator->next;
            (*_start)->previous = NULL;
        }
        else
            *_start = NULL;
        node_destructor(&iterator);
        iterator = NULL;
    }
    else {
        iterator->previous->next = iterator->next;
        if (iterator->next != NULL)
            iterator->next->previous = iterator->previous;
        node_destructor(&iterator);
        iterator = NULL;
    }
    return 0;
}
Node* list_find(Node* _start, const char* _str) {
    Node* iterator = _start;
    if (iterator == NULL)
        return NULL;
    while (iterator != NULL) {
        if(strlen(_str) != strlen(iterator->data)) {
            iterator = iterator->next;
            continue;
        }
            
        for (int i = 0; i < strlen(_str); i++) {
            if ((iterator->data)[i] != _str[i]) {
                iterator = iterator->next;
                continue;
            }
        }
        break;
    }
    return iterator;
}
Node* list_find_by_index(Node* _start, int _pos) {
    Node* iterator = _start;
    if (iterator == NULL)
        return NULL;
    for (int i = 0; i < _pos; i++) {
        if (iterator != NULL)
            iterator = iterator->next;
    }
    return iterator;
}
int list_update(Node* _start, int _pos, const char* _str) {
    Node* iterator = list_find_by_index(_start, _pos);
    if (iterator == NULL)
        return -1;
    void* data = node_set_data(iterator, _str);
    if(data == NULL)
        return -1;
    return 0;
}
int list_swap(Node** _start, int _pos1, int _pos2) {
    Node* iterator1 = list_find_by_index(*_start, _pos1);
    Node* iterator2 = list_find_by_index(*_start, _pos2);
    if (iterator1 == NULL || iterator2 == NULL)
        return -1;
    swap(&(iterator1->data), &(iterator2->data), sizeof(char*));
    return 0;
}
void list_destructor(Node** _start) {
    Node* iterator = *_start;
    if (iterator == NULL)
        return;
    while (iterator->next != NULL) {
        iterator = iterator->next;
    }
    while (iterator->previous != NULL) {
        iterator = iterator->previous;
        node_destructor(&(iterator->next));
    }
    node_destructor(&iterator);
    iterator = NULL;
}
void list_show(Node** _list_start) {
    printf("Now the list is: ");
    Node* iterator = *_list_start;
    while (iterator != NULL) {
        printf("%s", iterator->data);
        if (iterator->next != NULL)
            printf("->");
        iterator = iterator->next;
    }
    printf("\n");
}
