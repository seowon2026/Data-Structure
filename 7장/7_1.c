/*
    프로그램 내용: 순환적인 팩토리얼 계산 프로그램
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>

int factorial(int n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main(void)
{
    printf("%d\n", factorial(3));
    return 0;
}

// gcc ./7_1.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
