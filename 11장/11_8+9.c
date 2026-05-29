/*
프로그램 내용: 프로그램 11.8과 11.9를 조합한 너비 우선 탐색 프로그램
실습일: 26.05.29
학  번: 202311420
실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_VTXS  256
#define MAX_QUEUE_SIZE 100

// 오류 메시지를 출력하고 프로그램을 종료
void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

typedef char VtxData;
int vsize;
VtxData vdata[MAX_VTXS];

int visited[MAX_VTXS];
// 모든 정점의 방문 표시를 초기화
void reset_visited()
{
    int i;
    for (i = 0; i < vsize; i++)
        visited[i] = 0;
}

typedef int Element;
Element data[MAX_QUEUE_SIZE];
int front;
int rear;

// 큐를 빈 상태로 초기화
void init_queue() { front = rear = 0; }
// 큐가 비어 있는지 확인
int is_empty() { return front == rear; }
// 큐가 가득 찼는지 확인
int is_full() { return front == (rear + 1) % MAX_QUEUE_SIZE; }
// 큐의 뒤쪽에 원소를 추가
void enqueue(Element val)
{
    if (is_full())
        error("Error: 큐가 포화상태입니다\n");
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}
// 큐의 앞쪽 원소를 꺼내 반환
Element dequeue()
{
    if (is_empty())
        error("Error: 큐가 공백상태입니다\n");
    front = (front + 1) % MAX_QUEUE_SIZE;
    return data[front];
}

// 그래프가 비어 있는지 확인
int is_empty_graph() { return (vsize == 0); }
// 그래프 정점 배열이 가득 찼는지 확인
int is_full_graph() { return (vsize >= MAX_VTXS); }
// 그래프에 새 정점을 추가
void insert_vertex(VtxData name)
{
    if (is_full_graph())
        error("Error: 그래프 정점의 개수 초과\n");
    else
        vdata[vsize++] = name;
}

int adj_mat[MAX_VTXS][MAX_VTXS];

// 그래프를 빈 인접 행렬로 초기화
void init_mgraph()
{
    int i, j;
    vsize = 0;
    for (i = 0; i < MAX_VTXS; i++)
        for (j = 0; j < MAX_VTXS; j++)
            adj_mat[i][j] = 0;
}
// 인접 행렬에 방향 간선을 추가
void insert_medge(int u, int v, int val)
{
    adj_mat[u][v] = val;
}
// 파일에서 그래프 정보를 읽어 인접 행렬에 저장
void load_mgraph(char* filename)
{
    int i, j, val, n;
    char str[80];
    FILE* fp = fopen(filename, "r");
    if (fp != NULL) {
        init_mgraph();
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++) {
            fscanf(fp, "%s", str);
            insert_vertex(str[0]);
            for (j = 0; j < n; j++) {
                fscanf(fp, "%d", &val);
                if (val != 0)
                    insert_medge(i, j, val);
            }
        }
        fclose(fp);
    }
}

// 인접 행렬 그래프를 너비 우선 탐색
void BFS_M(int v)
{
    int w;
    visited[v] = 1;
    printf("%c ", vdata[v]);
    init_queue();
    enqueue(v);
    while (!is_empty()) {
        v = dequeue();
        for (w = 0; w < vsize; w++)
            if (adj_mat[v][w] != 0 && visited[w] == 0) {
                visited[w] = 1;
                printf("%c ", vdata[w]);
                enqueue(w);
            }
    }
}

typedef struct GraphNode {
    int id;
    struct GraphNode* link;
} GNode;

GNode* adj_list[MAX_VTXS];

// 그래프를 빈 인접 리스트로 초기화
void init_lgraph()
{
    int i;
    vsize = 0;
    for (i = 0; i < MAX_VTXS; i++)
        adj_list[i] = NULL;
}
// 인접 리스트의 모든 노드를 해제하고 그래프를 비움
void reset_lgraph()
{
    int i;
    GNode* n;

    for (i = 0; i < vsize; i++) {
        while (adj_list[i] != NULL) {
            n = adj_list[i];
            adj_list[i] = n->link;
            free(n);
        }
    }
    vsize = 0;
}
// 인접 리스트에 방향 간선을 추가
void insert_ledge(int u, int v)
{
    GNode* n = (GNode*)malloc(sizeof(GNode));
    n->link = adj_list[u];
    n->id = v;
    adj_list[u] = n;
}
// 파일에서 그래프 정보를 읽어 인접 리스트에 저장
void load_lgraph(char* filename)
{
    int i, j, val, n;
    char str[80];
    FILE* fp = fopen(filename, "r");
    if (fp != NULL) {
        init_lgraph();
        fscanf(fp, "%d", &n);
        for (i = 0; i < n; i++) {
            fscanf(fp, "%s", str);
            insert_vertex(str[0]);
            for (j = 0; j < n; j++) {
                fscanf(fp, "%d", &val);
                if (val != 0)
                    insert_ledge(i, j);
            }
        }
        fclose(fp);
    }
}

// 인접 리스트 그래프를 너비 우선 탐색
void BFS_L(int v)
{
    GNode* w;
    visited[v] = 1;

    printf("%c ", vdata[v]);
    init_queue();
    enqueue(v);
    while (!is_empty()) {
        v = dequeue();
        for (w = adj_list[v]; w != NULL; w = w->link) {
            if (!visited[w->id]) {
                visited[w->id] = 1;
                printf("%c ", vdata[w->id]);
                enqueue(w->id);
            }
        }
    }
}

// 인접 행렬과 인접 리스트의 BFS 결과를 출력
void main()
{
    load_mgraph("graph.txt");
    reset_visited();
    printf("BFS(인접행렬) ==> ");
    BFS_M(0);
    printf("\n");

    load_lgraph("graph.txt");
    reset_visited();
    printf("BFS(인접리스트) ==> ");
    BFS_L(0);
    printf("\n");

    reset_lgraph();
}

// gcc ./11_8+9.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
