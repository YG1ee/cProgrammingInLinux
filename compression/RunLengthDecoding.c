#include <stdio.h>
#include <string.h>

int main(int ac, char *av[]) {
    FILE *fp, *cfp;
    int c, d, num;
    char buf[200];

    if (ac != 2) {
        printf("Usage: %s filename\n", av[0]);
        return 1;
    }

    if ((fp = fopen(av[1], "rb")) == NULL) { // 압축된 cmp 파일 읽어들이기
        printf("Can't open %s\n", av[1]);
        return 2;
    }

    sprintf(buf, "%s.restore", av[1]); // 내용을 복구할 파일
    if ((cfp = fopen(buf, "wb")) == NULL) {
        printf("Can't open %s\n", buf);
        return 3;
    }

    while ((c = fgetc(fp)) != EOF) {
        num = c+1;
        d = fgetc(fp);
        for (int i = 0; i < num; i += 1)
            putc(d, cfp);
    }
    fclose(fp);
    fclose(cfp);

    return 0;
}
