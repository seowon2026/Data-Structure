/*
    프로그램 내용: 연결 리스트 기반 스택의 기본 연산을 확인하는 프로그램
    실습일 : 26.04.17
    학번 : 202311420
    실습자 : 연승현
*/


#include <stdio.h>
#include <stdlib.h>

typedef int Element;
typedef struct LinkedNode {
    Element data;               // 스택 원소를 노드 단위로 보관하기 위해 값과 링크를 함께 유지한다.
    struct LinkedNode* link;    // top 기준 삽입과 삭제 비용을 일정하게 유지하기 위해 다음 노드를 연결한다.
} Node;
Node* top = NULL;               // 전역 top 포인터로 현재 스택 상태를 모든 연산에서 공유한다.

/**
 * 치명적인 스택 오류를 즉시 보고하고 프로그램을 종료한다
 * @param str 표준 에러로 출력할 오류 메시지
 * @return 반환값 없음
 * @throws 종료 처리로 인해 함수가 복귀하지 않는다
 */
void error(char* str)
{
    fprintf(stderr, "%s\n", str);
    exit(1);
};

/**
 * 현재 스택이 비어 있는지 확인한다
 * @return 스택이 비어 있으면 참, 아니면 거짓
 */
int is_empty() { return top == NULL; }

/**
 * 스택 시작 상태를 빈 상태로 초기화한다
 * @return 반환값 없음
 */
void init_stack() { top = NULL; }

/**
 * 현재 연결된 노드 개수를 세어 스택 크기를 계산한다
 * @return 스택에 저장된 원소 개수
 */
int size(){
    Node* p;
    int count = 0;
    for (p = top; p != NULL; p = p->link) count++;
    return count;
}

/**
 * 새 노드를 top 앞에 연결해 스택에 원소를 추가한다
 * @param e 스택에 넣을 원소 값
 * @return 반환값 없음
 */
void push(Element e){
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = e;

    p->link = top;
    top = p;
}

/**
 * top 노드를 제거하고 그 값을 반환한다
 * @return 스택에서 꺼낸 원소 값
 * @throws 빈 스택에서 호출되면 오류 메시지를 출력하고 종료한다
 */
Element pop(){
    Node* p;
    Element e;
    if (is_empty()) {
        error("스택 공백 에러");
    }

    p = top;
    top = p->link;
    e = p->data;
    free(p);
    return e;
}

/**
 * top 노드의 값을 제거 없이 조회한다
 * @return 현재 top 원소 값
 * @throws 빈 스택에서 호출되면 오류 메시지를 출력하고 종료한다
 */
Element peek(){
    if (is_empty()) 
        error("스택 공백 에러");
    
    return top->data;
}

/**
 * 남아 있는 모든 노드를 제거해 스택 메모리를 정리한다
 * @return 반환값 없음
 */
void destroy_stack(){
    while (is_empty() == 0)
        pop();
}

/**
 * 스택 상태를 크기와 함께 출력해 연산 결과를 확인한다
 * @param msg 출력 앞에 붙일 설명 문자열
 * @return 반환값 없음
 */
void print_stack(char* msg)
{
    Node *p;
    printf("%s[%2d]= ", msg, size());
    for (p = top; p != NULL; p = p->link)
        printf("%2d ", p->data);
    printf("\n");
}

/**
 * 연결 리스트 기반 스택의 push, pop, destroy 동작을 순서대로 확인한다
 * @return 반환값 없음
 */
void main()
{
    int i;

    init_stack();
    for (i = 1; i < 10; i++)
        push(i);

    print_stack("연결된스택 push 9회");
    printf("\tpop() --> %d\n", pop());
    printf("\tpop() --> %d\n", pop());
    printf("\tpop() --> %d\n", pop());

    print_stack("연결된스택 pop 3회");
    destroy_stack();
    print_stack("연결된스택 destroy ");
}


// gcc ./linklist.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out