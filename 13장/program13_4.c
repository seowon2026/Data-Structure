/*
    프로그램 내용: 함수 포인터를 매개 변수로 받는 삽입 정렬 함수 (13.4)
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

// 함수 포인터를 매개변수로 받는 삽입정렬 함수
void insertion_sort_fn (int list[], int n, int (*f)(int,int))
{
    int i, j, key;
    for(i=1; i<n; i++){
        key = list[i];
        for(j=i-1 ; j>=0 && f(list[j],key) < 0 ; j--)
            list[j+1] = list[j];
        list[j+1] = key;
        printStep(list, n, i);
    }
}

int asc (int x, int y) { return y - x; }  // 오름차순
int desc (int x, int y) { return x - y; } // 내림차순

void main()
{
    int list1[] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
    int list2[] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
    int n = 9;
    int i;
    printArray( list1, n, "Original " );
    insertion_sort_fn( list1, n, asc );
    printArray( list1, n, "Ascending " );
    insertion_sort_fn( list2, n, desc );
    printArray( list2, n, "Descending " );
}

// gcc ./13장/program13_4.c -o ./program13_4.out && clear && ./program13_4.out
