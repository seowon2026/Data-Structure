/*
    프로그램 내용: 버블 정렬 함수 (13.3)
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

void printStep(int arr[], int n, int val)
{
    int i;
    printf(" Step %2d = ", val);
    for( i = 0; i<n; i++) printf("%3d", arr[i]);
    printf("\n");
}

void bubble_sort ( int list[], int n )
{
    int i, j, bChanged, tmp;
    for( i=n-1 ; i>0 ; i-- ) {
        bChanged = 0;
        for( j=0 ; j<i ; j++ ) {
            if (list[j] > list[j + 1] ) {
                SWAP(list[j],list[j+1],tmp);
                bChanged = 1;
            }
        }
        if (bChanged == 0) break;
        printStep(list, n, n - i);
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
    bubble_sort( list, n );
    printArray( list, n, "Bubble " );
}

// gcc ./program13_3.c -o ./program13_3.out && clear && ./program13_3.out
