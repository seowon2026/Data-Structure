/*
    프로그램 내용: 병합 정렬 함수 (13.6)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1024

void printArray(int arr[], int n, char *str)
{
    int i;
    printf("%s ", str);
    for( i = 0; i<n; i++) printf("%3d", arr[i]);
    printf("\n");
}

static void merge(int list[], int left, int mid, int right)
{
    int i, j, k = left, l;
    static int sorted[MAX_SIZE];
    // 병합 정렬된 리스트의 병합
    for( ;left<=mid && mid<right ; ) 
        sorted[k++] = (list[i]<list[j]) ? list[i++] : list[j++];
    if( i > mid )
        for( l = j ; l<=right ; l++)
            sorted[k++] = list[l];
    else 
        for( l = i ; l<=mid ; l++)
            sorted[k++] = list[l];
    for( l = left ; l<=right ; l++)
        list[l] = sorted[l];
}

void merge_sort(int list[], int left, int right)
{
    if (left < right) {
        int mid = (left + right) / 2;
        merge_sort(list, left, mid);
        merge_sort(list, mid+1, right);
        merge(list, left, mid, right);
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
    merge_sort( list, 0, n-1 );
    printArray( list, n, "MergeSort " );
}

// gcc ./13장/program13_6.c -o ./program13_6.out && clear && ./program13_6.out
