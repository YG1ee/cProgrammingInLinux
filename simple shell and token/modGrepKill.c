#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    int i, argNum = 1;
    int isToken = 0; // 문자열에 구분자가 들어있는지 확인하는 변수
    char str[200];
    // char *p;
    char token[] = " ";

    while (1) {
        printf("prompt$ ");

        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = 0;

        for (i = 0; i < strlen(str); i += 1)
            if(str[i] == ' ')
                isToken = 1;

        /* 입력된 문자열이 없을 경우 */
        if (strlen(str) == 0)
            continue;
        
        /* 입력된 문자열이 exit일 경우 */
        if (!strcmp(str, "exit"))
            return 0;
        
        /* 입력된 문자열에 구분자가 있는 경우 */
        else if (isToken) {
            char *ptr;
            ptr = strtok(str, token);

            if (!strcmp(ptr, "chmod")) { // chmod 구현
                mode_t mode;
                ptr = strtok(NULL, token);
                sscanf(ptr, "%o", &mode);
                
                while (ptr = strtok(NULL, token))
                    if (chmod(ptr, mode) == -1)
                        perror("chmod failed\n");
            }

            else if (!strcmp(ptr, "fgrep")) { // fgrep 구현
                FILE *fp;
                char buf[200];
                char *pattern;
                int i, j, state = 0;
                int plen;

                if (pattern = strtok(NULL, token)) {
                    plen = strlen(pattern);
                    while (ptr = strtok(NULL, token)) {
                        if( (fp = fopen(ptr, "r")) == NULL)
                            printf("Can't open %s\n", ptr);

                        while(fgets(buf, sizeof(buf), fp) != NULL) {
                            int blen = strlen(buf);
                            for(j = 0; j < blen; j += 1) {
                                if(buf[j] == pattern[state]) {
                                    state += 1;
                                    if(state == plen)
                                        printf("%s", buf);
                                }
                                else if(buf[j] == pattern[state])
                                    state = 1;
                                else
                                    state = 0;
                                }
                        }
                        fclose(fp);
                    }
                }
                else {
                    puts(str);
                }
            }

            else if (!strcmp(ptr, "kill")) {
                if (ptr = strtok(NULL, token)) {
                    if (ptr[0] == '-') { // 옵션을 주는 경우
                        char *target_s;
                        if (target_s = strtok(NULL, token)) {
                            int target = atoi(target_s);

                            switch (ptr[1]) {
                                case '2': kill(target, SIGINT);
                                    break;
                                case '9': kill(target, SIGKILL);
                                    break;
                                case '1':
                                    if(ptr[2] == '5') {
                                        kill(target, SIGTERM);
                                        break;
                                    }
                                default: printf("Wrong option given.\n");
                            }
                        }
                        else
                            printf("Usage: kill pid\n");
                    }
                    else // 옵션을 주지 않는 경우
                    // 원래는 SIGTERM 신호가 들어오지만 이 예제는 SIGINT
                        kill(atoi(ptr), SIGINT);
                }
                else {
                    printf("Usage: kill pid\n");
                }
            }
            isToken = 0;
        }
    }
}
