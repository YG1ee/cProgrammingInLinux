#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int ac, char *av[]) {
    FILE *fp;
    char buf[200];
    int i, j, state = 0;
    int plen;
    int lineNum = 1;
    char pat, read;

    
    if( ac == 1 ) {
        printf("Usage: %s [option] pattern [filename] ..\n", av[0]);
        return -1;
    }

    else if(av[1][0] == '-') { // 옵션을 주는 경우. av[2]가 패턴.
        if(ac == 2) { // 패턴을 입력하지 않은 경우.
            printf("Usage: %s %s pattern [filename] ..\n", av[0], av[1]);
            return -1;
        }

        plen = strlen(av[2]); // plen에 패턴의 길이 대입

        if(av[1][1] == 'n') {   // 줄번호 출력 옵션.
            if(ac == 3) { // 줄번호를 출력하고, 표준 입력에서 내용을 받는 경우
                while( fgets(buf, sizeof(buf), stdin) != NULL) {
                    int blen = strlen(buf); // blen에 버프의 길이 대입

                    for(j = 0; j < blen; j+=1) {
                        if(buf[j] == av[2][state]) {
                            state += 1;
                            if(state == plen)
                                printf("%d:%s", lineNum, buf);
                        }
                        else if(buf[j] == av[2][0])
                            state = 1;
                        else
                            state = 0;
                    }
                    lineNum += 1;
                }
            }

            else if(ac > 3) { // 줄번호를 출력하고, 파일명을 지정한 경우
                for(i = 3; i < ac; i+=1) {
                    if( (fp = fopen(av[i], "r")) == NULL) {
                        printf("Can't open %s\n", av[i]);
                        return -2;
                    }

                    while(fgets(buf, sizeof(buf), fp) != NULL) {
                        // str[strlen(str) - 1] = 0;
                        int blen = strlen(buf); // blen에 버프의 길이 대입

                        for(j = 0; j < blen; j+=1) {
                            if(buf[j] == av[2][state]) {
                                state += 1;
                                if(state == plen)
                                    printf("%d:%s", lineNum, buf);
                            }
                            else if(buf[j] == av[2][0])
                                state = 1;
                            else
                                state = 0;
                        }
                        lineNum += 1;
                    }
                    fclose(fp);
                }
            }
        } // 줄번호 출력 옵션 끝.

        else if(av[1][1] == 'i') { // 대소문자 무시 옵션.
            if(ac == 3) { // 대소문자를 무시하고, 표준 입력에서 내용을 받는 경우
                while(fgets(buf, sizeof(buf), stdin) != NULL) {
                    int blen = strlen(buf); // blen에 버프의 길이 대입

                    for(j = 0; j < blen; j+=1) {
                        pat = tolower(av[2][state]);
                        read = tolower(buf[j]);

                        if(pat == read) {
                            state += 1;
                            if(state == plen)
                                printf("%s", buf);
                        }
                        else if(read == av[2][0])
                            state = 1;
                        else
                            state = 0;
                    }
                }
            }

            else if(ac > 3) { // 대소문자를 무시하고, 파일명을 지정한 경우
                for(i = 3; i < ac; i+=1) {
                    if( (fp = fopen(av[i], "r")) == NULL) {
                        printf("Can't open %s\n", av[i]);
                        return -2;
                    }

                    while(fgets(buf, sizeof(buf), fp) != NULL) {
                        int blen = strlen(buf); // blen에 버프의 길이 대입

                        for(j = 0; j < blen; j+=1) {
                            pat = tolower(av[2][state]);
                            read = tolower(buf[j]);

                            if(pat == read) {
                                state += 1;
                                if(state == plen)
                                    printf("%s", buf);
                            }
                            else if(read == av[2][0])
                                state = 1;
                            else
                                state = 0;
                        }
                    }
                    fclose(fp);
                }
            }
        } // 대소문자 무시 옵션 끝.
    } // 옵션 끝.

    else { // 옵션을 주지 않는 경우. av[1]이 패턴.
        plen = strlen(av[1]); // plen에 패턴의 길이 대입

        if(ac == 2) { // 표준 입력에서 내용을 받는 경우
            while(fgets(buf, sizeof(buf), stdin) != NULL) {
                int blen = strlen(buf); // blen에 버프의 길이 대입

                for(j = 0; j < blen; j+=1) {
                    if(buf[j] == av[1][state]) {
                        state += 1;
                        if(state == plen)
                            printf("%s", buf);
                    }
                    else if(buf[j] == av[1][0]) {
                        state = 1;
                    }
                    else
                        state = 0;
                }
            }
        }
        
        else if(ac > 2) { // 파일명을 지정한 경우
            for(i = 2; i < ac; i+=1) {
                if( (fp = fopen(av[i], "r")) == NULL) {
                    printf("Can't open %s\n", av[i]);
                    return -2;
                }

                while(fgets(buf, sizeof(buf), fp) != NULL) {
                    int blen = strlen(buf); // blen에 버프의 길이 대입

                    for(j = 0; j < blen; j+=1) {
                        if(buf[j] == av[1][state]) {
                            state += 1;
                            if(state == plen)
                                printf("%s", buf);
                        }
                        else if(buf[j] == av[1][0])
                            state = 1;
                        else
                            state = 0;
                    }
                }
            }
        }
    }

    return 0;
}
