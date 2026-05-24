/*
    프로그램 내용: 반복적인 피보나치 수열 계산 함수
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <time.h>

int fib_iter(int n)
{
    int i, tmp, current, last;

    if (n < 2)
        return n;

    last = 0;
    current = 1;
    for (i = 2; i <= n; i++) {
        tmp = current;
        current += last;
        last = tmp;
    }
    return current;
}

int main(void)
{
    int n = 30;
    clock_t start, end;
    double elapsed;

    start = clock();
    printf("fib(%d) = %d\n", n, fib_iter(n));
    end = clock();

    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("실행 시간 = %.6f초\n", elapsed);
    return 0;
}

// gcc ./7_7.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
