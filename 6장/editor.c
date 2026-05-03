/*
    프로그램 내용: 리스트를 이용한 라인 편집기 프로그램
    실습일 : 26.04.24
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR_PER_LINE 1000

typedef struct Line {
    char str[MAX_CHAR_PER_LINE];
} Line;

typedef Line Element;

typedef struct LinkedNode {
    Element data;
    struct LinkedNode* link;
} Node;

Node* head;

// 리스트를 비어 있는 상태로 초기화한다.
void init_list() { head = NULL; }

// 리스트가 비어 있는지 확인한다.
int is_empty() { return head == NULL; }

// 지정한 위치의 노드를 찾아 반환한다.
Node* get_entry(int pos)
{
    Node* p = head;
    int i;

    if (pos < 0)
        return NULL;

    for (i = 0; i < pos; i++, p = p->link)
        if (p == NULL) return NULL;

    return p;
}

// 리스트에 저장된 노드 개수를 반환한다.
int size()
{
    Node* p;
    int count = 0;

    for (p = head; p != NULL; p = p->link)
        count++;

    return count;
}


// 지정한 위치의 데이터를 새 데이터로 변경한다.
void replace(int pos, Element e)
{
    Node* node = get_entry(pos);

    if (node != NULL)
        node->data = e;
}


// 기준 노드 뒤에 새 노드를 연결한다.
void insert_next(Node *before, Node *node) {
    if(before != NULL && node != NULL) {
        node->link = before->link;
        before->link = node;
    }
}


// 지정한 위치에 새 데이터를 삽입한다.
void insert(int pos, Element e)
{
    Node *new_node, *prev;

    if (pos < 0)
        return;

    new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "메모리 할당 실패\n");
        exit(EXIT_FAILURE);
    }

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


// 기준 노드 다음 노드를 리스트에서 분리해 반환한다.
Node* remove_next(Node *before)
{
    Node* removed;

    removed = before->link;
    if (removed != NULL) {
        before->link = removed->link;
    }
    return removed;
}


// 지정한 위치의 노드를 삭제한다.
void delete(int pos)
{
    Node* prev, *removed;

    if (pos < 0)
        return;

    if (pos == 0 && is_empty() == 0) {
        removed = head;
        head = head->link;
        free(removed);
    }
    else {
        prev = get_entry(pos - 1);
        if (prev != NULL) {
            removed = remove_next(prev);
            if (removed != NULL)
                free(removed);
        }
    }
}


// 리스트의 모든 노드를 삭제한다.
void clear_list() {
    while (is_empty() == 0)
        delete(0);
}

// 리스트 내용을 행 번호와 함께 출력한다.
void display(FILE *fp)
{
    int i=0;
    Node* p;
    for (p = head ; p != NULL ; p=p->link, i++ ) {
        fprintf(fp, "%3d: %s", i, p->data.str);
    }
}

// 리스트 내용을 파일 저장용 형식으로 출력한다.
void save_list(FILE *fp)
{
    Node* p;
    for (p = head ; p != NULL ; p=p->link)
        fprintf(fp, "%s", p->data.str);
}

// 현재 입력 줄에 남은 문자를 모두 버린다.
void clear_input_buffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// 한 줄 문자열을 입력받고 초과 입력을 정리한다.
int read_line(char *str, int size)
{
    if (fgets(str, size, stdin) == NULL)
        return 0;

    if (strchr(str, '\n') == NULL)
        clear_input_buffer();

    return 1;
}

// 행 번호를 입력받아 유효성을 검사한다.
int read_position(const char *prompt, int *pos)
{
    printf("%s", prompt);
    if (scanf("%d", pos) != 1) {
        printf("잘못된 행 번호입니다.\n");
        clear_input_buffer();
        return 0;
    }
    clear_input_buffer();

    if (*pos < 0) {
        printf("행 번호는 0 이상이어야 합니다.\n");
        return 0;
    }

    return 1;
}

// 라인 편집기 메뉴를 실행한다.
int main(void)
{
    int command;
    int pos;
    Line line;
    FILE *fp;

    init_list();
    do{
        printf("[메뉴선택] i-입력, d-삭제, r-변경, p-출력, l-파일읽기, s-저장, q-종료=> ");
        command = getchar();
        if (command == EOF)
            break;

        clear_input_buffer();

        switch(command) {

        case 'i':
            if (read_position(" 입력행 번호: ", &pos) == 0)
                break;
            printf(" 입력행 내용: ");
            if (read_line(line.str, MAX_CHAR_PER_LINE))
                insert(pos, line);
            break;

        case 'd':
            if (read_position(" 삭제행 번호: ", &pos) == 0)
                break;
            delete(pos);
            break;

        case 'r':
            if (read_position(" 변경행 번호: ", &pos) == 0)
                break;
            printf(" 변경행 내용: ");
            if (read_line(line.str, MAX_CHAR_PER_LINE))
                replace(pos, line);
            break;

        case 'l':
            fp = fopen("Test.txt", "r");
            if (fp != NULL) {
                clear_list();
                while (fgets(line.str, MAX_CHAR_PER_LINE, fp))
                    insert(size(), line);
                fclose(fp);
            }
            break;

        case 's':
            fp = fopen("Test.txt", "w");
            if (fp != NULL) {
                save_list(fp);
                fclose(fp);
            }
            break;

        case 'p':
            display(stdout);
        }

    } while(command != 'q');

    clear_list();
    return 0;
}

// gcc ./editor.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out
