/*
    프로그램 내용: 랜덤한 수를 생성하여 배열에 저장한 뒤 최대값을 찾아 출력하고 실행 시간을 측정하는 프로그램
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
    clock_t start, finish;
    double duration;
    int i, result;
    int score[MAX_ELEMENTS];

    srand(time(NULL));

    for (i = 0; i < MAX_ELEMENTS; i++) {
        score[i] = rand();
    }

    start = clock();
    result = find_max_score(score, MAX_ELEMENTS);

    printf("최대 점수는 %d 입니다.\n", result);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f 초 입니다.\n", duration);

    return 0;
}

int find_max_score(int* score, int n)
{
    int i, tmp;

    tmp = score[0];

    for (i = 1; i < n; i++) {
        if (score[i] > tmp)
            tmp = score[i];
    }

    return tmp;
}


// gcc ./bestScore.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out