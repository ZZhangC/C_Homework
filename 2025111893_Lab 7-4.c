/*
 * 2025111893_Lab 7-4.c
 * Author: ZZhangC
 * Date: 07/12/2025
 */
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct CARD {
	char  suit[10];
	char  face[10];
};

void Deal(struct CARD* wCard);
void Shuffle(struct CARD* wCard);
void FillCard(struct CARD wCard[], char* wFace[], char* wSuit[]);

int main() {
	char* suit[] = { "Spades","Hearts","Clubs","Diamonds" };
	char* face[] = { "A","2","3","4","5","6","7","8","9","10","Jack","Queen","King" };
	int i;
	struct CARD card[52];

	srand(time(NULL));

    //Initial Code
	/*
	 * FillCard(card, face, suit);
	 * Shuffle(card);
	 * Deal(card);
	 */

    //My Code
	void (*p1)(struct CARD*, char**, char**) = &FillCard;
	void (*p2)(struct CARD*) = &Shuffle;
	void (*p3)(struct CARD*) = &Deal;
    p1(card, face, suit);
    p2(card);
    p3(card);

	return 0;
}

/*	函数功能：将52张牌按黑桃、红桃、草花、方块的花色顺序，面值按A~K的顺序排列
	函数参数：结构体数组wCard，表示不同花色和面值的52张牌
			指针数组wFace，表示指向面值字符串
			指针数组wSuit，表示指向花色字符串
	函数返回值：无
*/
void  FillCard(struct CARD wCard[], char* wFace[], char* wSuit[]) {
	int	i;

	for (i = 0; i < 52; i++) {
		strcpy(wCard[i].suit, wSuit[i / 13]);
		strcpy(wCard[i].face, wFace[i % 13]);
	}
}

/*	函数功能：将52张牌的顺序打乱，循环52次，每一次产生一个0~51的随机数，将当前的
	一张牌与所产生的随机数的那张牌进行交换
	函数参数：结构体指针wCard，为指向存放52张牌的结构体数组的指针
			函数返回值：无
*/
void Shuffle(struct CARD* wCard) {
	int i, j;
	struct CARD temp;
	for (i = 0; i < 52; i++)				       /* 洗牌过程 */
	{
		j = rand() % 52;
		temp = wCard[i];
		wCard[i] = wCard[j];
		wCard[j] = temp;
	}
}

/* 	函数功能：输出发牌结果
	函数参数：结构体指针wCard，为指向存放52张牌的结构体数组的指针
	函数返回值：无
*/
void Deal(struct CARD* wCard) {
	int i;

	for (i = 0; i < 52; i++)		/* 输出发牌结果 */
		printf("%10s%10s\n", wCard[i].suit, wCard[i].face);
}
