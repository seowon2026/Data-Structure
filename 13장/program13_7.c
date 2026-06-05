/*
    프로그램 내용: 퀵 정렬 함수 (13.7)
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

int partition ( int list[], int left, int right )
{
    int tmp;
    int low = left+1;
    int high = right;
    int pivot = list[left];
    while(low < high) {
        for ( ; low<right && list[low] < pivot ; low++);
        for ( ; high>left && list[high] > pivot ; high--);
        if ( low < high )
            SWAP(list[low],list[high],tmp);
    }
    SWAP(list[left],list[high],tmp);
    return high;
}

void quick_sort ( int list[], int left, int right )
{
    int q;
    if( left<right ) {
        q = partition(list,left,right);
        quick_sort ( list, left, q-1);
        quick_sort ( list, q+1, right);
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
    quick_sort( list, 0, n-1 );
    printArray( list, n, "QuickSort " );
}

// gcc ./13장/program13_7.c -o ./program13_7.out && clear && ./program13_7.out
