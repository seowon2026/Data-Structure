/*
    프로그램 내용: 원형 큐 프로그램 (4-1)
	실습일 : 26.04.10
	학번 : 202311420
	실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef int Element;
Element data[MAX_QUEUE_SIZE];   // 요소의 배열
int front;                      // 전단
int rear;                       // 후단


// 오류 상황 처리를 위한 함수. 메세지 출력 후 프로그램 종료
void error(char* str) {
    printf("%s\n", str);
    exit(1);
}   // 프로그램 3.1의 error()함수와 동일


// 큐의 주요 연산: 공통
void init_queue() { front = rear = 0; }
int is_empty() { return front == rear; }
int is_full() { return front == (rear+1)%MAX_QUEUE_SIZE; }
int size() { return (rear-front+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE; }

void enqueue(Element val)
{
    if( is_full() )
        error(" 큐 포화 에러");
    rear = (rear+1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}

Element dequeue()
{
    if( is_empty() )
        error(" 큐 공백 에러");
    front = (front+1) % MAX_QUEUE_SIZE;
    return data[front];
}

Element peek()
{
    if( is_empty() )
        error(" 큐 공백 에러");
    return data[(front+1) % MAX_QUEUE_SIZE];
}

// 큐 테스트를 위한 코드: 요소 종류마다 수정
void print_queue(char msg[]) {
    int i, maxi = rear;
    if (front >= rear) maxi += MAX_QUEUE_SIZE;
    printf("%s[%2d]= ", msg, size());
    for( i = front+1 ; i<=maxi ; i++ )
        printf("%2d ", data[i%MAX_QUEUE_SIZE]);
    printf("\n");
}

void main()
{
    int i;

    init_queue();
    for( i=1 ; i<10 ; i++ )
        enqueue( i );
    print_queue("선형큐 enqueue 9회");

    printf("\tdequeue() --> %d\n", dequeue());
    printf("\tdequeue() --> %d\n", dequeue());
    printf("\tdequeue() --> %d\n", dequeue());

    print_queue("선형큐 dequeue 3회");
}

// gcc ./queue.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out