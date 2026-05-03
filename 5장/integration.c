/*
    프로그램 내용: 원형 큐 프로그램 (5-8)
	실습일 : 26.04.17
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct LinkedNode {
    Element data;                   // 데이터 영역
    struct LinkedNode* link;        // 다음 노드를 가리키는 포인터 변수
} Node;

Node* front = NULL;
Node* rear = NULL;

void error(char* str)
{
    fprintf(stderr, "%s\n", str);
    exit(1);
}


int is_empty() { return front == NULL; }

void init_queue() { front = rear = NULL; }

int size()
{
    Node *p;
    int count = 0;

    for (p = front; p != NULL; p = p->link) count++;

    return count;
}

void enqueue(Element e)
{
    Node* p = (Node*)malloc(sizeof(Node));  // 노드 동적 할당

    p->data = e;                            // 데이터 필드 초기화
    p->link = NULL;                         // 링크 필드 초기화

    if (is_empty()) front = rear = p;       // 그림 5.16의 (a)
    else {
        rear->link = p;                     // 그림 5.16 (b)의 (1)
        rear = p;                           // 그림 5.16 (b)의 (2)
    }
}

Element dequeue()
{
    Node* p;
    Element e;

    if (is_empty())
        error(" 큐 공백 에러");

    p = front;                          // 그림 5.17 (a)와 (b)의 (1)
    front = front->link;                // 그림 5.17 (a)와 (b)의 (2)

    if (front == NULL) rear = NULL;     // 그림 5.17 (b)의 (2)

    e = p->data;                        // p의 항목 복사
    free(p);                            // p를 동적 해제

    return e;                           // 복사된 항목을 반환
}

Element peek()
{
    if (is_empty())
        error(" 큐 공백 에러");

    return front->data;
}

void destroy_queue()
{
    while (is_empty() == 0)
        dequeue();
}

void print_queue(char* msg)
{
    Node *p;

    printf("%s[%2d]= ", msg, size());

    for (p = front; p != NULL; p = p->link)
        printf("%2d ", p->data);

    printf("\n");
}

void main()
{
    int i;

    init_queue();

    for (i = 1; i < 10; i++)
        enqueue(i);

    print_queue("연결된큐 enqueue 9회");

    printf("\tdequeue() --> %d\n", dequeue());
    printf("\tdequeue() --> %d\n", dequeue());
    printf("\tdequeue() --> %d\n", dequeue());

    print_queue("연결된큐 dequeue 3회");

    destroy_queue();

    print_queue("연결된큐 destroy ");
}


// gcc ./integration.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out