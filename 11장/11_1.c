/*
    프로그램 내용: 인접 행렬을 이용한 그래프 데이터와 기본 연산
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

// 스택 연산을 테스트
void main()
{
    int i;
    init_stack();
    for (i = 1; i < 10; i++)
        push(i);
    print_stack("스택 push 9회");
    printf("\tpop() --> %d\n", pop());
    printf("\tpop() --> %d\n", pop());
    printf("\tpop() --> %d\n", pop());
    print_stack("스택 pop 3회");
}       // 프로그램 3.1

typedef char VtxData;              // 그래프 정점에 저장할 데이터의 자료형
int adj[MAX_VTXS][MAX_VTXS];       // 인접 행렬
int vsize;                         // 전체 정점의 개수
VtxData vdata[MAX_VTXS];           // 정점에 저장할 데이터 배열

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
// gcc ./11_1.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
