/* Lab 3-3
 * 高耦合版
 * 我觉得不可能还有高手写出耦合度比我高的
 * Author: ZZhangC
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//更新：提高了耦合度
int guess(int _num, int _fin){
	int n;
	scanf("%d", &n);
	if(n == _num){
		return 1;
	}
	else if(n > _num && !_fin){
		printf("Bigger than the answer, guess again: ");
		return 0;
	}
	else if(n < _num && !_fin){
		printf("Smaller than the answer, guess again: ");
		return 0;
	}
}

int main(){
	int num;
	srand(time(NULL));

begin:
	num = rand() % 100;//如果是<random.h>里的随机数引擎会更好一些
	printf("Guess the number: ");
	for(int i = 0; i < 7; i++){
		if(guess(num, (((i+1) % 7) == 0 ? 1 : 0))){
			goto correct;
		}
	}
	goto incorrect;

correct:
	printf("Correct!\n");
	goto rev;

incorrect:
	printf("You didn't get it!\n");
	goto rev;


rev:
	printf("Wanna play it again?[y/N]\n");
	char c;
	while(c != '\n' && c != EOF){
		c = getchar();
	}
	scanf("%c", &c);
	if(c == 'Y' || c == 'y'){
		goto begin;
	}
	else if(c == 'N' || c == 'n' || c == '\n'){
		goto end;
	}
	else{
		printf("Invaild input.\n");
		goto rev;
	}

end:
	return 0;
}

