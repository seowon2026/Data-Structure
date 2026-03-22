/*
    프로그램 내용: 배열의 정수를 입력받아 순차적으로 찾아 출력하는 프로그램 (프로그램1.3 응용)
	실습일 : 26.03.13
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>

int sequential_search(int list[], int n, int key) {
    int i;
    for(int i=0; i<n; i++) 
        if(list[i]==key) 
            return i;
    return -1;
    
}

int main() {
    int list[10] = { 1, 32, 3434, 400, 1000, 2, 999, 777, 9, 10000 };
    int n=10, key, result;
    
    printf("찾는 값 : ");
    scanf("%d", &key);

    result = sequential_search(list, n, key);

    if (result != -1) {
        printf("찾는 정수가 %d번 인덱스에 존재함\n", result);
    } else {
        printf("찾는 정수가 없습니다.\n");
    }

    return 0;
}

// gcc ./sequential.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out