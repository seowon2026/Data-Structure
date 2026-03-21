/*
    2장 최댓값이 존재하는 배열을 찾는 프로그램
	날짜 : 26.03.13
	학번 : 202311420
	이름 : 연승현
*/


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

int find_max(int arr[], int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        if (max < arr[i])
            max = arr[i];
        return max;
    }
}

int main(void) {
    int A[5], B[5], max_a, max_b;
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        A[i] = rand() % 101;
        B[i] = rand() % 101;
    }

    max_a = find_max(A, 5);
    max_b = find_max(B, 5);

    if (max_a > max_b)
        printf("A 배열에 최댓값이 %d가 존재합니다. \n", max_a);
    else if (max_a < max_b)
        printf("B 배열에 최댓값이 %d가 존재합니다. \n", max_b);
    else
        printf("A, B배열의 최댓값이 동일합니다. \n");

    return 0;
}


// gcc ./findArray.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out