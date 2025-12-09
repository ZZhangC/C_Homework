#include <stdio.h>

int Is_Prime(const int _num) {
	if (_num < 2)
		return 0;
	for (int i = 2; i * i <= _num; ++i)
		if (_num % i == 0)
			return 0;
	return 1;
}

int Size(int _num) {
	int _tmp = 1;
	while (1) {
		_num /= 10;
		if (_num != 0)
			_tmp++;
		else
			break;
	}
	return _tmp;
}

int Is_Palindrome(const int _num) {
	int tmp1 = _num, tmp2 = 0;
	while (tmp1 != 0) {
		tmp2 = tmp1 % 10 + tmp2 * 10;
		tmp1 /= 10;
	}
	if (tmp2 == _num)
		return 1;
	else
		return 0;
}

int main() {
	int a, b;
	scanf("%d %d", &a, &b);
	short l = Size(a), r = Size(b);
	for (int i = (a % 2 == 0 ? a + 1 : a); i <= b; i += 2) {
		short tmp = Size(i);
		if (tmp % 2 == 0 && tmp != 2) {
			i = 1;
			for (int k = 0; k < tmp; k++)
				i *= 10;
			i++;
			continue;
		}
		else if (tmp != 1) {
			if(i % 5 ==0)
				continue;
			int tmp2 = i;
			for (int k = 1; k < tmp; k++)
				tmp2 /= 10;
			if (tmp2 % 2 == 0 || tmp2 % 5 == 0) {
				int tmp3 = 1;
				for (int k = 1; k < tmp; k++)
					tmp3 *= 10;
				i += tmp3 * (tmp2 %2 == 0 ? 1 : 2);
				i -= 2;
				continue;
			}
		}
		if (Is_Palindrome(i) && Is_Prime(i))
			printf("%d\n", i);
	}
	return 0;
}