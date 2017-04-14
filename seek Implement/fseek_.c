#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;

    if(argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return -2;
    }

    if((fp = fopen(argv[1], "r+")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        return -1;
    }

    while((c=fgetc(fp)) != EOF) {
        if(islower(c))
            c = toupper(c);
        fseek(fp, -1, SEEK_CUR);
        fputc(c, fp);
    }
    
    fclose(fp);
    
    return 0;
}