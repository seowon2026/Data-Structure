/*
    프로그램 내용: 후위 표기 수식의 계산 프로그램 (3-4)
	실습일 : 26.04.03
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef double Element;

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
int is_full() { return top == MAX_STACK_SIZE-1; }
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

double calc_postfix( char expr[] )
{
    char c;
    int i = 0;
    double val, val1, val2;

    init_stack();
    while (expr[i] != '\0') {
        c = expr[i++];
        if (c >= '0' && c <= '9') {
            val = c - '0';
            push(val);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') {
            val2 = pop();
            val1 = pop();
            switch (c) {
                case '+': push(val1 + val2); break;
                case '-': push(val1 - val2); break;
                case '*': push(val1 * val2); break;
                case '/': push(val1 / val2); break;
            }
        }
    }
    return pop();
}

void main()
{
    char expr[2][80] = { "8 2 / 3 - 3 2 * +", "1 2 / 4 * 1 4 / *" };

    printf("수식: %s = %1f\n", expr[0], calc_postfix(expr[0]));
    printf("수식: %s = %1f\n", expr[1], calc_postfix(expr[1]));
}
// gcc ./postfix.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out