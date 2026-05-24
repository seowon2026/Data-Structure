/*
    프로그램 내용: 최대 힙 트리 테스트 프로그램
    실습일 : 26.05.22
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_NODE 200

typedef int HNode;

#define Key(n) (n)
#define Parent(i) (heap[(i) / 2])
#define Left(i) (heap[(i) * 2])
#define Right(i) (heap[(i) * 2 + 1])

HNode heap[MAX_HEAP_NODE];
int heap_size;

void error(char str[])
{
    printf("%s\n", str);
    exit(1);
}

void init_heap(void) { heap_size = 0; }
int is_empty_heap(void) { return heap_size == 0; }
int is_full_heap(void) { return heap_size == MAX_HEAP_NODE - 1; }
HNode find_heap(void) { return heap[1]; }

void insert_heap(HNode n)
{
    int i;

    if (is_full_heap())
        return;

    i = ++heap_size;
    while (i != 1 && Key(n) > Key(Parent(i))) {
        heap[i] = Parent(i);
        i /= 2;
    }
    heap[i] = n;
}

HNode delete_heap(void)
{
    HNode hroot, last;
    int parent = 1, child = 2;

    if (is_empty_heap())
        error("Heap is empty");

    hroot = heap[1];
    last = heap[heap_size--];

    while (child <= heap_size) {
        if (child < heap_size && Key(Left(parent)) < Key(Right(parent)))
            child++;

        if (Key(last) >= Key(heap[child]))
            break;

        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = last;
    return hroot;
}

void print_heap(void)
{
    int i, level;

    for (i = 1, level = 1; i <= heap_size; i++) {
        if (i == level) {
            printf("\n");
            level *= 2;
        }
        printf("%2d ", Key(heap[i]));
    }
    printf("\n-----------");
}

int main(void)
{
    init_heap();

    insert_heap(2);
    insert_heap(5);
    insert_heap(4);
    insert_heap(8);
    insert_heap(9);
    insert_heap(3);
    insert_heap(7);
    insert_heap(3);
    print_heap();

    delete_heap();
    print_heap();

    delete_heap();
    print_heap();
    printf("\n");

    return 0;
}

// gcc ./10_4.c -o ./start.out && clear && chmod +x ./start.out && ./start.out