/*
    프로그램 내용: 하노이의 탑 문제 프로그램
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <time.h>

void hanoi_tower(int n, char from, char tmp, char to)
{
    if (n == 1)
        printf("원판 1을 %c에서 %c으로 옮긴다.\n", from, to);
    else {
        hanoi_tower(n - 1, from, to, tmp);
        printf("원판 %d을 %c에서 %c으로 옮긴다.\n", n, from, to);
        hanoi_tower(n - 1, tmp, from, to);
    }
}

int main(void)
{
    clock_t start, end;
    double elapsed;

    start = clock();
    hanoi_tower(4, 'A', 'B', 'C');
    end = clock();

    elapsed = (double)(end - start) / CLOCKS_PER_SEC;
    printf("실행 시간 = %.6f초\n", elapsed);
    return 0;
}

// gcc ./7_8.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
