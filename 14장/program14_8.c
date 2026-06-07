/*
    프로그램 내용: 체이닝을 위한 해시 맵 프로그램 (14.8)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 13

typedef struct RecordNode {
    char key[128];
    char value[128];
    struct RecordNode* link;
} Node ;

Node* ht[TABLE_SIZE];

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
        ht[i] = NULL;
}

void print_map ( )
{
    int i;
    Node* p;
    for( i=0 ; i<TABLE_SIZE ; i++ ) {
        printf("%2d] ", i);
        p = ht[i];
        while( p != NULL ) {
            printf("%s = %s -> ", p->key, p->value);
            p = p->link;
        }
        printf("\n");
    }
}

void add_record( char* key, char* value )
{
    int hashValue;
    Node* p;
    hashValue = hash_function( key );
    p = (Node*) malloc(sizeof(Node));
    strcpy(p->key, key);
    strcpy(p->value, value);
    p->link = ht[hashValue];
    ht[hashValue] = p;
}

Node* search_record( char *key )
{
    int hashValue;
    Node* p;
    hashValue = hash_function( key );
    for( p=ht[hashValue] ; p != NULL ; p = p->link ) {
        if( strcmp(p->key,key) == 0 ) {
            printf("[%s] 탐색성공 ", key);
            printf("%2d] %s = %s\n", hashValue, p->key, p->value);
            return p;
        }
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

// gcc ./program14_8.c -o ./program14_8.out && clear && ./program14_8.out
