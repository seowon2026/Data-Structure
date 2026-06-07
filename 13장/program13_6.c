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
    // 분할 정렬된 list의 병합
    for( i=left, j=mid+1 ; i<=mid && j<=right ; )
        sorted[k++] = (list[i]<list[j]) ? list[i++] : list[j++];
    // 한쪽에 남아 있는 레코드의 일괄 복사
    if( i > mid )
        for( l=j ; l<=right ; l++, k++ )
            sorted[k] = list[l];
    else 
        for( l=i ; l<=mid ; l++, k++ )
            sorted[k] = list[l];
    // 배열 sorted[]의 리스트를 배열 list[]로 다시 복사
    for( l=left ; l<=right ; l++ )
        list[l] = sorted[l];
}

// 병합 정렬 알고리즘을 이용해 int 배열을 오름차순으로 정렬하는 함수
void merge_sort ( int list[], int left, int right )
{
    if( left<right ) {
        int mid = (left+right)/2;
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
