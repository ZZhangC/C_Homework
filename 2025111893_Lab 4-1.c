/*
 * -README-
 * Note: 为了让这些接口看起来有用一点，我为一些接口加了防呆设计.(尽管依旧不规范，但是总归安全了些)
 * File: 2025111893_Lab 4-1.c
 * Author: ZZhangC
 * Date: 11/10/2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEP_LINE "-------------------------------------"
#define SPACE " "
#define TAB "  "
#define NON_DATE "   "
#define START_YEAR 1800
#define WEEK_LEN 7
#define START_DAY_INDEX 4



int isYearVaild(int _year);
int isMonthVaild(int _month);
int readInput(int* _year, int* _month);
void printMonth(int _year, int _month);

void printMonthTitle(int _year, int _month);
void getMonthName(int _month, char** _name);

void printMonthBody(int _year, int _month);
int getStartDay(int _year, int _month);
int getNumOfDaysInMonth(int _year, int _month);
int getFirstLineCount(int _year, int _month);
int getLineCount(int _year, int _month);
void printLineDay();
void printLineNum(int _year, int _month, int _line);
int isLeapYear(int _year);
//为了和strlen()风格一致，这个函数模仿C库风格，因此不采用驼峰命名法.
//实话说，驼峰写多了看着很累，我更喜欢Linux的命名方法.
int intlen(int _num);



//printCalendar()以main()代替
int main() {
    int year, month;
    if (!readInput(&year, &month))
        return -1;
    printMonth(year, month);
    return 0;
}


int isYearVaild(int _year) {
    return _year >= START_YEAR ? 1 : 0;
}

int isMonthVaild(int _month) {
    return _month >= 1 ? (_month <= 12 ? 1 : 0) : 0;
}


int readInput(int* _yearPtr, int* _monthPtr) {
    printf("Please input the year: ");
    if (scanf("%d", _yearPtr) == EOF)
        return 0;
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Please input the month: ");
    if (scanf("%d", _monthPtr) == EOF)
        return 0;
    if (!isYearVaild(*_yearPtr))
        return 0;
    if (!isMonthVaild(*_monthPtr))
        return 0;
    return 1;
}


void printMonth(int _year, int _month) {
    if (!isYearVaild(_year))
        return;
    if (!isMonthVaild(_month))
        return;
    //标题
    printMonthTitle(_year, _month);
    //分割线
    printf(SEP_LINE);
    printf("\n");
    //主体
    printMonthBody(_year, _month);
}

void printMonthTitle(int _year, int _month) {
    if (!isYearVaild(_year))
        return;
    if (!isMonthVaild(_month))
        return;
    char* _name;
    getMonthName(_month, &_name);
    int _titleLen = strlen(_name) + 3 * (int)strlen(SPACE) + intlen(_year);
    int _spaceLen = (strlen(SEP_LINE) - _titleLen) / 2;
    for (int i = 0; i < _spaceLen; i++) {
        printf(SPACE);
    }
    printf("%s   %d\n", _name, _year);
}


void printMonthBody(int _year, int _month) {
    if (!isYearVaild(_year))
        return;
    if (!isMonthVaild(_month))
        return;
    printLineDay();
    int _lines = getLineCount(_year, _month);
    for (int i = 1; i <= _lines; i++) {
        printLineNum(_year, _month, i);
    }
}

void getMonthName(int _month, char** _name) {
    if (!isMonthVaild(_month))
        return;
    switch (_month) {
    case 1:
        *_name = "January";
        break;
    case 2:
        *_name = "February";
        break;
    case 3:
        *_name = "March";
        break;
    case 4:
        *_name = "April";
        break;
    case 5:
        *_name = "May";
        break;
    case 6:
        *_name = "June";
        break;
    case 7:
        *_name = "July";
        break;
    case 8:
        *_name = "August";
        break;
    case 9:
        *_name = "September";
        break;
    case 10:
        *_name = "October";
        break;
    case 11:
        *_name = "November";
        break;
    case 12:
        *_name = "December";
        break;
    }
}


int getStartDay(int _year, int _month) {
    if (!isYearVaild(_year))
        return 0;
    if (!isMonthVaild(_month))
        return 0;
    int _day = 1;
    for (int i = START_YEAR; i < _year; i++)
        _day += isLeapYear(i) ? 366 : 365;
    for (int i = 1; i < _month; i++) {
        _day += getNumOfDaysInMonth(_year, i);
    }
    return _day;
}

int getNumOfDaysInMonth(int _year, int _month) {
    if (!isYearVaild(_year))
        return 0;
    if (!isMonthVaild(_month))
        return 0;
    switch (_month) {
        case 1:
            return 31;
            break;
        case 2:
            return isLeapYear(_year) ? 29 : 28;
            break;
        case 3:
            return 31;
            break;
        case 4:
            return 30;
            break;
        case 5:
            return 31;
            break;
        case 6:
            return 30;
            break;
        case 7:
            return 31;
            break;
        case 8:
            return 31;
            break;
        case 9:
            return 30;
            break;
        case 10:
            return 31;
            break;
        case 11:
            return 30;
            break;
        case 12:
            return 31;
            break;
    }
}

int getFirstLineCount(int _year, int _month) {
    if (!isYearVaild(_year))
        return 0;
    if (!isMonthVaild(_month))
        return 0;
    int _day = getStartDay(_year, _month);
    //这里是计算第一行有多少数字
    int _index = ((_day - 1) % WEEK_LEN + START_DAY_INDEX) % WEEK_LEN;
    if (_index == 0)
        _index = 7;
    return WEEK_LEN - _index + 1;
}

int getLineCount(int _year, int _month) {
    if (!isYearVaild(_year))
        return 0;
    if (!isMonthVaild(_month))
        return 0;
    int _lines = 0;
    int _total = getNumOfDaysInMonth(_year, _month);
    int _firstLineCount = getFirstLineCount(_year, _month);
    _lines++;
    _total -= _firstLineCount;
    _lines += _total / WEEK_LEN;
    if (_total % WEEK_LEN != 0)
        _lines++;
    return _lines;
}

void printLineDay() {
    printf(TAB);
    printf("Sun");
    printf(TAB);
    printf("Mon");
    printf(TAB);
    printf("Tue");
    printf(TAB);
    printf("Wed");
    printf(TAB);
    printf("Thu");
    printf(TAB);
    printf("Fri");
    printf(TAB);
    printf("Sat");
    printf("\n");
}

void printLineNum(int _year, int _month, int _line) {
    if (!isYearVaild(_year))
        return;
    if (!isMonthVaild(_month))
        return;
    /* _date打印的规则
     * _date小于1时打印三个空格
     * 大于等于1小于10时打印一个空格 + _date + 一个空格
     * 大于10时打印_date + 一个空格
     */
    int _date = 1;
    _date -= WEEK_LEN - getFirstLineCount(_year, _month);
    for (int i = 1; i < _line; i++) {
        _date += WEEK_LEN;
    }
    //printf("%d", _date);
    for (int i = 0; i < WEEK_LEN; i++) {
        printf(TAB);
        if (_date < 1) {
            printf(NON_DATE);
            _date++;
        }
        else if (_date < 10) {
            printf(SPACE);
            printf("%d", _date);
            printf(SPACE);
            _date++;
        }
        else if (_date <= getNumOfDaysInMonth(_year, _month)) {
            printf("%d", _date);
            printf(SPACE);
            _date++;
        }
        else {
            return;
        }
    }
    printf("\n");
}

int isLeapYear(int _year) {
    return ((_year % 4 == 0 && _year % 100 != 0) || _year % 400 == 0) ? 1 : 0;
}

int intlen(int _num) {
    int _len = 0;
    if (_num < 0)
        _len++;
    while (_num > 0) {
        _len++;
        _num /= 10;
    }
    return _len;
}
