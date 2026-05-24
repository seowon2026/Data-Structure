/*
    프로그램 내용: 순환적인 거듭제곱 계산 프로그램
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>

double power(double x, int n)
{
    if (n == 0)
        return 1;
    else if ((n % 2) == 0)
        return power(x * x, n / 2);
    else
        return x * power(x * x, (n - 1) / 2);
}

int main(void)
{
    printf("%.0f\n", power(2.0, 10));
    return 0;
}

// gcc ./7_5.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
