/*
    프로그램 내용: 인접 리스트를 이용한 그래프의 데이터와 기본 연산(11 - 4)
    실습일: 26.05.29
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS  256

// 오류 메시지를 출력하고 프로그램을 종료
void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

typedef struct GraphNode {
    int id;
    struct GraphNode* link;
} GNode;

typedef char VtxData;
GNode* adj[MAX_VTXS];
int vsize;
VtxData vdata[MAX_VTXS];

// 그래프가 비어 있는지 확인
int is_empty_graph() { return (vsize == 0); }
// 그래프 정점 배열이 가득 찼는지 확인
int is_full_graph() { return (vsize >= MAX_VTXS); }

// 그래프를 빈 인접 리스트로 초기화
void init_graph()
{
    int i;
    vsize = 0;
    for (i = 0; i < MAX_VTXS; i++)
        adj[i] = NULL;
}

// 인접 리스트의 모든 노드를 해제하고 그래프를 비움
void reset_graph()
{
    int i;
    GNode* n;

    for (i = 0; i < vsize; i++) {
        while (adj[i] != NULL) {
            n = adj[i];
            adj[i] = n->link;
            free(n);
        }
    }
    vsize = 0;
}

// 그래프에 새 정점을 추가
void insert_vertex(VtxData name)
{
    if (is_full_graph())
        error("Error: 그래프 정점의 개수 초과\n");
    else
        vdata[vsize++] = name;
}

// 인접 리스트에 방향 간선을 추가
void insert_edge(int u, int v)
{
    GNode* n = (GNode*)malloc(sizeof(GNode));
    n->link = adj[u];
    n->id = v;
    adj[u] = n;
}

// gcc ./11_4.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
