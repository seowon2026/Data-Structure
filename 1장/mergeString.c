/*
	날짜 : 26.03.13
	학번 : 202311420
	이름 : 연승현
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
// #define _CRT_SECURE_NO_WARNINGS

int main(void) {

    char s1[60] = "C language IS";
    char s2[60] = "a good programming language";
    char s3[60];
    char s4[4][50];
    int length, result, i;

    length = strlen(s1);
    printf("String length: %d\n", length);

    strcpy(s3, s1);
    printf("s3: %s\n", s3);

    result = strcmp("박", "김");
    printf("result: %d\n", result);

    result = strcmp(s1, s3);
    printf("result: %d\n", result);

    result = strcmp(s1, s2);
    printf("result: %d\n", result);

    strcat(s3, s2);
    printf("result: %s\n", s3);

    for (i = 0; i < 4; i++) {
        printf("이름을 입력하시오: ");
        scanf("%s", s4[i], 50);
    }

    for (i = 0; i < 4; i++) {
        if (islower(s4[i][0]))
            s4[i][0] = -= 32; //s[i][0] = toupper(s[i][0];
    }

    for (i = 0; i < 4; i++)
        printf("%s\t", s4[i]);

    return 0;
}

// gcc ./mergeString.c -o ./start.out -lm -ljson-c -lncurses && clear && chmod +x ./start.out && ./start.out