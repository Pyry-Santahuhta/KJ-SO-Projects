#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *file = NULL;
    char c, previous_c = '\0';
    int count = 0;

    if (argc <= 1){
        printf("my-zip: file1 [file2 ...]");
        exit(1);
    }

    for (size_t i = 1; i < argc; i++){
        if((file = fopen(argv[i], "r")) == NULL){
            printf("my-zip: cannot open file\n");
            exit(1);
        }

        do{
            c = fgetc(file);
            if(feof(file)){
                break;
            }
			    
            if(c == previous_c){
                count++;
            }else{
                if(previous_c != '\0'){
                    fwrite(&count, 4, 1, stdout);
                    fwrite(&previous_c, 1, 1, stdout);
                }
                count = 1;
                previous_c = c;

            } 
        }while(1);
        fclose(file);    
    }
    fwrite(&count, 4, 1, stdout);
    fwrite(&previous_c, 1, 1, stdout);
    fclose(stdout);
}