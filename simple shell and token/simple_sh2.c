#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

#define MAX_ARG 100
#define MAX_STR 200

int f_kill(int argc, char *argv[]);
int f_chmod(int argc, char *argv[]);
int f_cat(int argc, char *argv[]);
int fgrep(int argc, char *argv[]);

int main() {
    int i, argc;
    char *argv[MAX_ARG];
    char str[MAX_STR];
    char delim[] = " \t\n";

    while (1) {
        printf("prompt$ ");
        fgets(str, sizeof(str), stdin); // 표준 입력으로부터 1라인 입력 받아 str에 저장
        /*
        if (str[0] == EOF)
            return 0;
            인터럽트 (Ctrl+D) 가 들어왔을 때 무한루프에 빠지지 않고
            프로그램을 종료하는 방법은 ??
         */
        str[strlen(str) - 1] = 0;
        argc = 0;
        argv[argc++] = strtok(str, delim); // str에서 단어 단위로 포인터 배열에 저장
        while (argv[argc] = strtok(NULL,delim)) argc += 1;
        
        if (!strlen(str))
            continue;
        else if (!strcmp(argv[0], "exit")) // exit 명령일 경우 쉘 종료
            return 0;
        else if (!strcmp(argv[0], "kill")) // kill 내장 명령 구현
            f_kill(argc, argv);
        else if (!strcmp(argv[0], "chmod")) // chmod 명령 구현
            f_chmod(argc, argv);
        else if (!strcmp(argv[0], "cat"))
            f_cat(argc, argv);
        else if (!strcmp(argv[0], "fgrep"))
            fgrep(argc, argv);
        else
            printf("%s: Unknown command\n", argv[0]);
    }

    return 0;
}

int f_kill(int argc, char *argv[]) {
    int i;
    int signo = SIGINT;
    int pid[MAX_ARG], pnum = 0;
    int err = 0;

    for (i = 1; i < argc; i += 1) {
        if (argv[i][0] == '-') // option for signo
            signo = atoi(argv[i]+1);
        else
            pid[pnum++] = atoi(argv[i]);
    }

    for (i = 0; i < pnum; i += 1) {
        if (kill(pid[i], signo)) {
            fprintf(stderr, "Failed to kill %d\n", pid[i]);
            err = 1;
        }
    }

    return 1;
}

int f_chmod(int argc, char *argv[]) {
    int i;
    mode_t mode;
    sscanf(argv[1], "%o", &mode);

    for (i = 2; i < argc; i += 1) {
        if (chmod(argv[i], mode) == -1)
            perror("chmod failed\n");
    }
    return 1;
}

int f_cat(int argc, char *argv[]) {
    FILE *fp;
    int ch, i;
    int optionN = 0;

    for (i = 1; i < argc; i += 1)
        if (argv[i][0] == '-')
            if (argv[i][1] == 'n')
                optionN = 1;

    if (optionN) {
        int lineNum = 1;
        int flag = 0;

        if (argc == 2) { // 파일명을 입력하지 않은 경우
            while ((ch = fgetc(stdin)) != EOF) {
                if (lineNum == 1) {
                    printf("%6d  ", lineNum);
                    lineNum += 1;
                }
                else if (flag) {
                    printf("%6d  ", lineNum);
                    lineNum += 1;
                    flag = 0;
                }
                
                if (ch == '\n')
                    flag = 1;

                fputc(ch, stdout);
            }
            fclose(fp);
        }
        else { // 파일명을 입력한 경우
            if (argc > MAX_ARG+2) {
                printf("파일은 최대 %d개까지만 출력할 수 있습니다.\n", MAX_ARG+2);
                for (i = 0; i < argc-(MAX_ARG+2); i += 1)
                    printf("ignoring %s.. \n", argv[i+MAX_ARG+2]);
                printf("\n");
                argc = MAX_ARG+2;
            }

            for (i = 2; i < argc; i += 1) {
                if ((fp = fopen(argv[i], "r")) == NULL)
                    printf("Can't open %s\n", argv[i]);
                else {
                    while ((ch = fgetc(fp)) != EOF) {
                        if (lineNum == 1) {
                            printf("%6d  ", lineNum);
                            lineNum += 1;
                        }
                        else if (flag) {
                            printf("%6d  ", lineNum);
                            lineNum += 1;
                            flag = 0;
                        }
                        
                        if (ch == '\n')
                            flag = 1;

                        fputc(ch, stdout);
                    }
                    fclose(fp);
                }
            }
        }
    }
    else {
        if (argc == 1) { // 파일 미입력
            while ((ch = fgetc(stdin)) != EOF) // stdin에서 문자 읽어오기
                fputc(ch, stdout);
        }
        else {
            if (argc > MAX_ARG+1) {
                printf("파일은 최대 %d개까지만 출력할 수 있습니다.\n", MAX_ARG);
                for (i = 0; i < argc-(MAX_ARG+1); i += 1)
                    printf("ignoring %s..\n", argv[i+MAX_ARG+1]);
                printf("\n");
                argc = MAX_ARG+1;
            }

            for (i = 1; i < argc; i += 1) {
                if ((fp = fopen(argv[i], "r")) == NULL)
                    printf("Can't open %s\n", argv[i]);
                else {
                    while ((ch = fgetc(fp)) != EOF)
                        fputc(ch, stdout);
                    fclose(fp);
                }
            }
        }
    }
    return 1;
}

int fgrep(int argc, char *argv[]) {
    FILE *fp;
    char buf[200];
    char *pattern = argv[1];
    int plen = strlen(pattern);
    int i, j, state = 0;

    for (i = 2; i < argc; i += 1) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            printf("Can't open %s\n", argv[i]);
            continue;
        }
        
        while (fgets(buf, sizeof(buf), fp) != NULL) {
            int blen = strlen(buf);
            for (j = 0; j < blen; j += 1) {
                if (buf[j] == pattern[state]) {
                    state += 1;
                    if (state == plen)
                        printf("%s", buf);
                }
                else if (buf[j] == pattern[state])
                    state = 1;
                else
                    state = 0;
            }
        }
        fclose(fp);
    }
    return 1;
}
