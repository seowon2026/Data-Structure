/*
    프로그램 내용: 학생 정보 큐 테스트 프로그램 (5-9)
	실습일 : 26.04.17
	학번 : 202311420
	실습자 : 연승현
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    int id;             // 학번
    char name[32];      // 이름
    char dept[32];      // 소속 학과
} Student;

typedef Student Element;

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
        printf("\n\t%-15d %-10s %-20s",
               p->data.id, p->data.name, p->data.dept);

    printf("\n");
}

Student get_student(int id, char* name, char* dept)
{
    Student s;

    s.id = id;
    strcpy(s.name, name);
    strcpy(s.dept, dept);

    return s;
}

void main()
{
    init_queue();

    enqueue(get_student(2018130007, "홍길동", "컴퓨터공학과"));
    enqueue(get_student(2018130100, "이순신", "기계공학과"));
    enqueue(get_student(2018130135, "김연아", "체육학과"));
    enqueue(get_student(2018130135, "홍희", "법학과"));

    print_queue("연결된 학생큐(4명 삽입)");

    dequeue();

    print_queue("연결된 학생큐(1명 삭제)");

    destroy_queue();
}


// gcc ./studentList.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out