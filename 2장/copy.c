/*
    프로그램 내용: 함수의 매개변수로써의 변수와 배열
	실습일 : 26.03.20
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>

void copy_array(int a[], int b[], int len) {
    int i;
    for (i = 0; i < len; i++) {
        b[i] = a[i];
    }
}

void copy_variable(int a, int b) {
    b = a;
}

void main() {
    int A[5] = { 10, 20, 30 };
    int B[5], i, x = 2018, y = 0;

    copy_variable(x, y);
    copy_array(A, B, 5);

    printf("변수 복사 결과: x=%d, y=%d\n", x, y);
    printf("배열 복사 결과: \n");
    for (i = 0; i < 5; i++) {
        printf("A[%d] = %d\t", i, A[i]);
        printf("B[%d] = %d\n", i, B[i]);
    }
}


// gcc ./copy.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out