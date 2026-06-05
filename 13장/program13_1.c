/*
    프로그램 내용: 선택 정렬 함수와 전체 선택 정렬 프로그램 (13.1)
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

// 선택 정렬 함수
void selection_sort ( int list[], int n )
{
    int i, j, least, tmp;
    for( i=0 ; i<n-1 ; i++ ) {
        least = i;
        for(j=i+1; j<n; j++)
            if(list[j]<list[least]) least = j;
        SWAP(list[i],list[least],tmp);
        printStep(list, n, i+1);
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
    selection_sort( list, n );
    printArray( list, n, "Selection " );
}

// gcc ./13장/program13_1.c -o ./program13_1.out && clear && ./program13_1.out
