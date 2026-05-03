/*
    프로그램 내용: 연결 스택으로 문자열 회문을 판별하는 프로그램 (연습문제 10번)
    실습일 : 26.05.02
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node {
    char data;
    struct Node *next;
} Node;

Node *top = NULL;

// 스택에 문자를 삽입하는 함수
void push(char ch) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }

    newNode->data = ch;
    newNode->next = top;
    top = newNode;
}

// 스택에서 문자를 꺼내는 함수
char pop(void) {
    Node *temp;
    char ch;

    if (top == NULL) {
        return '\0';
    }

    temp = top;
    ch = temp->data;
    top = top->next;

    free(temp);

    return ch;
}

// 스택이 비어 있는지 확인하는 함수
int is_empty(void) {
    return top == NULL;
}

// 남아 있는 스택 메모리를 해제하는 함수
void free_stack(void) {
    while (!is_empty()) {
        pop();
    }
}

// 문자열이 회문인지 검사하는 함수
int is_palindrome(char str[]) {
    char clean[200];
    int i;
    int len = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (isalnum((unsigned char)str[i])) {
            clean[len] = tolower((unsigned char)str[i]);
            push(clean[len]);
            len++;
        }
    }

    clean[len] = '\0';

    for (i = 0; i < len; i++) {
        if (clean[i] != pop()) {
            free_stack();
            return 0;
        }
    }

    return 1;
}

// 문자열을 입력받고 회문 여부를 출력하는 메인 함수
int main(void) {
    char str[200];

    printf("문자열을 입력하시오: ");
    fgets(str, sizeof(str), stdin);

    if (is_palindrome(str)) {
        printf("회문입니다.\n");
    } else {
        printf("회문이 아닙니다.\n");
    }

    return 0;
}


// gcc ./practice-10.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out