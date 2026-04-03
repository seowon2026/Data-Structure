/*
    프로그램 내용: 최대값을 찾는 알고리즘 프로그램 (프로그램1.1)
	실습일 : 26.03.13
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>

int find_array_max(int score[], int n) {
    int i, tmp=score[0];

    for(i=1; i<n; i++) {
        if(score[i] > tmp) {
            tmp = score[i];
        }
    }
    return tmp;
}

int main(void) {
    int score[10]= { 1, 10, 100, 20, 30, 40, 99, 8, 9, 11 };
    int n = 10;
    
    int result = find_array_max(score, n);
    printf("결과: %d\n", result);
    return 0;
}




// gcc ./findScore.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out