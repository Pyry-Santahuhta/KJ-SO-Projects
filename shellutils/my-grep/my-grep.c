/*
*   Pyry Santahuhta 0545254
*   CT30A3370 22.4.2021
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *file = NULL;
    char *line = NULL;
    size_t limit = 0;

    /*Must have more args than 1*/
    if (argc <= 1){
        printf("my-grep: searchterm [file ...]\n");
        exit(1);
    }

    /*If only the searchable term is specified, search from stdin*/
    if(argc == 2){
        file = stdin;
    }
    
    /*Search from all files*/
    if (argc >= 3){
        if((file = fopen(argv[2], "r")) == NULL){
            printf("my-grep: cannot open file\n");
            exit(1);
        }
    }
    /*Read through files line at a time*/
    while(getline(&line, &limit, file) > 0){
        /*Try to find string within string with strstr, if so, print the line*/
        if(strstr(line, argv[1])){
            printf("%s", line);
        }
    }

    free(line);
    fclose(file);
    
    return 0;
}