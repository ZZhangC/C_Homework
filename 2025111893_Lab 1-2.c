#include <stdio.h>

int main(void){
    short x=93, y=33;
    /* 
     * x = 00000000 01011101
     * y = 00000000 00100001
     * !x = 0
     * x || y = 1
     * x && y = 1
     * ~x = 11111111 10100010   无符号时是65442，有符号时是-94
     * x|y = 00000000 01111101  是125
     * x&y = 00000000 00000001  是1
     */
    printf("%5hd%5hd%5hd\n", !x, x||y, x&&y);
    printf("%5hu%5hd%5hd\n", ~x, x|y, x&y);
    printf("%5hd%5hd%5hd\n \n", ~x, x|y, x&y);
    return 0;
}