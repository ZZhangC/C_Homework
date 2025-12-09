/* Lab 3-3
 * Author: ZZhangC
 */
#include <stdio.h>

int main(){
	for(int n = 5; n >= 1; n--){
		int flag_fruit = 1;
		for(int o = ((900 - n * 160) / 40); o >= 0 && flag_fruit == 1; o--){
			for(int w = ((900 - n * 160 - o * 40) / 50); w >= 0 && flag_fruit == 1; w--){
				for(int v = ((900 - n * 160 - o * 40 - w * 50) / 80); v >= 0; v--){
					if(o == 0 && w == 0){
						flag_fruit = 0;
					}
					if(flag_fruit == 1 && n + o + w + v <= 10 && 900 - n * 160 - o * 40 - w * 50 - v * 80 == 0){
						printf("%d %d %d %d\n", n, o, w, v);
					}
				}
			}
		}
	}
	return 0;
}
