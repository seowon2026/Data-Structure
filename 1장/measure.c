/*
    프로그램 내용: 랜덤 난수로 배열을 채워 최대값을 출력한 후 실행 시간을 측정하고, 점수를 입력받아 그 중 최대값을 찾는 프로그램 (프로그램1.2 응용)
	실습일 : 26.03.13
	학번 : 202311420
	실습자 : 연승현
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ELEMENTS 5

int find_max_score(int* score, int n);

int main(void) {
    int i, result;
    clock_t start, finish;
    double duration;
    int score[MAX_ELEMENTS];
    int score2[5];


    srand(time(NULL));
    for (i = 0; i < MAX_ELEMENTS; i++) {
        score[i] = rand();
    }

    start = clock();
    result = find_max_score(score, MAX_ELEMENTS);
    printf("최대 점수는 %d 입니다. \n", result);
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f 초 입니다.\n", duration);

    for (i = 0; i < MAX_ELEMENTS; i++) {
        printf("저장할 점수를 입력 >> ");
        scanf("%d", &score2[i]);
    }

    result = find_max_score(score2, MAX_ELEMENTS);
    printf("최대 점수는 %d 입니다.\n", result);
    return 0;
}

int find_max_score(int* score, int n) {
    int i, tmp;
        tmp = score[0];
    for (i = 1; i < n; i++) {
        if (score[i] > tmp)
            tmp = score[i];
    }
    return tmp;
}


// gcc ./measure.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out