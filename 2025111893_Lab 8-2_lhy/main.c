#include "my_linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_data(Node** _list_start) {
    printf("Input the index and data you want to insert:\n");
    char* input = get_input();
    Input_Data* pos = get_arg(input, strlen(input));
    Input_Data* data = get_arg(input, strlen(input));
    int status = list_insert((Node**)_list_start, pos->integer, data->string);
    if (status == 0)
        printf("Data added.\n");
    else
        printf("Error\n");
    list_show(_list_start);
}

void delete_data(Node** _list_start) {
    printf("Input the data you want to delete:\n");
    char* input = get_input();
    Input_Data* data = get_arg(input, strlen(input));
    int status = list_delete((Node**)_list_start, data->string);
    if(status == 0)
        printf("This data has been deleted successfully.\n");
    else
        printf("This data is not in the list.\n");
    list_show(_list_start);
}

void find_data(Node** _list_start) {
    printf("Input the data you want to find:\n");
    char* input = get_input();
    Input_Data* data = get_arg(input, strlen(input));
    Node* res = list_find(*_list_start, data->string);
    if (res != NULL)
        printf("Data found\n");
    else
        printf("Data not found.");
}

void update_data(Node** _list_start) {
    printf("Input the index and data you want to update:\n");
    char* input = get_input();
    Input_Data* pos = get_arg(input, strlen(input));
    Input_Data* data = get_arg(input, strlen(input));
    int status = list_update(*_list_start, pos->integer, data->string);
    if(status == 0)
        printf("This data has been updated successfully.\n");
    else
        printf("Error\n");
    list_show(_list_start);
}

void swap_data(Node** _list_start) {
    int status = 1;
    int i = 0;
    Node* i2 = *_list_start;
    while (1) {
        if (i2->next != NULL) {
            status = list_swap((Node**)_list_start, i, i + 1);
            if (i2->next->next != NULL) {
                i2 = i2->next->next;
                i += 2;
            }
            else {
                break;
            }
        }
        else {
            break;
        }
    }
    if(status == 0)
        printf("This data has been swapped successfully.\n");
    else
        printf("Error\n");
    list_show(_list_start);
}

void quit(Node** _list_start) {
    list_destructor((Node**)_list_start);
}

int main() {
    Node* start_node = NULL;
    Node** list_start = &start_node;
    int idx[6] = {1, 2, 3, 4, 5, 0};
    const char* options[6] = {"Insert", "Delete", "Find", "Update", "Swap", "Quit"};
    int flag_end = 0;
    while (1) {
        if (flag_end) {
            break;
        }
        for (int i = 0; i < 6; i++) {
            printf("%2d.%s\n", idx[i], options[i]);
        }
        printf("Please enter an option:\n");
        char* input = get_input();
        Input_Data* data = get_arg(input, strlen(input));
        Input_Data* data_check = get_arg(input, strlen(input));
        if (data->flag_type != TYPE_INT || data_check->flag_type != TYPE_NUL)
            continue;
        switch (data->integer)
        {
        case 0:
            flag_end = 1;
            list_destructor(list_start);
            break;
        case 1:
            insert_data(list_start);
            break;
        case 2:
            delete_data(list_start);
            break;
        case 3:
            find_data(list_start);
            break;
        case 4:
            update_data(list_start);
            break;
        case 5:
            swap_data(list_start);
            break;
        default:
            break;
        }
    }
    return 0;
}
