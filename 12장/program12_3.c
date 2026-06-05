/*
    프로그램 내용: Kruskal의 최소비용 신장트리 프로그램 (12.3)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VTXS 256
#define INF 9999
#define MAX_HEAP_NODE 200

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

/* ==================== Union-Find (from 프로그램 12.2) ==================== */
int parent[MAX_VTXS];
int set_size;

void init_set(int nSets)
{
    int i;
    set_size = nSets;
    for (i = 0; i < nSets; i++)
        parent[i] = -1;
}

int find_set(int id)
{
    while (parent[id] >= 0)
        id = parent[id];
    return id;
}

void union_set(int s1, int s2)
{
    parent[s1] = s2;
    set_size--;
}

/* ==================== Heap (우선순위 큐 for edges) ==================== */
typedef struct {
    int key;   // 가중치
    int v1;
    int v2;
} HNode;

HNode heap[MAX_HEAP_NODE];
int heap_size;

void init_heap() {
    heap_size = 0;
}

void insert_heap(HNode n) {
    int i = ++heap_size;
    while (i > 1 && n.key < heap[i/2].key) {
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = n;
}

HNode delete_heap() {
    int parent, child;
    HNode item, temp;
    if (heap_size == 0) {
        HNode err = {INF, -1, -1};
        return err;
    }
    item = heap[1];
    temp = heap[heap_size--];
    parent = 1;
    child = 2;
    while (child <= heap_size) {
        if (child < heap_size && heap[child].key > heap[child+1].key)
            child++;
        if (temp.key <= heap[child].key) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}

/* ==================== 프로그램 12.3 Kruskal ==================== */
void Kruskal()
{
    int i, j, edgeAccepted = 0, uset, vset;
    HNode e;

    init_heap();
    init_set(vsize);

    for (i = 0; i < vsize - 1; i++)
        for (j = i + 1; j < vsize; j++)
            if (adj[i][j] < INF) {
                e.key = adj[i][j];
                e.v1 = i;
                e.v2 = j;
                insert_heap(e);
            }

    while (edgeAccepted < vsize - 1) {
        e = delete_heap();
        uset = find_set(e.v1);
        vset = find_set(e.v2);
        if (uset != vset) {
            printf("간선 추가 : %c - %c (%d)\n", vdata[e.v1], vdata[e.v2], e.key);
            union_set(uset, vset);
            edgeAccepted++;
        }
    }
}

void main()
{
    load_wgraph("wgraph.txt");
    printf("MST By Kruskal's Algorithm\n");
    Kruskal();
}

// gcc ./12장/program12_3.c -o ./program12_3.out && clear && ./program12_3.out
