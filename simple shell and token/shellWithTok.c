#include <stdio.h>
#include <string.h>

int main() {
    int i, argNum = 1;
    int isToken = 0; // 문자열에 구분자가 들어있는지 확인하는 변수
    char str[200];
    // char *p;
    char token[] = " ";

    while(1) {
        printf("prompt$ ");

        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = 0;
        for(i = 0; i < strlen(str); i += 1)
            if(str[i] == ' ')
                isToken = 1;

        /* 입력된 문자열이 없을 경우 */
        if(strlen(str) == 0)
            continue;
        
        /* 입력된 문자열이 exit일 경우 */
        if(!strcmp(str, "exit"))
            return 0;
        
        /* 입력된 문자열에 구분자가 있는 경우 */
        else if (isToken) {
            char *ptr;
            ptr = strtok(str, token);
            printf("arg0: %s\n", ptr);
            while(ptr = strtok(NULL, token)) {
                printf("arg%d: %s\n", argNum, ptr);
                argNum += 1;
            }
            argNum = 1;
            isToken = 0;
        }

        else {
            puts(str);
        }
    }
}
