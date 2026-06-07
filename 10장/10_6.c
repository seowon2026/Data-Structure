/*
    프로그램 내용: 힙을 이용한 허프만 코드 (10.6)
    실습일: 26.06.05
    학  번: 202311420
    실습자: 연승현
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_NODE 100

typedef struct HuffmanNode {
    char data;
    int freq;
    struct HuffmanNode *left, *right;
} HuffmanNode;

typedef HuffmanNode* HNode;

HNode heap[MAX_HEAP_NODE];
int heap_size;

void error(char str[]) {
    printf("%s\n", str);
    exit(1);
}

void init_heap() { heap_size = 0; }

int is_empty_heap() { return heap_size == 0; }

void insert_heap(HNode n) {
    int i = ++heap_size;
    while (i != 1 && n->freq < heap[i/2]->freq) {  // min-heap
        heap[i] = heap[i/2];
        i /= 2;
    }
    heap[i] = n;
}

HNode delete_heap() {
    int parent, child;
    HNode item, temp;
    if (is_empty_heap()) {
        error("Heap is empty");
    }
    item = heap[1];
    temp = heap[heap_size--];
    parent = 1;
    child = 2;
    while (child <= heap_size) {
        if (child < heap_size && heap[child]->freq > heap[child+1]->freq)
            child++;
        if (temp->freq <= heap[child]->freq) break;
        heap[parent] = heap[child];
        parent = child;
        child *= 2;
    }
    heap[parent] = temp;
    return item;
}

HuffmanNode* new_node(char data, int freq) {
    HuffmanNode* node = (HuffmanNode*)malloc(sizeof(HuffmanNode));
    node->data = data;
    node->freq = freq;
    node->left = node->right = NULL;
    return node;
}

HuffmanNode* build_huffman_tree(char data[], int freq[], int size) {
    init_heap();
    for (int i = 0; i < size; i++) {
        insert_heap(new_node(data[i], freq[i]));
    }
    while (heap_size > 1) {
        HuffmanNode* left = delete_heap();
        HuffmanNode* right = delete_heap();
        HuffmanNode* top = new_node('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insert_heap(top);
    }
    return delete_heap();
}

void print_codes(HuffmanNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        print_codes(root->left, arr, top + 1);
    }
    if (root->right) {
        arr[top] = 1;
        print_codes(root->right, arr, top + 1);
    }
    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

void main() {
    char data[] = {'A', 'B', 'C', 'D', 'E'};
    int freq[] = {5, 9, 12, 13, 16};
    int size = sizeof(data) / sizeof(data[0]);

    printf("허프만 코드 생성 예제 (10.6 힙의 응용)\n");
    printf("문자 및 빈도: ");
    for (int i = 0; i < size; i++) {
        printf("%c:%d ", data[i], freq[i]);
    }
    printf("\n\n허프만 코드:\n");

    HuffmanNode* root = build_huffman_tree(data, freq, size);
    int arr[100];
    print_codes(root, arr, 0);
}

// gcc ./10장/program10_6.c -o ./program10_6.out && clear && ./program10_6.out
