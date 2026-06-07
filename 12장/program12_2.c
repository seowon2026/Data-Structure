/*
    프로그램 내용: Union-find 연산의 구현 (12.2)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VTXS 256

int parent[MAX_VTXS];   // 각 노드의 부모노드 인덱스
int set_size;           // 전체 집합의 개수

void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

void init_set ( int nSets)
{
    int i;
    set_size = nSets;
    for( i=0 ; i<nSets ;i++ )
        parent[i] = -1;     // 맨 처음에는 모든 정점이 각각 고유의 집합
}

int find_set( int id)
{
    while ( parent[id] >= 0 ) id = parent[id];
    return id;
}

void union_set(int s1, int s2)
{
    parent[s1] = s2;
    set_size--;
}

void main()
{
    int i;
    int n = 6;

    init_set(n);
    printf("초기 집합 수 = %d\n", set_size);

    union_set( find_set(4), find_set(5) );
    printf("union(4,5) 후 집합 수 = %d\n", set_size);

    union_set( find_set(3), find_set(5) );
    printf("union(3,5) 후 집합 수 = %d\n", set_size);

    printf("\n각 정점의 대표(루트) 번호:\n");
    for (i = 0; i < n; i++) {
        printf("  find_set(%d) = %d\n", i, find_set(i));
    }

    printf("\n[프로그램 12.2] Union-find 연산 테스트 완료\n");
}

// gcc ./12장/program12_2.c -o ./program12_2.out && clear && ./program12_2.out
