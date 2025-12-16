/*
 * 2025111893_Lab 8-2/my_linked_list.h
 * 本文件定义了链表、菜单和相关的函数
 * 实话说，如果有可能的话我想把这个文件拆成两个
 * Author: ZZhangC
 * Date: 15/12/2025
 */
#ifndef MY_LINKED_LIST

#define TYPE_INT 0
#define TYPE_STR 1
#define TYPE_NUL -1

typedef struct Node Node;
typedef struct Menu Menu;
typedef struct Input_Data Input_Data;
typedef void (*assignable_func)(Menu*, void**);

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

char* get_input();
Input_Data* get_arg(char* _buf, int len);
void swap(void* ptr1, void* ptr2, unsigned int len);

Node* node_get_new();
void* node_set_data(Node* node, const char* str);
void node_destructor(Node** _node);
int list_insert(Node** _start, int _pos, const char* _str);
int list_delete(Node** _start, const char* _str);
Node* list_find(Node* _start, const char* _str);
Node* list_find_by_index(Node* _start, int _pos);
int list_update(Node* _start, int _pos, const char* _str);
int list_swap(Node** _start, int _pos1, int _pos2);
void list_destructor(Node** _start);
void list_show(void** _list_start);

Menu* menu_init();
void menu_assign_option(Menu* _menu, int _index, const char* _option, assignable_func _func);
void menu_refresh(Menu* _menu);
void menu_call_func(Menu* _menu, int _index, void* _target);
void menu_destructor(Menu* _menu);
void menu_exec(Menu* _menu, void** _backend_target);

#define MY_LINKED_LIST
#endif