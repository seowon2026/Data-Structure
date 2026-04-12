/*
    프로그램 내용: 괄호 검사를 수행한 후 중위 표기 수식을 후위 표기 수식으로 변환하고 계산하는 프로그램
    실습일 : 26.04.12
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100

typedef int Element;
Element data[MAX_STACK_SIZE];
int top;
char postfix_result[MAX_EXPR_SIZE];


// 오류 메시지를 출력하고 프로그램을 종료
void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

// 스택을 빈 상태로 초기화
void init_stack() { top = -1; }
// 스택이 비어 있는지 확인
int is_empty() { return top == -1; }
// 스택이 가득 찼는지 확인
int is_full() { return top == MAX_STACK_SIZE-1; }
// 현재 스택에 저장된 원소 수를 반환
int size() { return top+1; }

// 스택의 맨 위에 원소를 삽입
void push( Element e ) {
    if(is_full())
        error("스택 포화 에러");
    data[++top] = e;
}

// 스택의 맨 위 원소를 꺼내 반환
Element pop() {
    if(is_empty()) 
        error("스택 공백 에러");
    return data[top--];
}

// 스택의 맨 위 원소를 제거하지 않고 반환
Element peek() {
    if (is_empty()) 
        error("스택 공백 에러");
    return data[top];
}

// 현재 스택의 내용을 출력
void print_stack(char msg[]) {
    int i;
    printf("%s[%2d]= ", msg, size());
    for (i=0; i<size(); i++)
        printf("%2d ", data[i]);
    printf("\n");
}

// 수식의 괄호 짝이 올바른지 검사
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


// 후위 표기 수식을 계산해 결과를 반환
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


// 연산자의 우선순위를 반환
int precedence( char op )
{
    switch (op) {
        case '(' : case ')' : return 0;
        case '+' : case '-' : return 1;
        case '*' : case '/' : return 2;
    }
    return -1;
}

// 중위 표기 수식을 후위 표기 수식으로 변환
void infix_to_postfix( char expr[] )
{
    int i = 0;
    int j = 0;
    char c, op;

    postfix_result[0] = '\0';
    init_stack();
    while( expr[i] != '\0' ) {
        c = expr[i++];
        if (c == ' ')
            continue;
        if ((c>='0' && c<='9')) {
            printf("%c ", c);
            postfix_result[j++] = c;
            postfix_result[j++] = ' ';
        }
        else if( c=='(' )
            push( c );
        else if( c==')' ) {
            while (is_empty() == 0) {
                op = pop();
                if( op=='(' ) break;
                else {
                    printf("%c ", op);
                    postfix_result[j++] = op;
                    postfix_result[j++] = ' ';
                }
            }
        }
        else if( c=='+' || c=='-' || c=='*' || c=='/' ){
            while ( is_empty() == 0 ) {
                op = peek();
                if (precedence(c) <= precedence(op)) {
                    printf("%c ", op);
                    postfix_result[j++] = op;
                    postfix_result[j++] = ' ';
                    pop();
                }
                else break;
            }
            push( c );
        }
    }

    while ( is_empty()==0 ) {
        op = pop();
        printf( "%c ", op );
        postfix_result[j++] = op;
        postfix_result[j++] = ' ';
    }

    if (j > 0)
        postfix_result[j-1] = '\0';
    else
        postfix_result[j] = '\0';

    printf("\n");
}


// 키보드로 수식을 입력받아 검사, 변환, 계산을 순서대로 수행
int main() {
    char expr[MAX_EXPR_SIZE];
    int err;

    printf("괄호가 포함된 중위표기 수식을 입력하세요: ");
    scanf("%s", expr);

    err = check_matching(expr);

    if (err == 0) {
        printf("정상: %s\n", expr);
        printf("후위표기 수식: ");
        infix_to_postfix(expr);
        printf("계산 결과: %.2f\n", calc_postfix(postfix_result));
    }
    else printf("오류: %s (조건%d 위반)\n", expr, err);
    return 0;
}


// gcc ./integration.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out