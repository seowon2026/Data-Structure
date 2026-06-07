/*
    프로그램 내용: 기수 정렬 프로그램 (13.10)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define BUCKETS 10
#define DIGITS 4
#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front, rear;
} Queue;

void init_queue(Queue *q) {
    q->front = q->rear = 0;
}

int is_empty(Queue *q) {
    return q->front == q->rear;
}

void enqueue(Queue *q, int item) {
    q->data[q->rear++] = item;
}

int dequeue(Queue *q) {
    return q->data[q->front++];
}

void printArray(int arr[], int n, char *str)
{
    int i;
    printf("%s ", str);
    for( i = 0; i<n; i++) printf("%3d", arr[i]);
    printf("\n");
}

void printStep(int arr[], int n, int val)
{
    int i;
    printf(" Step %2d = ", val);
    for( i = 0; i<n; i++) printf("%3d", arr[i]);
    printf("\n");
}

void radixSort( int list[], int n )
{
    Queue queues[BUCKETS];
    int factor=1, i, b, d;

    for( i=0 ; i<BUCKETS ; i++ )
        init_queue( &queues[i] );

    for( d=0 ; d<DIGITS ; d++ ) {
        for( i=0 ; i<n ; i++ )
            enqueue( &queues[(list[i]/factor)%10], list[i]);

        int pos = 0;
        for( b=0 ; b<BUCKETS ; b++ )
            while( !is_empty( &queues[b] ) )
                list[pos++] = dequeue( &queues[b] );

        factor *= 10;
        printStep(list, n, d+1);
    }
}

void main()
{
    int list[] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
    int n = 9;
    int org[9];
    int i;
    for(i=0; i<n; i++) org[i] = list[i];
    printArray( org, 9, "Original " );
    radixSort( list, n );
    printArray( list, n, "RadixSort " );
}

// gcc ./13장/program13_10.c -o ./program13_10.out && clear && ./program13_10.out
