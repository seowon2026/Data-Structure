/*
    프로그램 내용: 동적 할당으로 연락처를 저장하고 출력하는 프로그램 (연습문제 8번)
    실습일 : 26.05.02
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    char phone[20];
} Contact;

void main() {
    int count;
    int i;
    Contact *list;

    printf("주소의 개수: ");
    scanf("%d", &count);

    list = (Contact *)malloc(sizeof(Contact) * count);

    if (list == NULL) {
        printf("메모리 할당 실패\n");
        return;
    }

    for (i = 0; i < count; i++) {
        printf("이름을 입력하시오: ");
        scanf("%s", list[i].name);

        printf("휴대폰 번호를 입력하시오: ");
        scanf("%s", list[i].phone);
    }

    printf("====================================\n");
    printf("이름\t\t휴대폰 번호\n");
    printf("====================================\n");

    for (i = 0; i < count; i++) {
        printf("%s\t\t%s\n", list[i].name, list[i].phone);
    }

    printf("====================================\n");

    free(list);
}


// gcc ./practice-8.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out