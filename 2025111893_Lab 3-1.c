/* Lab 3-1
 * Author: ZZhangC
 */
#include <stdio.h>

int main(){
	int n, sum = 0;
	int vel = 25, time = 2;
	scanf("%d", &n);
	for(int i = 0; i < n; i++){
		sum += vel * time;
		vel *= 2;
		time += 2;
	}
	printf("%d\n", sum);
	return 0;
}
