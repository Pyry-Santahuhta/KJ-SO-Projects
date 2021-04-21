#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *file = NULL;
    char buffer[BUFSIZ];
    if (argc <= 1){
       exit(0);
    }

    for (size_t i = 1; i < argc; i++){
        if((file = fopen(argv[i], "r")) == NULL){
            printf("my-cat: cannot open file\n");
            exit(1);
        }

        while(fgets(buffer, BUFSIZ, file)){
            printf("%s", buffer); 
        }

        fclose(file);    
    }

    
}