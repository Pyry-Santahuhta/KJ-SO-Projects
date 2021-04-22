/*
*   Pyry Santahuhta 0545254
*   CT30A3370 22.4.2021
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *file = NULL;
    char buffer[BUFSIZ];

    if (argc <= 1){
       exit(0);
    }

    /*Go through args opening them as files*/
    for (size_t i = 1; i < argc; i++){
        if((file = fopen(argv[i], "r")) == NULL){
            printf("my-cat: cannot open file\n");
            exit(1);
        }

        /*Print output*/
        while(fgets(buffer, BUFSIZ, file)){
            printf("%s", buffer); 
        }

        fclose(file);    
    }
    return 0;
}