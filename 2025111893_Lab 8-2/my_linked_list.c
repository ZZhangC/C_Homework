/*
 * 2025111893_Lab 8-2/my_linked_list.c
 * 本文件是my_linked_list.h的实现
 * Author: ZZhangC
 * Date: 15/12/2025
 */

#include "my_linked_list_general.h"
#include "my_linked_list.h"

/**********************************************************
 ***************************通用***************************
 **********************************************************/
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
    if (input == NULL)
        input = "\0";
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
    char* new_str = NULL;
    //是数字就存，不是就不存
    if (is_digit) {
        //设置数据类型
        res->flag_type = TYPE_INT;
        //获取一个数字
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
    //把字符串格式存起来
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
//从7-2抄过来的swap函数
void swap(void* ptr1, void* ptr2, unsigned int len) {
    for (int i = 0; i < len; i++) {
        *((char*)(ptr1)+i) ^= *((char*)(ptr2)+i);
        *((char*)(ptr2)+i) ^= *((char*)(ptr1)+i);
        *((char*)(ptr1)+i) ^= *((char*)(ptr2)+i);
    }
}

/**********************************************************
 ***************************链表***************************
 **********************************************************/
//初始化一个值全为0的链表
Node* node_get_new() {
    Node* new_node = (Node*)malloc(sizeof(Node));
    memset(new_node, 0, sizeof(Node));
    return new_node;
}
void* node_set_data(Node* _node, const char* _str) {
    //这里不直接让_node->data等于_str的原因是防止输入的数据不是const char*类型，而且便于销毁
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
    printf("aa");//debug
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
void list_show(void** _list_start) {
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

/**********************************************************
 ***************************菜单***************************
 **********************************************************/
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
            if (*(_menu->opt_index + i) > _index || *(_menu->opt_index + i) <= 0)
                _insert_pos = i;
            else if (i == _opt_num - 1)
                _insert_pos = _opt_num;
        }
        else if (_index <= 0) {
            if ((*(_menu->opt_index + i) <= 0 && *(_menu->opt_index + i) < _index))
                _insert_pos = i;
            else if (i == _opt_num - 1)
                _insert_pos = _opt_num;
        }
    }

    if(_insert_pos != _opt_num) {
        memcpy(_opt_index, _menu->opt_index, sizeof(int*) * _insert_pos);
        memcpy(_options, _menu->options, sizeof(char*) * _insert_pos);
        memcpy(_opt_functions, _menu->opt_functions, sizeof(assignable_func) * _insert_pos);


        *(_opt_index + _insert_pos) = _index;
        *(_options + _insert_pos) = (char*)_option;
        *(_opt_functions + _insert_pos) = _func;

        memcpy(_opt_index + _insert_pos + 1, _menu->opt_index + _insert_pos, sizeof(int*) * (_opt_num - _insert_pos));
        memcpy(_options + _insert_pos + 1, _menu->options + _insert_pos, sizeof(char*) * (_opt_num - _insert_pos));
        memcpy(_opt_functions + _insert_pos + 1, _menu->opt_functions + _insert_pos, sizeof(assignable_func) * (_opt_num - _insert_pos));
    }
    else {
        memcpy(_opt_index, _menu->opt_index, sizeof(int*) * _opt_num);
        memcpy(_options, _menu->options, sizeof(char*) * _opt_num);
        memcpy(_opt_functions, _menu->opt_functions, sizeof(assignable_func) * _opt_num);

        *(_opt_index + _opt_num) = _index;
        *(_options + _opt_num) = (char*)_option;
        *(_opt_functions + _opt_num) = _func;
    }
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
    printf("Please enter an option:\n");
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
void menu_exec(Menu* _menu, void** _backend_target) {
    while (1) {
        if (_menu->flag_end) {
            break;
        }
        menu_refresh(_menu);
        char* input = get_input();
        Input_Data* data = get_arg(input, strlen(input));
        Input_Data* data_check = get_arg(input, strlen(input));
        if (data->flag_type != TYPE_INT || data_check->flag_type != TYPE_NUL)
            continue;
        menu_call_func(_menu, data->integer, _backend_target);
        printf("Press enter to continue...\n");
        get_input();
    }
}