/*
    프로그램 내용: 연결 큐로 양의 정수를 저장하고 출력하는 프로그램 (연습문제 11번)
    실습일 : 26.05.02
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Queue {
    Node *front;
    Node *rear;
} Queue;

// 큐를 초기화하는 함수
void init_queue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

// 큐가 비어 있는지 확인하는 함수
int is_empty(Queue *q) {
    return q->front == NULL;
}

// 큐의 뒤쪽에 데이터를 삽입하는 함수
void enqueue(Queue *q, int value) {
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("메모리 할당 실패\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;

    if (is_empty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// 큐의 모든 데이터를 출력하는 함수
void print_queue(Queue *q) {
    Node *current = q->front;

    while (current != NULL) {
        printf("%d->", current->data);
        current = current->next;
    }

    printf("NULL\n");
}

// 큐에 할당된 모든 메모리를 해제하는 함수
void free_queue(Queue *q) {
    Node *current = q->front;
    Node *temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    q->front = NULL;
    q->rear = NULL;
}

// 양의 정수를 입력받아 큐에 저장하고 출력하는 메인 함수
int main(void) {
    Queue q;
    int num;

    init_queue(&q);

    while (1) {
        printf("양의 정수를 입력하세요(종료: -1): ");
        scanf("%d", &num);

        if (num == -1) {
            break;
        }

        if (num > 0) {
            enqueue(&q, num);
        }
    }
    printf("\n");
    print_queue(&q);
    free_queue(&q);
    return 0;
}

// gcc ./practice-11.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out