/*
    프로그램 내용: 인접 행렬을 이용한 그래프 표현 프로그램 예(11-2)
    실습일: 26.05.29
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_VTXS  256
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

// 스택의 현재 내용을 출력
void print_stack(char msg[])
{
    int i;
    printf("%s[%2d]= ", msg, size());
    for (i = 0; i < size(); i++)
        printf("%2d", data[i]);
    printf("\n");
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

// 예제 그래프를 만들고 출력
void main()
{
    int i;

    init_graph();
    for (i = 0; i < 4; i++)
        insert_vertex('A' + i);

    insert_edge2(0, 1, 1);
    insert_edge2(0, 3, 1);
    insert_edge2(1, 2, 1);
    insert_edge2(1, 3, 1);
    insert_edge2(2, 3, 1);
    print_graph("그래프(인접행렬)\n");
}
// gcc ./11_2.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
