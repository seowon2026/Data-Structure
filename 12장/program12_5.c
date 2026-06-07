/*
    프로그램 내용: Dijkstra의 최단 경로 프로그램 (12.5)
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

/* ==================== 프로그램 12.5 Dijkstra의 최단 경로 ==================== */
int path[MAX_VTXS];
int dist[MAX_VTXS];
int found[MAX_VTXS];

void print_step(int step)
{
    int i;
    printf(" Step%2d:", step);
    for( i=0 ; i<vsize ; i++ ) {
        if (dist[i] == INF ) printf(" INF");
        else printf("%5d ", dist[i]);
    }
    printf("\n");
}

int choose_vertex()
{
    int i, min = INF, minpos = -1;
    for( i=0 ; i<vsize ; i++ )
        if ( dist[i]< min && ! found[i] ) {
            min = dist[i];
            minpos=i;
        }
    return minpos;
}

void shortest_path_dijkstra( int start )
{
    int i, u, w;
    for( i=0 ; i<vsize ; i++ ) {
        dist[i] = adj[start][i];
        path[i] = start;
        found[i] = 0;
    }
    found[start] = 1;
    dist[start] = 0;

    for( i=0 ; i<vsize ; i++ ) {
        print_step( i + 1 );   // 진행상황 출력
        u = choose_vertex();
        found[u] = 1;
        for( w=0 ; w<vsize ; w++ ) {
            if ( found[w] == 0 ) {
                if ( dist[u] + adj[u][w] < dist[w] ) {
                    dist[w] = dist[u] + adj[u][w];
                    path[w] = u;
                }
            }
        }
    }
}

void print_shortest_path(int start, int end)
{
    int i;
    printf("최단경로: %c<--%c %c", vdata[end], vdata[start], vdata[end]);
    while (path[end] != start ) {
        printf("<-%c", vdata[path[end]]);
        end = path[end];
    }
    printf("\n");
}

void main()
{
    int i;
    load_wgraph( "wgraph.txt" );  // 책 예제: "wgraph_sp.txt"
    // print_wgraph("최단거리(wgraph.txt)\n");
    printf("Shortest Path By Dijkstra Algorithm\n");
    shortest_path_dijkstra( 0 );
    for ( i = 1; i<vsize; i++ )
        print_shortest_path(0, i); // 0부터 i까지의 최단경로 출력
}

// gcc ./program12_5.c -o ./program12_5.out && clear && ./program12_5.out
