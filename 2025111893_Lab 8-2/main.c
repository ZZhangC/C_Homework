#include "my_linked_list.h"
#include "my_linked_list_general.h"

void func1(Menu* _menu, void* _node) {
    printf("func1 called");
    get_input();
}

void quit(Menu* _menu, void* _node) {
    menu_destructor(_menu);
}

int main() {
    Menu* menu = menu_init();
    Node* node = node_get_new();
    menu_assign_option(menu, 0, "退出", &quit);
    menu_assign_option(menu, 1, "func1", &func1);
    menu_exec(menu, node);
    return 0;
}
