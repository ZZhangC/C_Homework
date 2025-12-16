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
typedef void (*assignable_func)(Menu*, void*);

char* get_input();
Input_Data* get_arg(char* _buf, int len);
void swap(void* ptr1, void* ptr2, unsigned int len);

Node* node_get_new();
void* node_set_data(Node* node, const char* str);
int list_insert(Node* _start, int _pos, const char* _str);
int list_delete(Node* _start, const char* _str);
int list_find(Node* _start, const char* _str);
int list_update(Node* _start, int _pos, const char* _str);
int list_swap(Node* _start, int _pos1, int _pos2);
int list_destructor(Node* _start);

Menu* menu_init();
void menu_assign_option(Menu* _menu, int _index, const char* _option, assignable_func _func);
void menu_refresh(Menu* _menu);
void menu_call_func(Menu* _menu, int _index, void* _target);
void menu_destructor(Menu* _menu);
void menu_exec(Menu* _menu, void* _backend_target);

#define MY_LINKED_LIST
#endif