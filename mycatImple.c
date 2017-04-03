#include <stdio.h>

int main(int ac, char *av[]) {
    FILE *fp;
    int ch, i;
    // int lineNum = 2; 줄번호 출력용 변수

    if(av[1][0] == '-') {                               // 옵션을 주는 경우.
        if(ac > 22) {
            printf("파일은 최대 20개까지만 출력할 수 있습니다.\n");
            return -2;
        }
    /*
     *  if(av[1][1] == 'n') {                           //  줄번호 출력 옵션.
     *      for(i = 2; i < ac; i++) {
     *          if( (fp = fopen(av[i], "r")) == NULL) {
     *              printf("Can't open %s\n", av[i]);
     *              fclose(fp);
     *          }
     *          else {
     *              printf("1  ");
     *              while( (ch = fgetc(fp)) != EOF) {   // fp 파일로부터 한 문자 읽기
     *                  fputc(ch, stdout);              // 읽은 문자 표준 출력으로 보내기
     *                  if(ch == 10) {                  // 10은 개행 문자의 아스키 값
     *                      printf("%d  ", lineNum);
     *                      lineNum += 1;
     *                  }
     *              }
     *          }   
     *          printf("\n");
     *      }
     *  }
     */
	    if(av[1][1] == 'c') {                      // 소문자로 바꿔서 출력
            for(i = 2; i < ac; i++) {
                if( (fp = fopen(av[i], "r")) == NULL)
                        printf("Can't open %s\n", av[i]);
                else {
                    while( (ch = fgetc(fp)) != EOF) {   // fp 파일로부터 한 문자 읽기
                        if( (ch >= 65) & (ch <= 90) )
                            ch += 32;
                        fputc(ch, stdout);              // 읽은 문자 표준 출력으로 보내기
                    }
                    fclose(fp);
        	}
            }
        }
	    else if(av[1][1] == 'C') {                      // 대문자로 바꿔서 출력
            for(i = 2; i < ac; i++) {
                if( (fp = fopen(av[i], "r")) == NULL)
                        printf("Can't open %s\n", av[i]);
                else {
                    while( (ch = fgetc(fp)) != EOF) {   // fp 파일로부터 한 문자 읽기
                        if( (ch >= 95) & (ch <= 122) )
                            ch -= 32;
                        fputc(ch, stdout);              // 읽은 문자 표준 출력으로 보내기
                    }
                    fclose(fp);
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
        if(ac > 21) {
            printf("파일은 최대 20개까지만 출력할 수 있습니다.\n");
            return -2;
        }
        for(i = 1; i < ac; i++) {
            if( (fp = fopen(av[i], "r")) == NULL)
                printf("Can't open %s\n", av[i]);
            else {
                while( (ch = fgetc(fp)) != EOF) {   // fp 파일로부터 한 문자 읽기
                    fputc(ch, stdout);              // 읽은 문자 표준 출력으로 보내기
                }
                fclose(fp);
                printf("\n");
            }
        }
    }

    return 0;
}

