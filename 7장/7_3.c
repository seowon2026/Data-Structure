/*
    프로그램 내용: 반복적인 팩토리얼 계산 프로그램
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>

int factorial_iter(int n)
{
    int k;
    int result = 1;

    for (k = 1; k <= n; k++)
        result = result * k;

    return result;
}

int main(void)
{
    printf("%d\n", factorial_iter(3));
    return 0;
}

// gcc ./7_3.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
