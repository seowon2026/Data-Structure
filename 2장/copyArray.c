/*
    프로그램 내용: 배열 복사 연습
	실습일 : 26.03.20
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>

int main() 
{
	int A[5] = { 10, 20, 30 };
	int B[5], i, x = 2018, y = 0;
	y = x;
	for (i = 0; i < 5; i++) {
		B[i] = A[i];
	}
	printf("변수복사결과 x=%d, y=%d 입니다\n", x, y);
	printf("배열복사결과 \n" );
	for (i = 0; i < 5; i++) {
		printf("A[%d] = %d\t", i, A[i]);
		printf("B[%d] = %d\n", i, B[i]);
	}

	return 0;
}


// gcc ./copyArray.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out