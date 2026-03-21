/*
    입력받은 학생 정보중 가장 높은 점수를 가지고 있는 학생의 정보를 출력하는 프로그램
	날짜 : 26.03.20
	학번 : 202311420
	이름 : 연승현
*/


#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[20];
    double score;
} Student;

void print_student(Student s);
Student Max_student(Student s[], int n);

int main(void) {
    Student s[3], max;
    int i;

    for (i = 0; i < 3; i++) {
        printf("ID, name, score >> ");
        scanf("%d %s %lf", &s[i].id, s[i].name, &s[i].score);
        // scanf_s의 경우 scanf_s("%d %s %lf", &s[i].id, s[i].name, 20, &s[i].score);
    }
    
    for (i = 0; i < 3; i++)
        print_student(s[i]);

    max = Max_student(s, 3);
    printf("The max score student is : \n");
    print_student(max);

    return 0;
}

void print_student(Student s) {
    printf("ID = %d. Name = %s, Score = %lf\n", s.id, s.name, s.score);
}

Student Max_student(Student s[], int n) {
    int i;
    Student Max;

    Max = s[0];
    for (i = 0; i < n; i++)
        if (Max.score < s[i].score)
            Max = s[i];
    return Max;
}

// gcc ./student.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out