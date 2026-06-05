/*
    프로그램 내용: 삽입 정렬 함수 (13.2)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>

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

void insertion_sort ( int list[], int n )
{
    int i, j, key;
    for(i=1; i<n; i++){
        key = list[i];
        for(j=i-1 ; j>=0 && list[j]> key ; j--)
            list[j+1] = list[j];
        list[j+1] = key;
        printStep(list, n, i);
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
    insertion_sort( list, n );
    printArray( list, n, "Insertion " );
}

// gcc ./13장/program13_2.c -o ./program13_2.out && clear && ./program13_2.out
