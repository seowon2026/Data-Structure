/*
    프로그램 내용: 폴더 용량 계산 함수 및 테스트 프로그램
    실습일 : 26.05.24
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>

typedef int TElement;

typedef struct TNode {
    TElement data;
    struct TNode *left;
    struct TNode *right;
} TNode;

TNode *root;

TNode *create_tree(TElement val, TNode *left, TNode *right)
{
    TNode *node = (TNode *)malloc(sizeof(TNode));
    if (node == NULL)
        return NULL;
    node->data = val;
    node->left = left;
    node->right = right;
    return node;
}

int calc_size(TNode *n)
{
    if (n == NULL)
        return 0;
    return n->data + calc_size(n->left) + calc_size(n->right);
}

int main(void)
{
    TNode *m2, *m3, *m4, *m5;

    m4 = create_tree(200, NULL, NULL);
    m5 = create_tree(500, NULL, NULL);
    m3 = create_tree(100, m4, m5);
    m2 = create_tree(50, NULL, NULL);
    root = create_tree(0, m2, m3);

    printf("폴더 용량 = %d KB\n", calc_size(root));
    return 0;
}

// gcc ./8_10.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
