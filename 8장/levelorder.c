/*
    프로그램 내용: 이진트리의 레벨 순회 함수
    실습일 : 26.05.15
    학번 : 202311420
    실습자 : 연승현
*/

#define MAX_QUEUE_SIZE 100
typedef TNode* Element;

// 프로그램 4.1의 6~37행 추가

void levelOrder(TNode *root)
{
    TNode* n;

    if( root == NULL ) return;

    init_queue();
    enqueue( root );

    while( !is_empty() ) {
        n = dequeue();

        if( n != NULL ) {
            printf("[%c] ", n->data);

            enqueue( n->left );
            enqueue( n->right );
        }
    }
}

// gcc ./tree.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
