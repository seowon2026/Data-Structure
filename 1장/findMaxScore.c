/*
	프로그램 내용: 랜덤값을 배열에 넣어 최대값을 찾은 후 출력
	실습일 : 26.03.13
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEMENTS 5

int find_max_score(int* score, int n);

int main(void)
{
	int i, result;
	int score[MAX_ELEMENTS];
	clock_t start, finish;
	double duration;
	
	srand(time(NULL));
	for (i = 0; i < MAX_ELEMENTS; i++) {
		score[i] = rand();
	
	}
	result = find_max_score(score, MAX_ELEMENTS);
	printf("최대 점수는 %d 입니다. \n", result);
	return 0;

}

int find_max_score(int* score, int n); // int *score == int score[] */
	{
		int i, tmp;
		tmp = score[0];
		for (i = 1; i < n; i++) {
			if (score[i] > tmp)
				tmp = score[i];
		}
		return tmp;
}

// gcc ./findMaxScore.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out