#include <stdio.h>

#define MAX_CNT 20

int main(int ac, char *av[]) {
    FILE *fp;
    int ch, i;
    int lineNum = 1; // 줄번호
    int flag = 0; // lineNum을 출력할지 안 할지 정하는 플래그
    int ismax = ac > MAX_CNT;

    if( (ac>=2)&&(av[1][0] == '-') ) { // 옵션을 주는 경우.
        
        if(ac > MAX_CNT+2) { // 파일이 20개가 넘은 경우.
            printf("파일은 최대 20개까지만 입력할 수 있습니다.\n");
            for(i = 0; i < ac-(MAX_CNT+2); i+=1)
                printf("ignoring %s..\n", av[i+22]);
            printf("\n");
            ac = MAX_CNT+2;
        }

        if(av[1][1] == 'n') {   //  줄번호 출력 옵션.
            if(ac == 2) {   //  파일명을 입력하지 않은 경우
                printf("문자열 입력을 멈추고 싶으면 Ctrl+C를 입력하세요\n");
                while( (ch = fgetc(stdin)) != EOF) { // stdin에서 문자 읽어오기
                    if(lineNum == 1) {
                            printf("%6d  ", lineNum);
                            lineNum += 1;
                    }
                            
                    else if(flag) {
                        printf("%6d  ", lineNum);
                        lineNum += 1;
                        flag = 0;
                    }

                    if(ch == '\n')
                        flag = 1;

                    fputc(ch, stdout);
                }
            }

            else { // 파일명을 입력한 경우
                for(i = 2; i < ac; i++) {
                    if( (fp = fopen(av[i], "r")) == NULL)
                        printf("Can't open %s\n", av[i]);
                    else {
                        while( (ch = fgetc(fp)) != EOF) {       // fp 파일로부터 문자 읽어오기
                            if(lineNum == 1) {
                                printf("%6d  ", lineNum);
                                lineNum += 1;
                            }
        
                            else if(flag) {
                                printf("%6d  ", lineNum);
                                lineNum += 1;
                                flag = 0;
                            }

                            if(ch == 10)
                                flag = 1;

                            fputc(ch, stdout);
                        }
                        fclose(fp);
                    }
                }
            }
        }

        else if(av[1][1] == 'c') {   // 소문자 출력 옵션.
            for(i = 2; i < ac; i+=1) {
                if( (fp = fopen(av[i], "r")) == NULL)
                    printf("Can't open %s\n", av[i]);
                else {
                    while( (ch = fgetc(fp)) != EOF) {
                        if(isupper(ch))
                            ch = tolower(ch);
                        fputc(ch, stdout);
                    }
                    fclose(fp);
                }
            }
        }

        else if(av[1][1] == 'C') { // 대문자 출력 옵션.
            for(i = 2; i < ac; i+=1) {
                if( (fp = fopen(av[i], "r")) == NULL)
                    printf("Can't open %s\n", av[i]);
                else {
                    while( (ch = fgetc(fp)) != EOF) {
                        if(islower(ch))
                            ch = toupper(ch);
                        fputc(ch, stdout);
                    }
                    fclose(fp);
                }
            }
        }
        
        else { // 유효하지 않은 옵션
            printf("구현되지 않은 기능입니다.\n");
            return -1;
        }
    }

    else { // 옵션을 주지 않는 경우. 줄번호 미출력
        if(ac == 1) { // 파일 미입력
            printf("문자열 입력을 멈추고 싶으면 Ctrl+C를 입력하세요\n");
            while( (ch = fgetc(stdin)) != EOF) { // stdin에서 문자 읽어오기
                fputc(ch, stdout);
            }
        }

        else { // 파일 입력
            if(ac > MAX_CNT+1) { // 파일이 20개가 넘은 경우.
                printf("파일은 최대 20개까지만 입력할 수 있습니다.\n");
                for(i = 0; i < ac-(MAX_CNT+1); i++)
                    printf("ignoring %s..\n", av[i+21]);
                printf("\n");
                ac = MAX_CNT+1;
            }

            for(i = 1; i < ac; i++) {
                if( (fp = fopen(av[i], "r")) == NULL)
                    printf("Can't open %s\n", av[i]);
                else {
                    while( (ch = fgetc(fp)) != EOF)   // fp 파일로부터 한 문자 읽기
                        fputc(ch, stdout);              // 읽은 문자 표준 출력으로 보내기
                    fclose(fp);
                }
            }
        }
    }

    return 0;
}