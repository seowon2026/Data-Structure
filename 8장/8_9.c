/*
    프로그램 내용: 수식트리의 계산 함수 및 테스트 프로그램
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

int evaluate(TNode *n)
{
    int op1, op2;

    if (n == NULL)
        return 0;
    if (n->left == NULL && n->right == NULL)
        return n->data;
    else {
        op1 = evaluate(n->left);
        op2 = evaluate(n->right);
        switch (n->data) {
        case '+':
            return op1 + op2;
        case '-':
            return op1 - op2;
        case '*':
            return op1 * op2;
        case '/':
            return op1 / op2;
        }
        return 0;
    }
}

int main(void)
{
    TNode *n1, *n2, *n3, *n4, *n5, *n6;

    n1 = create_tree(3, NULL, NULL);
    n2 = create_tree(2, NULL, NULL);
    n3 = create_tree('*', n1, n2);
    n4 = create_tree(5, NULL, NULL);
    n5 = create_tree(6, NULL, NULL);
    n6 = create_tree('-', n4, n5);
    root = create_tree('+', n3, n6);

    printf("계산 결과 = %d\n", evaluate(root));
    return 0;
}

// gcc ./8_9.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
