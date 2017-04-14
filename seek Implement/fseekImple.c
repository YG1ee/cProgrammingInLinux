// mycatImple 기반의 대소문자 변환 프로그램 코드

#include <stdio.h>
#include <ctype.h>
#define MAX_CNT 20

int main(int ac, char *av[]) {
    int ch, i;
    FILE *fp;
    int ismax = ac > MAX_CNT;

    if( (ac>=2)&&(av[1][0] == '-') )    // 옵션을 주는 경우.
        if(av[1][1] == 'c' || av[1][1] == 'C') {
            if(ac > MAX_CNT+2) {
                printf("파일은 최대 20개까지만 출력할 수 있습니다.\n");
                for(i = 0; i < ac-(MAX_CNT+2); i++)
                    printf("ignoring %s..\n", av[i+22]);
                printf("\n");
                ac = MAX_CNT+2;
            }
            
            if(av[1][1] == 'c') {   // 소문자 출력 옵션.
                for(i = 2; i < ac; i++) {
                    if( (fp = fopen(av[i], "r+")) == NULL)
                        printf("Can't open %s\n", av[i]);
                    else {
                        while( (ch = fgetc(fp)) != EOF) {
                            if(isupper(ch))
                                ch = tolower(ch);
                            fseek(fp, -1, SEEK_CUR);
                            fputc(ch, fp);
                        }
                        fclose(fp);
                        printf("Successfully converted to lower case.\n");
                    }
                }
            }
        
            if(av[1][1] == 'C') {                           // 대문자 출력 옵션.
                for(i = 2; i < ac; i++) {
                    if( (fp = fopen(av[i], "r+")) == NULL)
                        printf("Can't open %s\n", av[i]);
                    else {
                        while( (ch = fgetc(fp)) != EOF) {       // fp 파일로부터 문자 읽어오기
                            if(islower(ch))
                                ch = toupper(ch);
                            fseek(fp, -1, SEEK_CUR);
                            fputc(ch, fp);
                        }
                        fclose(fp);
                        printf("Successfully converted to upper case.\n");
                    }
                }
            }
        }
        else { // pass
        printf("구현되지 않은 기능입니다.\n");
        return -1;
        }

    else {
        if(ac > MAX_CNT+1) {
        printf("파일은 최대 20개까지만 출력할 수 있습니다.\n");
            for(i = 0; i < ac-(MAX_CNT+1); i++)
                printf("ignoring %s..\n", av[i+21]);
            printf("\n");
            ac = MAX_CNT+1;
        }

        for(i = 1; i < ac; i++) {
            if( (fp = fopen(av[i], "r+")) == NULL)
                printf("Can't open %s\n", av[i]);
            else {
                while( (ch = fgetc(fp)) != EOF)
                    fputc(ch, fp);
                fclose(fp);
            }
        }
    }
    return 0;
}
