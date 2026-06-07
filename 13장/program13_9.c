/*
    프로그램 내용: 힙 정렬 프로그램 (13.9)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>

#define SWAP(x,y,t)  ((t)=(x), (x)=(y), (y)=(t))

void printArray(int arr[], int n, char *str)
{
    int i;
    printf("%s ", str);
    for( i = 0; i<n; i++) printf("%3d", arr[i]);
    printf("\n");
}

void adjust ( int list[], int root, int n )
{
    int child, temp;
    temp = list[root];
    child = 2 * root;
    while( child <= n ) {
        if ( (child < n) && (list[child] < list[child+1]) )
            child++;
        if ( temp > list[child] )
            break;
        list[child/2] = list[child];
        child *= 2;
    }
    list[child/2] = temp;
}

void heap_sort ( int list[], int n )
{
    int i, temp;
    for( i = n/2 ; i>0 ; i-- )
        adjust ( list, i, n );
    for( i = n ; i>1 ; i-- ) {
        SWAP( list[1], list[i], temp);
        adjust ( list, 1, i-1 );
    }
}

void main()
{
    int list[] = { 0, 5, 3, 8, 4, 9, 1, 6, 2, 7 }; // index 1 based for heap
    int n = 9;
    int org[10];
    int i;
    for(i=1; i<=n; i++) org[i] = list[i];
    printArray( &org[1], 9, "Original " );
    heap_sort( list, n );
    printArray( &list[1], 9, "HeapSort " );
}

// gcc ./program13_9.c -o ./program13_9.out && clear && ./program13_9.out
