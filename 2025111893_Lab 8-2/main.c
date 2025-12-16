#include "my_linked_list.h"
#include "my_linked_list_general.h"



void insert_data(Menu* _menu, void** _list_start) {
    printf("Input the index and data you want to insert:\n");
    char* input = get_input();
    Input_Data* pos = get_arg(input, strlen(input));
    if (pos->flag_type != TYPE_INT) {
        printf("An error occurred, aborting...\n");
        return;
    }
    Input_Data* data = get_arg(input, strlen(input));
    if (data->flag_type == TYPE_NUL) {
        printf("An error occurred, aborting...\n");
        return;
    }
    int status = list_insert((Node**)_list_start, pos->integer, data->string);
    if (status == 0)
        printf("Data added.\n");
    else
        printf("An error occurred, aborting...\n");
    list_show(_list_start);
}

void delete_data(Menu* _menu, void** _list_start) {
    printf("Input the data you want to delete:\n");
    char* input = get_input();
    Input_Data* data = get_arg(input, strlen(input));
    if (data->flag_type == TYPE_NUL) {
        printf("An error occurred, aborting...\n");
        return;
    }
    int status = list_delete((Node**)_list_start, data->string);
    if(status == 0)
        printf("This data has been deleted successfully.\n");
    else
        printf("This data is not in the list.\n");
    list_show(_list_start);
}

void find_data(Menu* _menu, void** _list_start) {
    printf("Input the data you want to find:\n");
    char* input = get_input();
    Input_Data* data = get_arg(input, strlen(input));
    if (data->flag_type == TYPE_NUL) {
        printf("An error occurred, aborting...\n");
        return;
    }
    Node* res = list_find(*_list_start, data->string);
    if (res != NULL) {
        printf("Data found at: ");
        printf("(start)");
        if (res->previous != NULL) {
            if(res->previous->previous != NULL)
                printf("...%s->", res->previous->data);
            else
                printf("%s->", res->previous->data);
        }
        printf("%s", res->data);
        if (res->next != NULL) {
            if(res->next->next != NULL)
                printf("->%s...", res->next->data);
            else
                printf("->%s", res->next->data);
        }
        printf("(end)\n");
    }
    else
        printf("Data not found.");
}

void update_data(Menu* _menu, void** _list_start) {
    printf("Input the index and data you want to update:\n");
    char* input = get_input();
    Input_Data* pos = get_arg(input, strlen(input));
    if (pos->flag_type != TYPE_INT) {
        printf("An error occurred, aborting...\n");
        return;
    }
    Input_Data* data = get_arg(input, strlen(input));
    if (data->flag_type == TYPE_NUL) {
        printf("An error occurred, aborting...\n");
        return;
    }
    int status = list_update(*_list_start, pos->integer, data->string);
    if(status == 0)
        printf("This data has been updated successfully.\n");
    else
        printf("An error occurred, aborting...\n");
    list_show(_list_start);
}

void swap_data(Menu* _menu, void** _list_start) {
    printf("Input 2 index you want to swap:\n");
    char* input = get_input();
    Input_Data* pos1 = get_arg(input, strlen(input));
    if (pos1->flag_type != TYPE_INT) {
        printf("An error occurred, aborting...\n");
        return;
    }
    Input_Data* pos2 = get_arg(input, strlen(input));
    if (pos2->flag_type != TYPE_INT) {
        printf("An error occurred, aborting...\n");
        return;
    }
    int status = list_swap((Node**)_list_start, pos1->integer, pos2->integer);
    if(status == 0)
        printf("This data has been swapped successfully.\n");
    else
        printf("An error occurred, aborting...\n");
    list_show(_list_start);
}

void quit(Menu* _menu, void** _list_start) {
    menu_destructor(_menu);
    list_destructor((Node**)_list_start);
}

int main() {
    Menu* menu = menu_init();
    Node* start_node = NULL;
    Node** list_start = &start_node;
    menu_assign_option(menu, 0, "Quit", &quit);
    menu_assign_option(menu, 1, "Insert", &insert_data);
    menu_assign_option(menu, 2, "Delete", &delete_data);
    menu_assign_option(menu, 3, "Find", &find_data);
    menu_assign_option(menu, 4, "Update", &update_data);
    menu_assign_option(menu, 5, "Swap", &swap_data);
    menu_exec(menu, (void**)list_start);
    menu = NULL;
    return 0;
}
