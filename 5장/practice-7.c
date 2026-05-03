/*
    프로그램 내용: 사용자가 입력하는 정수를 동적 메모리에 저장하는 프로그램 (연습문제 7번)
    실습일 : 26.05.02
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>

void main() {
    int count;
    int *arr;
    int i;

    printf("정수의 개수: ");
    scanf("%d", &count);

    arr = (int *)malloc(sizeof(int) * count);

    if (arr == NULL) {
        printf("메모리 할당 실패\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("정수 #%d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    printf("\n입력한 정수 출력\n");

    for (i = 0; i < count; i++) {
        printf("정수 #%d: %d\n", i + 1, arr[i]);
    }

    free(arr);
}


// gcc ./practice-7.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out