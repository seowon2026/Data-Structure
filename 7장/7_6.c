/*
    프로그램 내용: 순환적인 피보나치 수열 계산 함수
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <time.h>

int fib(int n)
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int main(void)
{
    int n = 30;
    clock_t start, end;
    double elapsed;

    start = clock();
    printf("fib(%d) = %d\n", n, fib(n));
    end = clock();

    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("실행 시간 = %.6f초\n", elapsed);
    return 0;
}

// gcc ./7_6.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
