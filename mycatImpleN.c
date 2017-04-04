// 줄번호 옵션만 구현

#include <stdio.h>

int main(int ac, char *av[]) {
    FILE *fp;
    int ch, i;
    int lineNum = 1; // 줄번호
    int flag = 0; // lineNum을 출력할지 안 할지 정하는 플래그

    if( (ac>=2)&&(av[1][0] == '-') ) {                      // 옵션을 주는 경우.
        if(av[1][1] == 'n') {                  //  줄번호 출력 옵션.
            if(ac > 22) {
                printf("파일은 최대 20개까지만 출력할 수 있습니다.\n");
                return -2;
            }

            else if(ac == 2) {                            //  파일명을 입력하지 않은 경우
                while( (ch = fgetc(stdin)) != EOF) { // stdin에서 문자 읽어오기
                    if(lineNum == 1) {
                            printf("%3d  ", lineNum);
                            lineNum += 1;
                    }
                            
                    else if(flag) {
                        printf("%3d  ", lineNum);
                        lineNum += 1;
                        flag = 0;
                    }

                    if(ch == 10)
                        flag = 1;

                    fputc(ch, stdout);
                }
                fclose(fp);
                return 0;
            }
            
            else {
                for(i = 2; i < ac; i++) {
                    if( (fp = fopen(av[i], "r")) == NULL) {
                        printf("Can't open %s\n", av[i]);
                        fclose(fp);
                    }
                    else {
                        while( (ch = fgetc(fp)) != EOF) {       // fp 파일로부터 문자 읽어오기
                            if(lineNum == 1) {
                                printf("%3d  ", lineNum);
                                lineNum += 1;
                            }
                            
                            else if(flag) {
                                printf("%3d  ", lineNum);
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
        else {
            // pass
            printf("구현되지 않은 기능입니다.\n");
            return -1;
        }
    }
    else { // 옵션을 주지 않는 경우. 줄번호 미출력
        if(ac > 21) {   // 20개 이상의 파일 입력
            printf("파일은 최대 20개까지만 출력할 수 있습니다.\n");
            return -2;
        } 
        else if(ac == 1) { // 파일 미입력
            while( (ch = fgetc(stdin)) != EOF) { // stdin에서 문자 읽어오기
                fputc(ch, stdout);
            }
        }
        else {          // 파일 입력
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