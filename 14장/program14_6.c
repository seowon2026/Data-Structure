/*
    프로그램 내용: 문자열 탐색기의 정수 변환 및 해시 함수 (14.6)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 13   // 해시 테이블의 크기 예: 소수 13을 사용

// 문자열로 된 탐색키를 숫자로 변환 : 간단한 덧셈 방식
int transform(char *key)
{
    int number=0;
    while (*key != '\0') number += (*key++);
    return number;
}

// 해시 함수 : 제산 합수를 사용
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

// gcc ./program14_6.c -o ./program14_6.out && clear && ./program14_6.out
