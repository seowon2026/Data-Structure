/*
    프로그램 내용: 힙 정렬 프로그램
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

void print_array(int a[], int n, char *msg)
{
    int i;

    printf("%s: ", msg);
    for (i = 0; i < n; i++)
        printf("%3d", a[i]);
    printf("\n");
}

int main(void)
{
    int i, data[10];

    for (i = 0; i < 10; i++)
        data[i] = rand() % 100;

    print_array(data, 10, "Before sort");
    init_heap();

    for (i = 0; i < 10; i++)
        insert_heap(data[i]);

    for (i = 9; i >= 0; i--)
        data[i] = Key(delete_heap());

    print_array(data, 10, "After sort");

    return 0;
}


// gcc ./10_5.c -o ./start.out && clear && chmod +x ./start.out && ./start.out