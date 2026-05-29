/*
    프로그램 내용: 그래프 위상 정렬 프로그램 (11.11)
    실습일: 26.05.29
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_VTXS 256
#define MAX_STACK_SIZE 100
typedef int Element;

Element data[MAX_STACK_SIZE];
int top;

// 오류 메시지를 출력하고 프로그램을 종료
void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

// 스택을 빈 상태로 초기화
void init_stack() { top = -1; }
// 스택이 비어 있는지 확인
int is_empty() { return top == -1; }
// 스택이 가득 찼는지 확인
int is_full() { return top == MAX_STACK_SIZE - 1; }
// 스택에 저장된 원소 개수를 반환
int size() { return top + 1; }

// 스택의 맨 위에 원소를 추가
void push(Element e) {
    if (is_full())
        error("스택 포화 에러");
    data[++top] = e;
}

// 스택의 맨 위 원소를 꺼내 반환
Element pop() {
    if (is_empty())
        error("스택 공백 에러");
    return data[top--];
}

// 스택의 맨 위 원소를 제거하지 않고 반환
Element peek() {
    if (is_empty())
        error("스택 공백 에러");
    return data[top];
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

// 진입 차수를 이용해 그래프를 위상 정렬
void topological_sort()
{
    GNode* p;
    int i, u, w, inDeg[MAX_VTXS];

    for (i = 0; i < vsize; i++) inDeg[i] = 0;
    for (i = 0; i < vsize; i++) {
        p = adj[i];
        while (p != NULL) {
            inDeg[p->id]++;
            p = p->link;
        }
    }

    init_stack();
    for (i = 0; i < vsize; i++)
        if (inDeg[i] == 0) push(i);

    while (!is_empty()) {
        w = pop();
        printf(" %c ", vdata[w]);
        for (p = adj[w]; p != NULL; p = p->link) {
            u = p->id;
            inDeg[u]--;
            if (inDeg[u] == 0) push(u);
        }
    }
    printf("\n");
}

// 위상 정렬 예제 그래프를 만들고 결과를 출력
void main()
{
    int i;

    init_graph();
    for (i = 0; i < 6; i++)
        insert_vertex('A' + i);

    insert_edge(0, 2);  insert_edge(0, 3);  insert_edge(1, 3);
    insert_edge(1, 4);  insert_edge(2, 3);  insert_edge(2, 5);
    insert_edge(3, 5);  insert_edge(4, 5);

    printf("Topological Sort:\n");
    topological_sort();
}

// gcc ./11_11.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
