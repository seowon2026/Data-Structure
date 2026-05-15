/*
    프로그램 내용: 이진탐색트리 테스트 프로그램
    실습일 : 26.05.15
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>

typedef int TElement;

typedef struct BinTNode {
    TElement data;
    struct BinTNode* left;
    struct BinTNode* right;
} TNode;

TNode* root;

// 트리의 전역 루트를 NULL로 초기화
void init_tree() { root = NULL; }
// 트리가 비어있는지 여부(루트가 NULL인지) 반환
int is_empty_tree() { return root == NULL; }

// 주어진 값과 자식을 가진 새 트리 노드를 동적 할당하여 반환
TNode* create_tree(TElement val, TNode* l, TNode* r)
{
    TNode* n = (TNode*)malloc(sizeof(TNode));
    n->data = val;
    n->left = l;
    n->right = r;
    return n;
}

/* 큐 */
#define MAX_QUEUE_SIZE 100
typedef TNode* Element;

Element queue[MAX_QUEUE_SIZE];
int front, rear;

// 큐의 front와 rear 인덱스를 초기화
void init_queue()
{
    front = rear = 0;
}

// 큐가 비어있는지 여부를 반환
int is_empty()
{
    return front == rear;
}

// 큐가 가득 찼는지 여부를 반환
int is_full()
{
    return front == (rear + 1) % MAX_QUEUE_SIZE;
}

// 큐의 뒤쪽에 요소를 추가
void enqueue(Element val)
{
    if (is_full()) return;
    rear = (rear + 1) % MAX_QUEUE_SIZE;
    queue[rear] = val;
}

// 큐의 앞에서 요소를 제거하여 반환
Element dequeue()
{
    if (is_empty()) return NULL;
    front = (front + 1) % MAX_QUEUE_SIZE;
    return queue[front];
}

/* 순회 */
// 전위 순회: 노드 -> 왼쪽 -> 오른쪽 순으로 방문
void preorder(TNode* n)
{
    if (n != NULL) {
        printf("[%d] ", n->data);
        preorder(n->left);
        preorder(n->right);
    }
}

// 중위 순회: 왼쪽 -> 노드 -> 오른쪽 순으로 방문
void inorder(TNode* n)
{
    if (n != NULL) {
        inorder(n->left);
        printf("[%d] ", n->data);
        inorder(n->right);
    }
}

// 후위 순회: 왼쪽 -> 오른쪽 -> 노드 순으로 방문
void postorder(TNode* n)
{
    if (n != NULL) {
        postorder(n->left);
        postorder(n->right);
        printf("[%d] ", n->data);
    }
}

// 레벨 순회(BFS): 큐를 이용해 레벨별로 노드를 방문
void levelorder(TNode* root)
{
    TNode* n;

    if (root == NULL) return;

    init_queue();
    enqueue(root);

    while (!is_empty()) {
        n = dequeue();

        if (n != NULL) {
            printf("[%d] ", n->data);
            enqueue(n->left);
            enqueue(n->right);
        }
    }
}

/* 트리 정보 */
// 서브트리의 모든 노드 수를 재귀적으로 계산
int count_node(TNode* n)
{
    if (n == NULL) return 0;
    return 1 + count_node(n->left) + count_node(n->right);
}

// 서브트리의 단말(리프) 노드 수를 재귀적으로 계산
int count_leaf(TNode* n)
{
    if (n == NULL) return 0;
    if (n->left == NULL && n->right == NULL) return 1;
    return count_leaf(n->left) + count_leaf(n->right);
}

// 트리(서브트리)의 높이를 재귀적으로 계산하여 반환
int calc_height(TNode* n)
{
    int hLeft, hRight;

    if (n == NULL) return 0;

    hLeft = calc_height(n->left);
    hRight = calc_height(n->right);

    return (hLeft > hRight ? hLeft : hRight) + 1;
}

/* 이진탐색트리 탐색 */
// 재귀적으로 이진탐색트리에서 키를 탐색하여 노드 포인터 반환
TNode* search(TNode* n, int key)
{
    if (n == NULL) return NULL;
    else if (key == n->data) return n;
    else if (key < n->data) return search(n->left, key);
    else return search(n->right, key);
}

// 반복문을 이용해 이진탐색트리에서 키를 탐색하여 노드 포인터 반환
TNode* search_iter(TNode* n, int key)
{
    while (n != NULL) {
        if (key == n->data) return n;
        else if (key < n->data) n = n->left;
        else n = n->right;
    }

    return NULL;
}

/* 이진탐색트리 삽입 */
// 이진탐색트리에 노드를 재귀적으로 삽입(중복값은 삽입하지 않음)
int insert(TNode* r, TNode* n)
{
    if (n->data == r->data) return 0;

    else if (n->data < r->data) {
        if (r->left == NULL) r->left = n;
        else insert(r->left, n);
    }
    else {
        if (r->right == NULL) r->right = n;
        else insert(r->right, n);
    }

    return 1;
}

/* 이진탐색트리 삭제 */
// 이진탐색트리에서 주어진 노드를 삭제(자식 수에 따라 경우 분기)
void delete(TNode* parent, TNode* node)
{
    TNode *child, *succ, *succp;

    if ((node->left == NULL && node->right == NULL)) {
        if (parent == NULL) root = NULL;
        else {
            if (parent->left == node)
                parent->left = NULL;
            else
                parent->right = NULL;
        }
    }

    else if (node->left == NULL || node->right == NULL) {
        child = (node->left != NULL) ? node->left : node->right;

        if (node == root) root = child;
        else {
            if (parent->left == node)
                parent->left = child;
            else
                parent->right = child;
        }
    }

    else {
        succp = node;
        succ = node->right;

        while (succ->left != NULL) {
            succp = succ;
            succ = succ->left;
        }

        if (succp->left == succ)
            succp->left = succ->right;
        else
            succp->right = succ->right;

        node->data = succ->data;
        node = succ;
    }

    free(node);
}

/* 테스트용 함수 */
// 루트에서 주어진 키를 탐색하고 결과를 출력하는 테스트용 래퍼 함수
void search_BST(int key)
{
    TNode* n = search(root, key);

    if (n != NULL)
        printf("[탐색 연산] : 성공 [%d] = %p\n", n->data, n);
    else
        printf("[탐색 연산] : 실패: No %d!\n", key);
}

// 루트 기반으로 키를 삽입하는 테스트용 래퍼 함수
void insert_BST(int key)
{
    TNode* n = create_tree(key, NULL, NULL);

    if (is_empty_tree())
        root = n;
    else if (insert(root, n) == 0)
        free(n);
}

// 루트에서 키를 찾아 삭제 작업을 호출하는 테스트용 래퍼 함수
void delete_BST(int key)
{
    TNode* parent = NULL;
    TNode* node = root;

    if (node == NULL) return;

    while (node != NULL && node->data != key) {
        parent = node;
        node = (key < node->data) ? node->left : node->right;
    }

    if (node == NULL)
        printf(" Error: key is not in the tree!\n");
    else
        delete(parent, node);
}



// 프로그램 실행 진입점: 테스트 케이스 실행
void main()
{
    // 삽입 연산 테스트
    printf("[삽입 연산] : 35 18 7 26 12 3 68 22 30 99");

    init_tree();

    insert_BST(35);    insert_BST(18);
    insert_BST(7);     insert_BST(26);
    insert_BST(12);    insert_BST(3);
    insert_BST(68);    insert_BST(22);
    insert_BST(30);    insert_BST(99);

    // 트리 정보 출력
    printf("\n    In-Order : ");    inorder(root);
    printf("\n   Pre-Order : ");    preorder(root);
    printf("\n  Post-Order : ");    postorder(root);
    printf("\nLevel-Order : ");     levelorder(root);

    printf("\n 노드의 개수 = %d\n", count_node(root));
    printf(" 단말의 개수 = %d\n", count_leaf(root));
    printf(" 트리의 높이 = %d\n", calc_height(root));

    // 탐색 연산 테스트
    search_BST(26);
    search_BST(25);

    // 삭제 연산 테스트
    printf("\noriginal bintree: LevelOrder: "); levelorder(root);
    delete_BST(3);

    printf("\ncase1: < 3> 삭제: LevelOrder: "); levelorder(root);
    delete_BST(68);

    printf("\ncase2: <68> 삭제: LevelOrder: "); levelorder(root);
    delete_BST(18);

    printf("\ncase3: <18> 삭제: LevelOrder: "); levelorder(root);
    delete_BST(35);

    printf("\ncase3: <35> root: LevelOrder: "); levelorder(root);

    // 최종 트리 정보 출력
    printf("\n 노드의 개수 = %d\n", count_node(root));
    printf(" 단말의 개수 = %d\n", count_leaf(root));
    printf(" 트리의 높이 = %d\n", calc_height(root));
}
// gcc ./tree_5.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out

