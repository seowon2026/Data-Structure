/*
    프로그램 내용: 이진트리를 위한 노드 구조체와 기본 연산들
    실습일 : 26.05.15
    학번 : 202311420
    실습자 : 연승현
*/


#include <stdio.h>
#include <stdlib.h>

typedef char TElement;

typedef struct BinTNode {
    TElement data;
    struct BinTNode* left;
    struct BinTNode* right;
} TNode;

TNode* root;

void init_tree() { 
    root = NULL; 
}

int is_empty_tree() { 
    return root == NULL; 
}

TNode* get_root() { 
    return root; 
}

TNode* create_tree(TElement val, TNode* l, TNode* r)
{
    TNode* n = (TNode*)malloc(sizeof(TNode));

    n->data = val;
    n->left = l;
    n->right = r;

    return n;
}

// 전위 순회 함수
void preorder(TNode *n)
{
    if( n != NULL ) {
        printf("[%c] ", n->data);
        preorder(n->left);
        preorder(n->right);
    }
}

// 중위 순회 함수
void inorder(TNode *n)
{
    if( n != NULL ) {
        inorder(n->left);
        printf("[%c] ", n->data);
        inorder(n->right);
    }
}

// 후위 순회 함수
void postorder(TNode *n)
{
    if( n != NULL ) {
        postorder(n->left);
        postorder(n->right);
        printf("[%c] ", n->data);
    }
}


// 레벨 순회 함수
void levelOrder(TNode* root)
{
    // 아직 큐 코드가 없으면 임시로 비워둠
}

// #define MAX_QUEUE_SIZE 100
// typedef TNode* Element;

// // 프로그램 4.1의 6~37행 추가

// void levelOrder(TNode *root)
// {
//     TNode* n;

//     if( root == NULL ) return;

//     init_queue();
//     enqueue( root );

//     while( !is_empty() ) {
//         n = dequeue();

//         if( n != NULL ) {
//             printf("[%c] ", n->data);

//             enqueue( n->left );
//             enqueue( n->right );
//         }
//     }
// }


// 노드 개수 계산 함수
int count_node(TNode* n)
{
    if (n == NULL) return 0;

    return 1 + count_node(n->left) + count_node(n->right);
}

// 단말 노드 개수 계산 함수
int count_leaf(TNode* n)
{
    if (n == NULL) return 0;

    if (n->left == NULL && n->right == NULL)
        return 1;

    return count_leaf(n->left) + count_leaf(n->right);
}

// 트리 높이 계산 함수
int calc_height(TNode* n)
{
    int hLeft, hRight;

    if (n == NULL) return 0;

    hLeft = calc_height(n->left);
    hRight = calc_height(n->right);

    return (hLeft > hRight ? hLeft : hRight) + 1;
}

// 트리의 초기 생성 코드 포함
void main()
{
    TNode *b, *c, *d, *e, *f;

    init_tree();

    d = create_tree('D', NULL, NULL);
    e = create_tree('E', NULL, NULL);
    b = create_tree('B', d, e);
    f = create_tree('F', NULL, NULL);
    c = create_tree('C', f, NULL);
    root = create_tree('A', b, c);

    // 트리 테스트 프로그램 추가
    printf("\n In-Order : ");
    preorder(root);

    printf("\n Pre-Order : ");
    postorder(root);

    printf("\n level-Order : ");
    levelOrder(root);

    printf("\n");

    printf(" 노드의 개수 = %d\n", count_node(root));
    printf(" 단말의 개수 = %d\n", count_leaf(root));
    printf(" 트리의 높이 = %d\n", calc_height(root));
}

// gcc ./tree.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
