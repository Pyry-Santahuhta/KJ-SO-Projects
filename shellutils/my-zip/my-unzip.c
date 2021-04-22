/*
*   Pyry Santahuhta 0545254
*   CT30A3370 22.4.2021
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *file = NULL;
    char c[1];
    int count = 0;

    if (argc <= 1){
        printf("my-unzip: file1 [file2 ...]");
        exit(1);
    }
    
    /*Go through args opening them as files*/
    for (size_t i = 1; i < argc; i++){
        if((file = fopen(argv[i], "r")) == NULL){
            printf("my-unzip: cannot open file\n");
            exit(1);
        }

        /*Read the integer from before the character into count*/
        while(fread(&count, 4, 1, file)){
            /*Read the character into c*/
            fread(&c, 1, 1, file);
            /*Print count amount of character c*/
            for (size_t j = 0; j < count; j++){
                printf("%s", c);
            }
        } 
        fclose(file);    
    }
    return 0;
}
