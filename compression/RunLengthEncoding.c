#include <stdio.h>

int main(int ac, char *av[]) {
    FILE *fp, *cfp;
    int c, d;
    char buf[200];

    if (ac != 2) {
        printf("Usage: %s filename\n", av[0]);
        return 1;
    }

    if ((fp = fopen(av[1], "rb")) == NULL) {
        printf("Can't open %s\n", av[1]);
        return 2;
    }

    sprintf(buf, "%s.cmp", av[1]);
    if ((cfp = fopen(buf, "wb")) == NULL) {
        printf("Can't open %s\n", buf);
        return 3;
    }

    while ((c = fgetc(fp)) != EOF) {
        unsigned char ccnt = 0;
        while ((d = fgetc(fp)) != EOF) {
            if (c == d) {
                ccnt += 1;
                if (ccnt == 255)
                    break; // MAX VALUE
            }
            else {
                ungetc(d, fp);
                break;
            }
        }
        putc(ccnt, cfp);
        putc(c, cfp);
    }
    fclose(fp);
    fclose(cfp);

    return 0;
}
