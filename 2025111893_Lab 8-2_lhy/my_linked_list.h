#define TYPE_INT 0
#define TYPE_STR 1
#define TYPE_NUL -1

typedef struct Node Node;
typedef struct Input_Data Input_Data;

 //双向链表
typedef struct Node {
    Node* previous;
    Node* next;
    char* data;
} Node;
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
void list_show(Node** _list_start);
