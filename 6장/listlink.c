/*
    프로그램 내용: 단순연결리스트를 이용한 리스트 전체 프로그램
    실습일 : 26.04.24
    학번 : 202311420
    실습자 : 연승현
*/


#include <stdio.h>
#include <stdlib.h>

typedef int Element;

typedef struct LinkedNode {
    Element data;
    struct LinkedNode* link;
} Node;

Node* head = NULL;

void init_list() { head = NULL; }
int is_empty() { return head == NULL; }

Node* get_entry(int pos)
{
    Node* p = head;
    int i;

    for (i = 0; i < pos; i++, p = p->link)
        if (p == NULL) return NULL;

    return p;
}


int size()
{
    Node* p;
    int count = 0;

    for (p = head; p != NULL; p = p->link)
        count++;

    return count;
}


void replace(int pos, Element e)
{
    Node* node = get_entry(pos);

    if (node != NULL)
        node->data = e;
}

Node* find(Element e)
{
    Node* p;

    for (p = head; p != NULL; p = p->link)
        if (p->data == e)
            return p;

    return NULL;
}

void insert_next(Node *before, Node *node) {
    if(node != NULL) {
        node->link = before->link;
        before->link = node;
    }
}


void insert(int pos, Element e)
{
    Node *new_node, *prev;

    new_node = (Node*)malloc(sizeof(Node));
    new_node->data = e;
    new_node->link = NULL;

    if (pos == 0) {
        new_node->link = head;
        head = new_node;
    }
    else {
        prev = get_entry(pos - 1);
        if (prev != NULL)
            insert_next(prev, new_node);
        else
            free(new_node);
    }
}


Node* remove_next(Node *before)
{
    Node* removed;

    removed = before->link;
    if (removed != NULL) {
        before->link = removed->link;
    }
    return removed;
}


void delete(int pos)
{
    Node* prev, *removed;

    if (pos == 0 && is_empty() == 0) {
        removed = head;
        head = head->link;
        free(removed);
    }
    else {
        prev = get_entry(pos - 1);
        if (prev != NULL) {
            removed = remove_next(prev);
            free(removed);
        }
    }
}


void clear_list() {
    while (is_empty() == 0)
        delete(0);
}

void print_list(char* msg)
{
    Node* p;
    printf("%s[%2d]: ", msg, size());
    for (p = head; p != NULL; p = p->link)
        printf("%2d ", p->data);
    printf("\n");
}

void main()
{
    init_list();

    insert(0, 10);
    insert(0, 20);
    insert(1, 30);
    insert(size(), 40);
    insert(2, 50);

    print_list("단순연결리스트로 구현한 List(삽입x5)");

    replace(2, 90);
    print_list("단순연결리스트로 구현한 List(교체x1)");

    delete(2);
    delete(size() - 1);
    delete(0);

    print_list("단순연결리스트로 구현한 List(삽입x3)");

    clear_list();
    print_list("단순연결리스트로 구현한 List(정리후)");
}

// gcc ./listlink.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out