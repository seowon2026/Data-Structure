/*
    프로그램 내용: 반복적인 거듭제곱 계산 프로그램
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>

double slow_power(double x, int n)
{
    int i;
    double result = 1.0;

    for (i = 0; i < n; i++)
        result = result * x;

    return result;
}

int main(void)
{
    printf("%.0f\n", slow_power(2.0, 10));
    return 0;
}

// gcc ./7_4.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
