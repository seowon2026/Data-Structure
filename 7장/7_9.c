/*
    프로그램 내용: 순환을 이용한 미로 탐색 프로그램
    실습일 : 26.05.08
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>

#define MAZE_SIZE 6

char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '1', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}
};

int xExit = 5, yExit = 4, done = 0;

int is_valid(int x, int y)
{
    if (x < 0 || y < 0 || x >= MAZE_SIZE || y >= MAZE_SIZE)
        return 0;
    return map[y][x] == '0' || map[y][x] == 'x';
}

void search_recur(int x, int y)
{
    if (done)
        return;

    printf("(%d,%d) ", x, y);
    if (x == xExit && y == yExit) {
        done = 1;
        return;
    }

    map[y][x] = '.';
    if (is_valid(x - 1, y))
        search_recur(x - 1, y);
    if (is_valid(x + 1, y))
        search_recur(x + 1, y);
    if (is_valid(x, y - 1))
        search_recur(x, y - 1);
    if (is_valid(x, y + 1))
        search_recur(x, y + 1);
}

int main(void)
{
    search_recur(0, 1);
    if (done)
        printf("\n ==> 출구가 탐지되었습니다.\n");
    else
        printf("\n ==> 출구를 찾지 못했습니다.\n");
    return 0;
}

// gcc ./7_9.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
