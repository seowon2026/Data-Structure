/*
    프로그램 내용: 선형 조사를 위한 해시 맵 프로그램 (14.7)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 13

typedef struct Record {
    char key[128];
    char value[128];
} Record ;

Record ht[TABLE_SIZE];

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

void init_map ( )
{
    int i;
    for ( i=0 ; i<TABLE_SIZE ; i++ )
        ht[i].key[0] = ht[i].value[0] = '\0';
}

void print_map ( )
{
    int i;
    for( i=0 ; i<TABLE_SIZE ; i++ )
        printf("%2d] %s = %s\n", i, ht[i].key, ht[i].value);
}

void add_record( char* key, char* value )
{
    int i, hashValue;
    hashValue = i = hash_function( key );
    while( ht[i].key[0] != '\0' ) {
        if( strcmp( ht[i].key, key ) == 0 ) {
            printf("[%s] 탐색키가 중복되었습니다.\n", key);
            return;
        }
        i = (i+1) % TABLE_SIZE;
        if( i == hashValue ) break;
    }
    strcpy(ht[i].key, key);
    strcpy(ht[i].value, value);
}

Record* search_record( char *key )
{
    int i, hashValue;
    hashValue = i = hash_function( key );
    while( ht[i].key[0] != '\0' ) {
        if( strcmp( ht[i].key, key ) == 0 ) {
            printf("[%s] 탐색성공 ", key);
            printf("%2d] %s = %s\n", i, ht[i].key, ht[i].value);
            return &ht[i];
        }
        i = (i+1) % TABLE_SIZE;
        if( i == hashValue ) break;
    }
    printf("[%s] 탐색실패: 찾는 값이 테이블에 없음\n", key);
    return NULL;
}

void main()
{
    init_map( );
    add_record( "do", "반복" );
    add_record( "for", "반복" );
    add_record( "if", "분기" );
    add_record( "case", "분기" );
    add_record( "else", "분기" );
    add_record( "return", "반환" );
    add_record( "function", "함수" );
    print_map( );
    search_record( "return" );
    search_record( "function" );
    search_record( "class" );
}

// gcc ./14장/program14_7.c -o ./program14_7.out && clear && ./program14_7.out
