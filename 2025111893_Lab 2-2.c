#include <stdio.h>

int main() {
	char c;
	scanf("%c", &c);
	if (c >= 'A' && c <= 'Z') {
		goto print;
	}
	else if (c >= 'a' && c <= 'z') {
		c += 'A' - 'a';
		goto print;
	}
	else {
		printf("Invalid character!\n");
		goto end;
	}
print:
	for (char i = 'A'; i <= c; i++) {
		for (char j = i - (c - 'A'); j <= i + i - 'A'; j++)
		{
			if (j < 'A') {
				printf(" ");
			}
			else {
				printf("%c", j > i ? (i - (j - i)) : j);
			}
		}
		printf("\n");
	}
end:
	return 0;
}