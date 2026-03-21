/*
	날짜 : 26.03.13
	학번 : 202311420
	이름 : 연승현
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
    printf("%f 초 입니다.", duration);

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