/*
    프로그램 내용: 미팅 중개 프로그램
    실습일 : 26.04.23
    학번 : 202311420
    실습자 : 연승현
*/	

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100
#define NAME_LEN 50

// 학생 이름 문자열 타입
typedef char Element[NAME_LEN];

// 원형 큐 구조체
typedef struct CircularQueue {
    Element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

// 오류 출력 후 종료
void error(char* str) {
    printf("%s\n", str);
    exit(1);
}

// 큐 초기화
void init_queue(Queue *q) {
    q->front = 0;
    q->rear  = 0;
}

// 큐가 비어 있는지 검사
int is_empty(Queue *q) {
    return q->front == q->rear;
}

// 큐가 가득 찼는지 검사
int is_full(Queue *q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

// 큐에 저장된 요소 개수
int size(Queue *q) {
    return (q->rear - q->front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

// 큐에 요소 삽입
void enqueue(Queue *q, Element val) {
    if (is_full(q))
        error("큐가 가득 찼습니다.");
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    strncpy(q->data[q->rear], val, NAME_LEN - 1);
    q->data[q->rear][NAME_LEN - 1] = '\0';
}

// 큐에서 요소 삭제 후 반환
Element* dequeue(Queue *q) {
    if (is_empty(q))
        error("큐가 비어 있습니다.");
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return &(q->data[q->front]);
}

// 큐 맨 앞 요소 반환 (삭제 없음)
Element* peek(Queue *q) {
    if (is_empty(q))
        error("큐가 비어 있습니다.");
    return &(q->data[(q->front + 1) % MAX_QUEUE_SIZE]);
}

// 큐 내용 출력
void print_queue(Queue *q, char msg[]) {
    printf("%s: ", msg);
    if (is_empty(q)) {
        printf("(비어 있음)\n");
        return;
    }
    int i = (q->front + 1) % MAX_QUEUE_SIZE;
    while (i != (q->rear + 1) % MAX_QUEUE_SIZE) {
        printf("%s ", q->data[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf("\n");
}

// ───── 메인 함수 ─────
int main(void) {
    Queue male_q, female_q;
    init_queue(&male_q);
    init_queue(&female_q);

    char name[NAME_LEN];
    char gender[10];

    printf("미팅 주선 프로그램 입니다.\n");

    while (1) {
        printf("\n  고객의 이름은?(종료는 -1) >> ");
        if (scanf("%s", name) != 1) break;

        // 종료 조건
        if (strcmp(name, "-1") == 0) break;

        printf("  성별을 입력(남자는 m, 여자는 f) >> ");
        if (scanf("%s", gender) != 1) break;

        if (strcmp(gender, "m") == 0) {
            // 남학생 등록
            if (!is_empty(&female_q)) {
                // 여학생 큐에 대기자가 있으면 매칭
                Element *girl = dequeue(&female_q);
                printf("     커플 탄생 :  %s 과(와)  %s\n", name, *girl);
            } else {
                // 여학생 없으면 남학생 큐에 대기
                enqueue(&male_q, name);
                printf("     아직 대상자가 없습니다.\n");
            }
        } else if (strcmp(gender, "f") == 0) {
            // 여학생 등록
            if (!is_empty(&male_q)) {
                // 남학생 큐에 대기자가 있으면 매칭
                Element *boy = dequeue(&male_q);
                printf("     커플 탄생 :  %s 과(와)  %s\n", *boy, name);
            } else {
                // 남학생 없으면 여학생 큐에 대기
                enqueue(&female_q, name);
                printf("     아직 대상자가 없습니다.\n");
            }
        } else {
            printf("     잘못된 입력입니다.\n");
        }

        // 현재 대기 큐 상태 출력
        print_queue(&male_q,    "남학생 큐");
        print_queue(&female_q,  "여학생 큐");
    }

    printf("\n미팅 주선 프로그램을 종료합니다.\n");
    return 0;
}


// gcc ./meeting.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out