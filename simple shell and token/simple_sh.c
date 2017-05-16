#include <stdio.h>

int main() {
    char str[200];

    while (1) {
        printf("prompt$ ");
	    fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = 0;

        if(strlen(str) == 0)
            continue;

        if(!strcmp(str, "exit"))
            return 0;
        
        else {
            puts(str);
        }
    }
}
