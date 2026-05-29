/*
    프로그램 내용: 인접 행렬을 이용한 그래프의 연결 성분 탐색 프로그램 (11.10)
    실습일: 26.05.29
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VTXS 256

// 오류 메시지를 출력하고 프로그램을 종료
void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

typedef char VtxData;
int adj[MAX_VTXS][MAX_VTXS];
int vsize;
VtxData vdata[MAX_VTXS];

// 그래프가 비어 있는지 확인
int is_empty_graph() { return (vsize == 0); }
// 그래프 정점 배열이 가득 찼는지 확인
int is_full_graph() { return (vsize >= MAX_VTXS); }

// 그래프를 빈 인접 행렬로 초기화
void init_graph()
{
    int i, j;
    vsize = 0;
    for (i = 0; i < MAX_VTXS; i++)
        for (j = 0; j < MAX_VTXS; j++)
            adj[i][j] = 0;
}

// 그래프에 새 정점을 추가
void insert_vertex(VtxData name)
{
    if (is_full_graph())
        error("Error: 그래프 정점의 개수 초과\n");
    else
        vdata[vsize++] = name;
}

// 방향 간선을 인접 행렬에 추가
void insert_edge(int u, int v, int val)
{
    adj[u][v] = val;
}

// 무방향 간선을 인접 행렬에 추가
void insert_edge2(int u, int v, int val)
{
    adj[u][v] = adj[v][u] = val;
}

// 인접 행렬 그래프를 화면에 출력
void print_graph(char* msg)
{
    int i, j;
    printf("%s", msg);
    printf("%d\n", vsize);
    for (i = 0; i < vsize; i++) {
        printf("%c ", vdata[i]);
        for (j = 0; j < vsize; j++)
            printf(" %3d", adj[i][j]);
        printf("\n");
    }
}

int visited[MAX_VTXS];

// 모든 정점의 방문 표시를 초기화
void reset_visited()
{
    int i;
    for (i = 0; i < vsize; i++)
        visited[i] = 0;
}

int label[MAX_VTXS];

// 깊이 우선 탐색으로 연결 성분 번호를 표시
void labelDFS(int v, int color)
{
    int w;

    visited[v] = 1;
    label[v] = color;
    printf("%c ", vdata[v]);

    for (w = 0; w < vsize; w++)
        if (adj[v][w] != 0 && visited[w] == 0)
            labelDFS(w, color);
}

// 그래프의 연결 성분을 찾아 개수와 라벨을 출력
void find_connected_component()
{
    int i, count = 0;

    reset_visited();
    for (i = 0; i < vsize; i++) {
        if (visited[i] == 0)
            labelDFS(i, ++count);
    }

    printf("\n그래프 연결성분 개수 = %d\n", count);
    for (i = 0; i < vsize; i++)
        printf(" %c=%d ", vdata[i], label[i]);
    printf("\n");
}

// 연결 성분 테스트용 그래프를 만들고 탐색
void main()
{
    int i;

    init_graph();
    for (i = 0; i < 5; i++)
        insert_vertex('A' + i);

    insert_edge2(1, 0, 1);
    insert_edge2(2, 0, 1);
    insert_edge2(3, 4, 1);

    print_graph("그래프(연결성분테스트)\n");
    find_connected_component();
}

// gcc ./11_10.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
