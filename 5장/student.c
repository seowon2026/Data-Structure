/*
    프로그램 내용: 구조체 전달 방식에 따른 원본 변경 범위를 비교하는 프로그램
    실습일 : 26.04.17
    학번 : 202311420
    실습자 : 연승현
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    int id;
    char name[20];
    char dept[32];
} Student;

/**
 * 구조체를 값으로 전달할 때 원본이 유지됨을 확인하기 위한 예제 함수
 * @param s 복사되어 전달된 학생 정보
 * @return 반환값 없음
 */
void test1(Student s);

/**
 * 구조체 포인터를 전달할 때 원본이 직접 수정됨을 확인하기 위한 예제 함수
 * @param s 수정할 학생 구조체의 주소
 * @return 반환값 없음
 */
void test2(Student *s);

/**
 * 수정된 구조체를 반환해 대입으로 원본을 갱신하는 방식을 보여준다
 * @param s 복사되어 전달된 학생 정보
 * @return 변경된 학생 구조체
 */
Student test3(Student s);

/**
 * 구조체의 값 전달, 주소 전달, 반환 대입 차이를 순서대로 확인한다
 * @return 프로그램 종료 상태 코드
 */
int main(void)
{
    Student s1;
    Student *ps;

    s1.id = 10;
    strcpy(s1.name, "Park");
    strcpy(s1.dept, "Computer Eng.");

    ps = (Student *)malloc(sizeof(Student));
    *ps = s1;

    printf("ps->id : %d, ps->name : %s, ps->dept : %s \n",
           ps->id, ps->name, ps->dept);

    test1(*ps);
    printf("ps->id : %d, ps->name : %s, ps->dept : %s \n",
           ps->id, ps->name, ps->dept);

    test2(ps);
    printf("ps->id : %d, ps->name : %s, ps->dept : %s \n",
           ps->id, ps->name, ps->dept);

    *ps = test3(*ps);
    printf("ps->id : %d, ps->name : %s, ps->dept : %s \n",
           ps->id, ps->name, ps->dept);

    free(ps);

    return 0;
}

/**
 * 값 전달에서는 함수 내부 변경이 원본에 반영되지 않음을 보여준다
 * @param s 복사된 학생 구조체
 * @return 반환값 없음
 */
void test1(Student s)
{
    s.id = 20;
}

/**
 * 포인터 전달에서는 함수 내부 변경이 원본에 반영됨을 보여준다
 * @param s 수정할 학생 구조체의 주소
 * @return 반환값 없음
 */
void test2(Student *s)
{
    s->id = 20;
}

/**
 * 복사본을 수정해 반환하면 대입 시점에만 원본이 갱신됨을 보여준다
 * @param s 복사된 학생 구조체
 * @return 학번이 변경된 학생 구조체
 */
Student test3(Student s)
{
    s.id = 30;
    return s;
}
