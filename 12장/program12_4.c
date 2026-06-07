/*
    프로그램 내용: Prim의 최소비용 신장트리 프로그램 (12.4)
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

int selected[MAX_VTXS];
int dist[MAX_VTXS];

int getMinVertex()
{
    int v, minv=0, mindist= INF;
    for( v=0 ; v<vsize ; v++ )
        if ( (selected[v] == 0) && dist[v]<mindist ) {
            mindist = dist[v];
            minv = v;
        }
    return minv;
}

void Prim()
{
    int i, u, v;

    for(i=0 ; i<vsize ; i++ ) {
        dist[i] = INF;
        selected[i] = 0;
    }
    dist[0]=0;

    for(i=0 ; i<vsize ; i++){
        u = getMinVertex();
        selected[u] = 1;
        if( dist[u] == INF ) return;
        printf("%c ", vdata[u]);
        for( v=0; v<vsize; v++)
            if( adj[u][v] != INF )
                if( (selected[v] == 0) && adj[u][v]< dist[v] )
                    dist[v] = adj[u][v];
    }
    printf("\n");
}

void main()
{
    load_wgraph("wgraph.txt");
    printf("MST By Prim's Algorithm\n");
    Prim();
}

// gcc ./program12_4.c -o ./program12_4.out && clear && ./program12_4.out
