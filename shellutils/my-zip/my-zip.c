/*
*   Pyry Santahuhta 0545254
*   CT30A3370 22.4.2021
*   Reading with fgetc source: https://www.geeksforgeeks.org/fgetc-fputc-c/
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    FILE *file = NULL;
    char c, previous_c = '\0';
    int count = 0;
    
    /*Must have more args than 1*/
    if (argc <= 1){
        printf("my-zip: file1 [file2 ...]\n");
        exit(1);
    }

    /*Go through args, opening each one as file if possible*/
    for (size_t i = 1; i < argc; i++){
        if((file = fopen(argv[i], "r")) == NULL){
            printf("my-zip: cannot open file\n");
            exit(1);
        }
        /*Read through file one character at a time*/
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
    /*Writing count+character*/
    fwrite(&count, 4, 1, stdout);
    fwrite(&previous_c, 1, 1, stdout);
    
    return 0;
}