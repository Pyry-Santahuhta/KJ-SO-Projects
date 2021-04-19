#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *file = NULL;
    char *line = NULL;
    size_t limit = 0;

    if (argc <= 1){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    if(argc == 2){
        file = stdin;
    }
    
    if (argc >= 3){
        if((file = fopen(argv[2], "r")) == NULL){
            printf("my-grep: cannot open file\n");
            exit(1);
        }
    }

    while(getline(&line, &limit, file) > 0){
        if(strstr(line, argv[1])){
            printf("%s", line);
        }
    }

    free(line);
    fclose(file);
}