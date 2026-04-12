/*
    프로그램 내용: 미로 탐색 프로그램 (4-4)
	실습일 : 26.04.10
	학번 : 202311420
	실습자 : 연승현
*/


#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100

typedef struct {
    int x;
    int y;
} Location2D;

typedef Location2D Element;


Element data[MAX_QUEUE_SIZE];   // 요소의 배열
int front;                      // 전단
int rear;                       // 후단


/**
 * 에러 메시지 출력 후 프로그램 종료
 * @param {char*} str - 출력할 에러 메시지
 */
void error(char* str) {
    printf("%s\n", str);
    exit(1);
}


/**
 * 원형 큐를 초기화한다
 */
void init_queue() { front = rear = 0; }

/**
 * 큐가 비어있는지 확인한다
 * @returns {int} 큐가 비어있으면 1, 아니면 0
 */
int is_empty() { return front == rear; }

/**
 * 큐가 가득 찼는지 확인한다
 * @returns {int} 큐가 가득 찼으면 1, 아니면 0
 */
int is_full() { return front == (rear+1)%MAX_QUEUE_SIZE; }

/**
 * 큐에 저장된 요소의 개수를 반환한다
 * @returns {int} 큐의 크기
 */
int size() { return (rear-front+MAX_QUEUE_SIZE)%MAX_QUEUE_SIZE; }


/**
 * 큐의 후단에 요소를 추가한다
 * @param {Element} val - 추가할 요소
 * @throws 큐가 가득 찬 경우 에러 발생
 */
void enqueue(Element val)
{
    if( is_full() )
        error(" 큐 포화 에러");
    rear = (rear+1) % MAX_QUEUE_SIZE;
    data[rear] = val;
}

/**
 * 큐의 전단에서 요소를 제거 및 반환한다
 * @returns {Element} 제거된 요소
 * @throws 큐가 비어있는 경우 에러 발생
 */
Element dequeue()
{
    if( is_empty() )
        error(" 큐 공백 에러");
    front = (front+1) % MAX_QUEUE_SIZE;
    return data[front];
}

/**
 * 큐의 전단 요소를 반환한다 (제거하지 않음)
 * @returns {Element} 전단의 요소
 * @throws 큐가 비어있는 경우 에러 발생
 */
Element peek()
{
    if( is_empty() )
        error(" 큐 공백 에러");
    return data[(front+1) % MAX_QUEUE_SIZE];
}




/**
 * 덱(Double-Ended Queue)을 초기화한다
 */
void init_deque() { init_queue(); }

/**
 * 덱의 후단에 요소를 추가한다
 * @param {Element} val - 추가할 요소
 */
void add_rear(Element val) { enqueue(val); }

/**
 * 덱의 전단에서 요소를 제거 및 반환한다
 * @returns {Element} 제거된 요소
 */
Element delete_front() { return dequeue(); }

/**
 * 덱의 전단 요소를 반환한다 (제거하지 않음)
 * @returns {Element} 전단의 요소
 */
Element get_front() { return peek(); }

/**
 * 덱의 전단에 요소를 추가한다
 * @param {Element} val - 추가할 요소
 * @throws 덱이 가득 찬 경우 에러 발생
 */
void add_front(Element val)
{
    if( is_full() )
        error(" 덱 포화 에러");
    data[front] = val;
    front = (front-1+MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

/**
 * 덱의 후단에서 요소를 제거 및 반환한다
 * @returns {Element} 제거된 요소
 * @throws 덱이 비어있는 경우 에러 발생
 */
Element delete_rear()
{
    int prev = rear;
    if( is_empty() )
        error(" 덱 공백 에러");
    rear = (rear-1+MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return data[prev];
}

/**
 * 덱의 후단 요소를 반환한다 (제거하지 않음)
 * @returns {Element} 후단의 요소
 * @throws 덱이 비어있는 경우 에러 발생
 */
Element get_rear()
{
    if( is_empty() )
        error(" 덱 공백 에러");
    return data[rear];
}


#define MAZE_SIZE 6

char map[MAZE_SIZE][MAZE_SIZE] = {
    {'1', '1', '1', '1', '1', '1'},
    {'e', '0', '1', '0', '0', '1'},
    {'1', '0', '0', '0', '1', '1'},
    {'1', '0', '1', '0', '1', '1'},
    {'1', '0', '0', '0', '0', 'x'},
    {'1', '1', '1', '1', '1', '1'}
};

/**
 * 좌표 위치를 Location2D 구조체로 변환한다
 * @param {int} x - x 좌표
 * @param {int} y - y 좌표
 * @returns {Location2D} 변환된 위치 정보
 */
Location2D getLocation2D(int x, int y) {
    Location2D p;
    p.x = x;
    p.y = y;
    return p;
}

/**
 * 좌표가 미로 범위 내에 있고 이동 가능한 위치인지 확인한다
 * 이동 가능한 경우: 통로('0') 또는 목표('x')
 * @param {int} x - x 좌표
 * @param {int} y - y 좌표
 * @returns {int} 유효한 위치면 1, 아니면 0
 */
int is_valid(int x, int y) {
    if (x < 0 || y < 0 || x >= MAZE_SIZE || y >= MAZE_SIZE)
        return 0;
    else
        return (map[y][x] == '0' || map[y][x] == 'x');
}

/**
 * 깊이 우선 탐색(DFS)으로 미로를 탐색한다
 * 덱의 후단에서만 삽입/삭제하여 스택처럼 동작
 * 시작점 'e'에서 목표점 'x'까지 경로 탐색
 * @returns {int} 목표에 도달하면 1, 실패하면 0
 */
int DFS() {
    int x, y;
    Location2D here;

    init_deque();
    add_rear(getLocation2D(0, 1));

    printf("DFS: ");

    while (is_empty() == 0) {
        here = delete_rear();
        printf("(%2d,%2d)", here.x, here.y);

        x = here.x;
        y = here.y;

        if (map[y][x] == 'x')
            return 1;
        else {
            // 방문한 위치를 표시하여 중복 방문 방지
            map[y][x] = '.';

            // 상하좌우 인접한 위치를 후단에 추가 (역순으로 추가하여 탐색 순서 결정)
            if (is_valid(x - 1, y))
                add_rear(getLocation2D(x - 1, y));
            if (is_valid(x + 1, y))
                add_rear(getLocation2D(x + 1, y));
            if (is_valid(x, y - 1))
                add_rear(getLocation2D(x, y - 1));
            if (is_valid(x, y + 1))
                add_rear(getLocation2D(x, y + 1));
        }
    }
    return 0;
}

/**
 * 너비 우선 탐색(BFS)으로 미로를 탐색한다
 * 덱의 후단에 삽입, 전단에서만 삭제하여 큐처럼 동작
 * 시작점 'e'에서 목표점 'x'까지 경로 탐색
 * @returns {int} 목표에 도달하면 1, 실패하면 0
 */
int BFS() {
    int x, y;
    Location2D here;

    init_deque();
    add_rear(getLocation2D(0, 1));

    printf("BFS: ");

    while (is_empty() == 0) {
        here = delete_front();
        printf("(%2d,%2d)", here.x, here.y);

        x = here.x;
        y = here.y;

        if (map[y][x] == 'x')
            return 1;
        else {
            // 방문한 위치를 표시하여 중복 방문 방지
            map[y][x] = '.';

            // 상하좌우 인접한 위치를 후단에 추가 (FIFO 순서로 가까운 노드부터 탐색)
            if (is_valid(x - 1, y))
                add_rear(getLocation2D(x - 1, y));
            if (is_valid(x + 1, y))
                add_rear(getLocation2D(x + 1, y));
            if (is_valid(x, y - 1))
                add_rear(getLocation2D(x, y - 1));
            if (is_valid(x, y + 1))
                add_rear(getLocation2D(x, y + 1));
        }
    }
    return 0;
}

/**
 * 미로 탐색 프로그램의 진입점
 * DFS 알고리즘으로 미로를 탐색하고 결과를 출력한다
 */
void main() {
    printf("->%s\n", DFS() ? "성공" : "실패");
    // TODO: BFS 테스트 필요 시 아래 라인 활성화
    // printf("->%s\n", BFS() ? "성공" : "실패");
}


// gcc ./miro.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out