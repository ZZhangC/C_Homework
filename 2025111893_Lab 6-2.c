/*
 * 2025111893_Lab 6-2.c
 * Author: ZZhangC
 * Date: 24/11/2025
 */
#include <stdio.h>
#include <stdlib.h>

//这个0是干什么的
static int dayTab[2][13] = {{0,31,28,31,30,31,30,31,31,30,31,30,31},	
					        {0,31,29,31,30,31,30,31,31,30,31,30,31}};
//神秘函数
void MonthDay(int year, int yearDay, int *pMonth, int *pDay) {
	int  i, leap;
	leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);    
	for (i = 1; yearDay>dayTab[leap][i]; i++) {
    	yearDay = yearDay - dayTab[leap][i];
	}
	*pMonth = i;      /*将计算出的月份值赋值给pMonth所指向的变量*/
	*pDay = yearDay;   /*将计算出的日期赋值给pDay所指向的变量*/
}

void YearDay(int year, int month, int monthDay, int *pDay){
    int count = 0;
    int leap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0); 
    for (int i = 0; i < month; i++) {//这里让i=0使得数组里的0变得有用
        count += dayTab[leap][i];
    }
    count += monthDay;
    *pDay = count;
}

int main() {
    //task1
    int year, yearDay, month, day;
    year = 2025;
    yearDay = 328;
    //调用
    MonthDay(year, yearDay, &month, &day);
    printf("%d\n", day);
    //task2
    int year2, month2, monthDay, day2;
    year2 = 2012;
    month2 = 12;
    monthDay = 21;
    YearDay(year2, month2, monthDay, &day2);
    printf("%d\n", day2);
    return 0;
}