/*
    프로그램 내용: 해싱을 이용한 탐색 (14.4)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 13

int transform(char *key)
{
    int number=0;
    while (*key != '\0') number += (*key++);
    return number;
}

int hash_function(char *key)
{
    return transform(key) % TABLE_SIZE;
}

void main()
{
    char *keys[] = {"do", "for", "if", "case", "else", "return", "function"};
    int i;
    printf("해시 함수 테스트 (TABLE_SIZE=%d)\n", TABLE_SIZE);
    for(i=0; i<7; i++) {
        int h = hash_function(keys[i]);
        printf("%s -> hash = %d\n", keys[i], h);
    }
}

// gcc ./program14_4.c -o ./program14_4.out && clear && ./program14_4.out
