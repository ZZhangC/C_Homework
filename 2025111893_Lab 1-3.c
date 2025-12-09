#include <stdio.h>

int main(void){
    int mode;
    double a;
    scanf("%d %lf", &mode, &a);
    if(mode){
        printf("The Fahrenheit is %.2lf\n", 9 * a / 5 + 32);
    }
    else{
        printf("The Centigrade is %.2lf\n", 5 * (a - 32) / 9);
    }
    return 0;
}