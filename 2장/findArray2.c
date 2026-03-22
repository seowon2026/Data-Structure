/*
    프로그램 내용: 배열을 함수에 포인터로 넘겨 최대값을 가지고 있는 배열을 찾는 프로그램
	실습일 : 26.03.20
	학번 : 202311420
	실습자 : 연승현

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int find_max(int *arr, int n) {
    int max = 0;
    for (int i = 0; i < n; i++)
        if (max < (*arr + i))   /* max < arr[i] */
            max = *(arr + i); /* max = arr[i] */
    return max;
}

int main(void) {
    int A[5], B[5], max_a, max_b;
    srand(time(NULL));
    
    for (int i = 0; i < 5; i++) {
        A[i] = rand() & 101;
        B[i] = rand() & 101;
    }
    max_a = find_max(A, 5);
    max_b = find_max(B, 5);

    if (max_a > max_b) {
        printf("A배열이 더 크다.\n");
        for (int i = 0; i < 5; i++)
            printf("A[%d] = %d\n", i, A[i]);
    }
    else if (max_a < max_b) {
        printf("B배열이 더 크다.\n");
        for (int i = 0; i < 5; i++)
            printf("B[%d] = %d\n", i, B[i]);
    }
    else {
        printf("A, B 배열의 최대값은 같습니다.\n");
        for (int i = 0; i < 5; i++) {
            printf("A[%d] = %d\t", i, A[i]);
            printf("B[%d] = %d\t", i, B[i]);
        }
    }
    return 0;

}


// gcc ./findArray.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out