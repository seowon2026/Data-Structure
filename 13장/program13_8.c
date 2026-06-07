/*
    프로그램 내용: 퀵 정렬에서 partition() 함수 (13.8)
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

int partition(int list[], int left, int right)
{
	int pivot, tmp;
	int low, high;

	low = left;
	high = right + 1;
	pivot = list[left];
	do {
		do
			low++;
		while (low <= right && list[low] < pivot);
		do
			high--;
		while (high >= left && list[high] > pivot);
		if (low < high) SWAP(list[low], list[high], tmp);
	} while (low < high);

	SWAP(list[left], list[high], tmp);
	return high;
}

void main()
{
    int list[] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
    int n = 9;
    printArray( list, n, "Original " );
    int p = partition( list, 0, n-1 );
    printArray( list, n, "After Partition " );
    printf("Pivot index: %d\n", p);
}

// gcc ./13장/program13_8.c -o ./program13_8.out && clear && ./program13_8.out
