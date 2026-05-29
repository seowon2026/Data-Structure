/*
    프로그램 내용: 인접 행렬로 구현된 가중치 그래프 테스트 프로그램 (12.1)
    실습일: 26.05.29
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VTXS 256
#define INF 9999

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

// 파일에서 가중치 그래프 정보를 읽어 인접 행렬에 저장
void load_wgraph(char* filename)
{
    int i, j, val, n;
    char str[80];
    FILE* fp = fopen(filename, "r");

    if (fp != NULL) {
        init_graph();
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++) {
            fscanf(fp, "%s", str);
            insert_vertex(str[0]);
            for (j = 0; j < n; j++) {
                fscanf(fp, "%d", &val);
                if (i != j && val == 0)
                    adj[i][j] = INF;
                else adj[i][j] = val;
            }
        }
        fclose(fp);
    }
}

// 가중치 그래프의 인접 행렬을 화면에 출력
void print_wgraph(char* msg)
{
    int i, j, val;
    printf("%s%d\n", msg, vsize);
    for (i = 0; i < vsize; i++) {
        printf("%c  ", vdata[i]);
        for (j = 0; j < vsize; j++) {
            val = adj[i][j];
            if (i == j) printf("  0 ");
            else if (val >= INF) printf("  - ");
            else printf("%3d ", val);
        }
        printf("\n");
    }
}

// 가중치 그래프를 파일에서 읽고 출력
void main()
{
    load_wgraph("wgraph.txt");
    print_wgraph("가중치그래프(wgraph.txt)\n");
}

// gcc ./12_1.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
