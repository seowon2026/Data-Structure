/*
    프로그램 내용: 쉘 정렬 함수 (13.5)
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

// gap 만큼 떨어진 요소들을 삽입 정렬로 정렬하는 함수
static void sortGapInsertion ( int list[], int first, int last, int gap )
{
    int i, j, key;
    for(i=first+gap; i<=last; i+=gap){
        key = list[i];
        for( j=i-gap ; j>=first && key<list[j] ; j-= gap )
            list[j+gap]=list[j];
        list[j+gap]=key;
    }
}

void shell_sort ( int list[], int n )
{
    int i, gap, count=0;
    for( gap=n/2; gap>0; gap = gap/2 ) {
        if( (gap%2) == 0 ) gap++;
        for( i=0 ; i<gap ; i++ )
            sortGapInsertion( list, i, n-1, gap );
        printStep(list, n, ++count);
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
    shell_sort( list, n );
    printArray( list, n, "ShellSort " );
}

// gcc ./13장/program13_5.c -o ./program13_5.out && clear && ./program13_5.out
