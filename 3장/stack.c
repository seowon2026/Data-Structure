/*
    프로그램 내용: 배열을 이용한 int 스택의 구현 (3-1)
	실습일 : 26.04.03
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef int Element;

Element data[MAX_STACK_SIZE];
int top;


// 오류 상황 처리를 위한 함수, 메세지 출력 후 프로그램 종료.
void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

// 스택의 주요 연산: 공통
void init_stack() { top = -1; }
int is_empty() { return top == -1; }
int is_full() { return top == MAX_STACK_SIZE; }
int size() { return top+1; }

void push( Element e ) {
    if(is_full())
        error("스택 포화 에러");
    data[++top] = e;
}

Element pop() {
    if(is_empty()) 
        error("스택 공백 에러");
    return data[top--];
}

Element peek() {
    if (is_empty()) 
        error("스택 공백 에러");
    return data[top];
}

// 스택 테스트를 위한 코드 요소 종류마다 수정
void print_stack(char msg[]) {
    int i;
    printf("%s[%2d]= ", msg, size());
    for (i=0; i<size(); i++)
        printf("%2d ", data[i]);
    printf("\n");
}



void main(void)
{
    int i;
    init_stack();
    for(i=1; i<10; i++) {
        push(i);
    }

    print_stack("스택 push 9회");
    printf("\tpop() --> %d\n", pop());
    printf("\tpop() --> %d\n", pop());
    printf("\tpop() --> %d\n", pop());
    print_stack("스택 pop 3회");
}

// gcc ./stack.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out