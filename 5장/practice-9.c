/*
    프로그램 내용: 동적 배열로 정수를 저장하고 메뉴를 실행하는 프로그램 (연습문제 9번)
    실습일 : 26.05.02
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 크기가 n인 동적 배열을 생성
int* create_array(int n) {
    return (int*)malloc(sizeof(int) * n);
}

// 배열을 난수로 채움
void fill_random(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100 + 1;
    }
}

// 배열의 각 원소를 출력
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
}

// 배열 원소들의 합을 계산
int sum_array(int arr[], int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    return sum;
}

// 동적 할당된 메모리를 반환
void free_array(int* arr) {
    free(arr);
}

int main(void) {
    int* arr = NULL;
    int n = 0;
    int menu;

    srand((unsigned int)time(NULL));

    while (1) {
        printf("====================================\n");
        printf("1. 크기가 n인 동적 배열을 생성\n");
        printf("2. 배열을 난수로 채운다.\n");
        printf("3. 배열의 각 원소를 출력한다.\n");
        printf("4. 배열의 각 원소들의 합을 출력한다.\n");
        printf("5. 동적 할당 공간을 반환한다.\n");
        printf("====================================\n");
        printf("메뉴를 선택하시오: ");
        scanf("%d", &menu);

        if (menu == 1) {
            if (arr != NULL) {
                free_array(arr);
            }

            printf("배열의 크기 n을 입력하시오: ");
            scanf("%d", &n);

            arr = create_array(n);

            if (arr == NULL) {
                printf("메모리 할당 실패\n");
                n = 0;
            } else {
                printf("동적 배열이 생성되었습니다.\n");
            }
        } 
        else if (menu == 2) {
            if (arr == NULL) {
                printf("배열이 생성되지 않았습니다.\n");
            } else {
                fill_random(arr, n);
                printf("배열을 난수로 채웠습니다.\n");
            }
        } 
        else if (menu == 3) {
            if (arr == NULL) {
                printf("배열이 생성되지 않았습니다.\n");
            } else {
                print_array(arr, n);
            }
        } 
        else if (menu == 4) {
            if (arr == NULL) {
                printf("배열이 생성되지 않았습니다.\n");
            } else {
                printf("배열 원소들의 합: %d\n", sum_array(arr, n));
            }
        } 
        else if (menu == 5) {
            if (arr != NULL) {
                free_array(arr);
                arr = NULL;
                n = 0;
                printf("동적 할당 공간을 반환했습니다.\n");
            } else {
                printf("반환할 공간이 없습니다.\n");
            }
            break;
        } 
        else {
            printf("잘못된 메뉴입니다.\n");
        }
        printf("\n");
    }

    return 0;
}


// gcc ./practice-9.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out