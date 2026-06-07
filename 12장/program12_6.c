/*
    프로그램 내용: Floyd의 최단 경로 프로그램 (12.6)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VTXS 256
#define INF 9999

typedef char VtxData;
int adj[MAX_VTXS][MAX_VTXS];
int vsize;
VtxData vdata[MAX_VTXS];

void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

int is_empty_graph() { return (vsize == 0); }
int is_full_graph() { return (vsize >= MAX_VTXS); }

void init_graph()
{
    int i, j;
    vsize = 0;
    for (i = 0; i < MAX_VTXS; i++)
        for (j = 0; j < MAX_VTXS; j++)
            adj[i][j] = 0;
}

void insert_vertex(VtxData name)
{
    if (is_full_graph())
        error("Error: 그래프 정점의 개수 초과\n");
    else
        vdata[vsize++] = name;
}

void insert_edge(int u, int v, int val)
{
    adj[u][v] = val;
}

void insert_edge2(int u, int v, int val)
{
    adj[u][v] = adj[v][u] = val;
}

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

/* ==================== 프로그램 12.6 Floyd의 최단 경로 ==================== */
int A[MAX_VTXS][MAX_VTXS];  // 최단경로 거리

void printA( )
{
    int i, j;
    printf("=======================\n");
    for( i=0 ; i<vsize ; i++ ){
        for(j=0; j<vsize; j++ ) {
            if (A[i][j] == INF ) printf(" INF");
            else printf("%4d ", A[i][j]);
        }
        printf("\n");
    }
    printf("=======================\n");
}

void shortest_path_floyd( )
{
    int i, j, k;
    for( i=0 ; i<vsize ; i++ )
        for( j=0 ; j<vsize ; j++ )
            A[i][j] = adj[i][j];

    for(k=0 ; k<vsize ; k++ ) {
        for( i=0 ; i<vsize ; i++ )
            for( j=0 ; j<vsize ; j++ ) {
                if (A[i][k] + A[k][j] < A[i][j] )
                    A[i][j] = A[i][k] + A[k][j];
            }
    }
}

void main()
{
    load_wgraph( "wgraph.txt" );  // 책 예제: "wgraph_sp.txt"
    print_wgraph("최단거리(wgraph.txt)\n");
    printf("Shortest Path By Floyd Algorithm\n");
    shortest_path_floyd( );
    printA();   // 진행상황(최단거리 행렬) 출력
}

// gcc ./program12_6.c -o ./program12_6.out && clear && ./program12_6.out
