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

    for (size_t i = 1; i < argc; i++){
        if((file = fopen(argv[i], "r")) == NULL){
            printf("my-unzip: cannot open file\n");
            exit(1);
        }

        while(fread(&count, 4, 1, file)){
            fread(&c, 1, 1, file);
            for (size_t j = 0; j < count; j++){
                printf("%s", c);
            }
        } 
        fclose(file);    
    }
    return 0;
}
