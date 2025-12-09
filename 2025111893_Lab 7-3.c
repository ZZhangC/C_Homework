/*
 * 2025111893_Lab 7-3.c
 * Author: ZZhangC
 * Date: 07/12/2025
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Event {
    int begin_hour : 8;
    int end_hour : 8;
} Event;

typedef struct Event_Status {
    Event event;
    int index : 7;
    int flag_can_be_arranged : 1;
} Event_Status;

int get_num_abs(char* _buf, int len) {
    int num = 0;
    int index = 0;

    //忽略非数字字符
    while ((_buf[index] < '0' || _buf[index] > '9') && index < len) {
        index++;
    }

    //越界检查
    if (index >= len) {
        return -1;
    }

    //获取一个数字
    while (_buf[index] >= '0' && _buf[index] <= '9') {
        num *= 10;
        num += (int)(_buf[index]) - (int)'0';
        _buf[index] = ' ';
        index++;
    }
    return num;
}

void swap(void* ptr1, void* ptr2, unsigned int len) {
    for (int i = 0; i < len; i++) {
        *((char*)(ptr1)+i) ^= *((char*)(ptr2)+i);
        *((char*)(ptr2)+i) ^= *((char*)(ptr1)+i);
        *((char*)(ptr1)+i) ^= *((char*)(ptr2)+i);
    }
}

void printEvent(struct Event_Status* events, int count) {
    for (int i = 0; i < count; i++) {
        for (int j = count - 1; j > i; j--) {
            if (events[j].event.begin_hour < events[j - 1].event.begin_hour) {
                swap((void*)&(events[j]), (void*)&(events[j - 1]), sizeof(Event_Status));
            }
            else if (events[j].event.begin_hour == events[j - 1].event.begin_hour) {
                if (events[j].event.end_hour < events[j - 1].event.end_hour)
                    swap((void*)&(events[j]), (void*)&(events[j - 1]), sizeof(Event_Status));
            }
        }
    }
    printf("%8s\t%6s\t%6s\n", "Index", "Begin", "End");
    for (int i = 0; i < count; i++) {
        printf("Event%2d:\t%6d\t%6d\n", events[i].index, events[i].event.begin_hour, events[i].event.end_hour);
    }
}

int main() {
    //数据处理
    char* buf = NULL;
    int len = 0;
    int count = 0;
    char c;
    printf("Input:");
    while ((c = getchar()) != '\n') {
        if (c >= '0' && c <= '9') {
            char* tmp = malloc(len + 1);
            tmp[len] = c;
            memcpy(tmp, buf, len);
            free(buf);
            buf = tmp;
            len++;
        }
        else if (c == ',') {
            char* tmp = malloc(len + 1);
            tmp[len] = ' ';
            memcpy(tmp, buf, len);
            free(buf);
            buf = tmp;
            len++;
        }
    }
    int flag_digit = 0;
    for (int i = 0; i < len; i++) {
        if (buf[i] >= '0' && buf[i] <= '9') {
            if (!flag_digit) {
                count++;
                flag_digit = 1;
            }
        }
        else {
            if (flag_digit) {
                flag_digit = 0;
            }
        }
    }
    count = (count % 2 == 0) ? (count / 2) : ((count + 1) / 2);

    //初始化
    Event_Status* events = malloc(count * sizeof(Event_Status));
    for (int i = 0; i < count; i++) {
        events[i].event.begin_hour = get_num_abs(buf, len);
        events[i].event.end_hour = get_num_abs(buf, len);
        if (events[i].event.begin_hour == -1 || events[i].event.end_hour == -1) {
            printf("Error: Wrong Data Format\n");
            return -1;
        }
        events[i].flag_can_be_arranged = 1;
        events[i].index = i + 1;
    }

    //任务1
    printEvent(events, count);

    //任务2
    for (int i = 0; i < count; i++) {
        if (events[i].flag_can_be_arranged) {
            for (int j = 1; j < count; j++) {
                if (events[i].event.begin_hour > events[j].event.begin_hour && events[i].event.begin_hour < events[j].event.end_hour) {
                    events[i].flag_can_be_arranged = 0;
                    events[j].flag_can_be_arranged = 0;
                }
                if (events[i].event.end_hour > events[j].event.begin_hour && events[i].event.end_hour < events[j].event.end_hour) {
                    events[i].flag_can_be_arranged = 0;
                    events[j].flag_can_be_arranged = 0;
                }
            }
        }
    }

    //输出
    //出于稳定性考虑，把“是/否”换成了“Yes/No”
    printf("%8s\t%6s\t%6s\t%10s\n", "Index", "Begin", "End", "Available");
    for (int i = 0; i < count; i++) {
        printf("Event%2d:\t%6d\t%6d\t%10s\n", events[i].index, events[i].event.begin_hour, events[i].event.end_hour, events[i].flag_can_be_arranged ? "Yes" : "No");
    }
    return 0;
}