#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define segmentsize 5;


int main(int argc, char *argv[]){
    FILE *file = NULL;
    char c[2], previous_c[2];
    int count = 0;

    if (argc <= 1){
        printf("my-unzip: file1 [file2 ...]");
        exit(1);
    }

    for (size_t i = 1; i < argc; i++){
        if((file = fopen(argv[i], "r")) == NULL){
            printf("my-cat: cannot open file\n");
            exit(1);
        }

        while(fread(c, 1, 1, file)){
            if(feof(file)){
                break;
            }

            if(strcmp(c, previous_c) == 0){
                count++;
            }else{
                if(previous_c != "\0"){
                    fwrite(&count, 4, 1, stdout);
                    fwrite(previous_c, 1, 1, stdout);
                }
                count = 1;
                strcpy(previous_c, c);

            } 
        }
        fclose(file);    
    }

    
}