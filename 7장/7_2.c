/*
    프로그램 내용: 출력문이 추가된 순환적인 팩토리얼 계산 프로그램
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>

int factorial(int n)
{
    printf("factorial(%d)\n", n);
    if (n == 1)
        return 1;
    else
        return n * factorial(n - 1);
}

int main(void)
{
    factorial(3);
    return 0;
}

// gcc ./7_2.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
