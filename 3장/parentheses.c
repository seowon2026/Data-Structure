/*
    프로그램 내용: 괄호 검사 프로그램 (3-3)
	실습일 : 26.04.03
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void print_stack(char msg[]) {
    int i;
    printf("%s[%2d]= ", msg, size());
    for (i=0; i<size(); i++)
        printf("%2d ", data[i]);
    printf("\n");
}

int check_matching(char expr[]) {
    int i = 0, prev;
    char ch;

    init_stack();
    while (expr[i] != '\0') {
        ch = expr[i++];
        if (ch == '[' || ch == '(' || ch == '{')
            push(ch);
        else if (ch == ']' || ch == ')' || ch == '}') {
            if (is_empty())
                return 2;               // 조건 2 위반
            prev = pop();
            if ((ch == ']' && prev != '[')
            || (ch == ')' && prev != '(')
            || (ch == '}' && prev != '{')) {
                return 3;               // 조건 3 위반
            }
        }
    }
    if (is_empty() == 0) return 1;      // 조건 1 위반
    return 0;                            // 괄호 정상
}


void main()
{
    char expr[4][80] = { "{A[(i+1)]=0;}", "if((i==0) && (j==0)",
                         "A[(i+1])=0;", "A[i] =f();}" };

    int errCode, i;

    for (i = 0; i < 4; i++) {
        errCode = check_matching(expr[i]);
        if (errCode == 0)
            printf(" 정상: %s\n", expr[i]);
        else
            printf(" 오류: %s (조건%d 위반)\n", expr[i], errCode);
    }
}

// gcc ./parentheses.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out