/*
 * 2025111893_Lab 8-2/my_linked_list.c
 * 本文件是my_linked_list.h的实现
 * Author: ZZhangC
 * Date: 15/12/2025
 */

#include "my_linked_list_general.h"
#include "my_linked_list.h"

 /***************************结构***************************/
 //双向链表
typedef struct Node {
    Node* previous;
    Node* next;
    char* data;
} Node;
//菜单
typedef struct Menu {
    int* opt_index;
    char** options;
    assignable_func* opt_functions;

    int opt_num;
    int flag_end;
} Menu;
//输入数据
typedef struct Input_Data {
    int flag_type;
    int integer;
    char* string;
    int str_len;
} Input_Data;

/***************************通用***************************/
//从8-1抄过来的获取输入函数
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
//从7-3抄过来再修改的输入处理函数
Input_Data* get_arg(char* _buf, int len) {
    Input_Data* res = (Input_Data*)malloc(sizeof(Input_Data));
    memset(res, 0, sizeof(Input_Data));
    res->flag_type = TYPE_NUL;
    int index = 0;

    //忽略空白字符
    while (_buf[index] == ' ' && index < len) {
        index++;
    }

    //越界检查
    if (index >= len) {
        return res;
    }

    //看参数是否是数字
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

    //赋值
    switch (is_digit) {
    case 1:
        //设置数据类型
        res->flag_type = TYPE_INT;
        //获取一个数字
        int sign = _buf[index] == '-' ? -1 : 1;
        while (_buf[index] >= '0' && _buf[index] <= '9') {
            res->integer *= 10;
            res->integer += (int)(_buf[index]) - (int)'0';
            _buf[index] = ' ';
            index++;
        }
        res->integer *= sign;
        break;

    case 0:
        //设置数据类型
        res->flag_type = TYPE_STR;
        //获取一个字符串
        while (_buf[index] >= '0' && _buf[index] <= '9') {
            char* new_str = (char*)malloc(res->str_len + 1);
            memcpy(new_str, res->string, res->str_len);
            new_str[res->str_len] = _buf[index];
            free(res->string);
            res->string = new_str;
            index++;
            res->str_len++;
        }
        break;
    }

    return res;
}
//从7-2抄过来的swap函数
void swap(void* ptr1, void* ptr2, unsigned int len) {
    for (int i = 0; i < len; i++) {
        *((char*)(ptr1)+i) ^= *((char*)(ptr2)+i);
        *((char*)(ptr2)+i) ^= *((char*)(ptr1)+i);
        *((char*)(ptr1)+i) ^= *((char*)(ptr2)+i);
    }
}

/*************************链表部分*************************/
//初始化一个值全为0的链表
Node* node_get_new() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    memset(new_node, 0, sizeof(Node));
    return new_node;
}

/*************************菜单部分*************************/
//初始化一个值全为0的菜单
Menu* menu_init() {
    Menu* new_menu = (Menu*)malloc(sizeof(Menu));
    memset(new_menu, 0, sizeof(Menu));
    return new_menu;
}
//注册能被菜单调用的函数
void menu_assign_option(Menu* _menu, int _index, const char* _option, assignable_func _func) {
    int* _opt_index = NULL;
    char** _options = NULL;
    assignable_func* _opt_functions = NULL;
    int _opt_num = _menu->opt_num;

    _opt_index = (int*)malloc(sizeof(int*) * (_opt_num + 1));
    _options = (char**)malloc(sizeof(char*) * (_opt_num + 1));
    _opt_functions = (void*)malloc(sizeof(assignable_func) * (_opt_num + 1));

    int _insert_pos = 0;

    for (int i = 0; i < _opt_num; i++) {
        if (_index > 0) {
            if (*(_menu->opt_index + i) > _index)
                _insert_pos = i;
        }
        else if (_index <= 0) {
            if ((*(_menu->opt_index + i) <= 0 && *(_menu->opt_index + i) < _index) || *(_menu->opt_index + i) > 0)
                _insert_pos = i;
        }
    }

    memcpy(_opt_index, _menu->opt_index, sizeof(int*) * _insert_pos);
    memcpy(_options, _menu->options, sizeof(char*) * _insert_pos);
    memcpy(_opt_functions, _menu->opt_functions, sizeof(assignable_func) * _insert_pos);


    *(_opt_index + _insert_pos) = _index;
    *(_options + _insert_pos) = (char*)_option;
    *(_opt_functions + _insert_pos) = _func;

    memcpy(_opt_index + _insert_pos + 1, _menu->opt_index + _insert_pos, sizeof(int*) * (_opt_num - _insert_pos));
    memcpy(_options + _insert_pos + 1, _menu->options + _insert_pos, sizeof(char*) * (_opt_num - _insert_pos));
    memcpy(_opt_functions + _insert_pos + 1, _menu->opt_functions + _insert_pos, sizeof(assignable_func) * (_opt_num - _insert_pos));

    free(_menu->opt_index);
    free(_menu->options);
    free(_menu->opt_functions);

    _menu->opt_index = _opt_index;
    _menu->options = _options;
    _menu->opt_functions = _opt_functions;
    _menu->opt_num = _opt_num + 1;
}
//刷新菜单
void menu_refresh(Menu* _menu) {
    printf("\x1B[2J\x1B[H\n");
    for (int i = 0; i < _menu->opt_num; i++) {
        printf("%2d.%s\n", *(_menu->opt_index + i), *(_menu->options + i));
        if (*(_menu->opt_index + i) > 0 && *(_menu->opt_index + i + 1) <= 0)
            printf("\n");
        if (*(_menu->opt_index + i) == 0)
            printf("\n");
    }
    printf("请输入你的选择：\n");
}
//调用指定的函数
void menu_call_func(Menu* _menu, int _index, void* _target) {
    for (int i = 0; i < _menu->opt_num; i++) {
        if (*(_menu->opt_index + i) == _index) {
            (*(_menu->opt_functions + i))(_menu, _target);
        }
    }
}
//菜单的析构函数（不知道怎么叫了就这么叫吧）
void menu_destructor(Menu* _menu) {
    //理论上字符串会自己在程序结束之后释放，所以这里只释放指向字符串的指针
    free(_menu->opt_index);
    free(_menu->options);
    free(_menu->opt_functions);
    _menu->opt_num = 0;//为了防患于未然
    _menu->flag_end = 1;
}
//使用该函数进入主循环
void menu_exec(Menu* _menu, void* _backend_target) {
    while (1) {
        if (_menu->flag_end) {
            break;
        }
        menu_refresh(_menu);
        char* input = get_input();
        Input_Data* data = get_arg(input, strlen(input));
        if (data->flag_type != TYPE_INT)
            continue;
        menu_call_func(_menu, data->integer, _backend_target);
    }
}