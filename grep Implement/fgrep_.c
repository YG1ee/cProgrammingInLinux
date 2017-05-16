#include <stdio.h>
#include <string.h>

int main(int ac, char *av[]) {
    FILE *fp;
    char buf[200];
    int i, j, state = 0;
    int plen;

    if(ac < 3) {
        printf("Usage: %s pattern filename ..\n", av[0]);
		return -1;
    }
    plen = strlen(av[1]);

    for(i = 2; i < ac; i+=1) {
        if( (fp = fopen(av[i], "r")) == NULL) {
	    printf("Can't open %s\n", av[i]);
	    return -2;
		}

		while(fgets(buf, sizeof(buf), fp) != NULL) {
			int blen = strlen(buf);
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
		fclose(fp);
    }
    return 0;
}
