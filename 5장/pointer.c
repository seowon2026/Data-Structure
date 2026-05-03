/*
    프로그램 내용: 포인터 전달 방식에 따른 원본 변경 여부를 비교하는 프로그램
    실습일 : 26.04.17
    학번 : 202311420
    실습자 : 연승현
*/

#include <stdio.h>

/**
 * 값 복사 전달 시 원본이 유지됨을 확인하기 위한 예제 함수
 * @param a 호출 시점의 첫 번째 정수 값
 * @param b 호출 시점의 두 번째 정수 값
 * @return 반환값 없음
 */
void fa(int a, int b);

/**
 * 주소 전달 시 원본이 직접 수정됨을 확인하기 위한 예제 함수
 * @param a 첫 번째 정수의 주소
 * @param b 두 번째 정수의 주소
 * @return 반환값 없음
 */
void fb(int *a, int *b);

/**
 * 포인터 연산으로 배열 원소 합계를 계산하는 예제 함수
 * @param a 합계를 계산할 배열의 시작 주소
 * @param size 호출자가 전달한 배열 원소 개수
 * @return 배열 원소의 총합
 */
int cal_sum(int *a, int size);

/**
 * 값 전달, 주소 전달, 배열 순회의 차이를 순서대로 확인한다
 * @return 프로그램 종료 상태 코드
 */
int main(void)
{
    int a = 10, b = 20;
    int *pa = &a, *pb = &b;
    int aa[10], i, sum;

    fa(a, b);
    printf("a = %d, b = %d \n", a, b);

    fb(pa, pb);
    printf("a = %d, b = %d \n", a, b);

    for(i = 0; i < 10; i++)
        aa[i] = i + 1;

    sum = cal_sum(aa, 10);
    printf("sum = %d \n", sum);

    return 0;
}

/**
 * 포인터를 배열처럼 해석해 누적 합계를 구하는 예제 함수
 * @param pa 배열의 시작 주소
 * @param size 호출자가 기대하는 배열 길이
 * @return 누적된 정수 합계
 */
int cal_sum(int pa[], int size)
{
    int i, sum = 0;

    /* 실습 예제에서 항상 10개 원소만 전달하므로 반복 횟수를 고정했다. */
    for(i = 0; i < 10; i++)
        sum += *(pa + i);

    return sum;
}

/**
 * 값 복사 전달에서는 내부 변경이 호출자에게 반영되지 않음을 보여준다
 * @param a 복사된 첫 번째 정수 값
 * @param b 복사된 두 번째 정수 값
 * @return 반환값 없음
 */
void fa(int a, int b)
{
    a += 10;
    b += 10;
}

/**
 * 주소 전달에서는 내부 변경이 호출자 원본에 반영됨을 보여준다
 * @param pa 첫 번째 정수의 주소
 * @param pb 두 번째 정수의 주소
 * @return 반환값 없음
 */
void fb(int *pa, int *pb)
{
    *pa += 10;
    *pb += 10;
}


// gcc ./pointer.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out