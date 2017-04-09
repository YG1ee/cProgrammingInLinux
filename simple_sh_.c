#include <stdio.h>

int main() {
    char str[200];

    while(1) {
        printf("prompt$ ");
    gets(str);
    if(!strcmp(str, "exit"))
        return 0;
    if(strlen(str) == 0) // 입력된 문자열이 없을 경우
        continue;
    else	// 쉘에서는 입력된 명령을 수행하기 위한 코드 삽입
            // 본 예제에서는 입력된 문장을 단순히 출력함
        puts(str);
    }
}
