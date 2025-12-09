#include <stdio.h>

int main() {
	int t;
	scanf("%d", &t);
	if (t >= 0 && t < 12) {
		printf("good morning.\n");
	}
	else if (t == 12) {
		printf("good noon.\n");
	}
	else if (t < 18 && t >= 0) {
		printf("good afternoon.\n");
	}
	else if (t < 21 && t >= 0) {
		printf("good evening.\n");
	}
	else if (t < 24 && t >= 0) {
		printf("good night.\n");
	}
	else {
		printf("the input is invalid.\n");
	}
	return 0;
}