/*
 * 2025111893_Lab 7-2.c
 * Author: ZZhangC
 * Date: 07/12/2025
 */
#include <stdio.h>

typedef struct Subject {
    int mathScore;
    int physicsScore;
    int programmingScore;
} Subject;

typedef struct Student {
    char* id;
    char* name;
    Subject sub;
} Student;

void swap(void* ptr1, void* ptr2, unsigned int len);

void printMathScore(struct Student* stu, int len);

int main() {
    Subject sub[10] = {
        {99, 100, 60},
        {98, 88, 90},
        {87, 100, 100},
        {89, 88, 87},
        {78, 90, 93},
        {100, 100, 100},
        {80, 94, 99},
        {100, 88, 78},
        {78, 77, 76},
        {90, 90, 97}
    };

    Student stu[10] = {
        {"20221101", "A", sub[0]},
        {"20221102", "B", sub[1]}, 
        {"20221103", "C", sub[2]},
        {"20221104", "D", sub[3]}, 
        {"20221105", "E", sub[4]},
        {"20221106", "F", sub[5]}, 
        {"20221107", "G", sub[6]},
        {"20221108", "H", sub[7]}, 
        {"20221109", "I", sub[8]},
        {"20221110", "J", sub[9]}
    };

    printMathScore(stu, 10);

    return 0;
}

void swap(void* ptr1, void* ptr2, unsigned int len) {
    for (int i = 0; i < len; i++) {
        *((char*)(ptr1) + i) ^= *((char*)(ptr2) + i);
        *((char*)(ptr2) + i) ^= *((char*)(ptr1) + i);
        *((char*)(ptr1) + i) ^= *((char*)(ptr2) + i);
    }
}

void printMathScore(struct Student* stu, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = len - 1; j > i; j--) {
            if (stu[j].sub.mathScore > stu[j - 1].sub.mathScore) {
                swap((void*)&(stu[j]), (void*)&(stu[j - 1]), sizeof(Student));
            }
        }
        
    }
    
    printf("%8s\t%8s\t%8s\t%8s\n", "Rank", "Id", "Name", "Score");
    for (int i = 0; i < len; i++) {
        printf("%8d\t%8s\t%8s\t%8d\n", i + 1, stu[i].id, stu[i].name, stu[i].sub.mathScore);
    }
}