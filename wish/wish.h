#ifndef __WISH_H__
#define __WISH_H__
    #include <stdio.h>       
    #include <stdlib.h>      
    #include <unistd.h>      
    #include <sys/wait.h>   
    #include <string.h>

    #define BUFF_SIZE 256
    #define TOK_BUFF_SIZE 64
    #define TOK_DELIM " \t\r\n\a"

    char *paths[BUFF_SIZE] = {"/bin", NULL};
    int path_changed = 0;
    int argcount = 0;
    FILE *output = NULL;

    void print_error(int error_code){
        char error_message[30];
        
        switch (error_code){
            case 1:
                strcpy(error_message,"Couldn't open output file\n");
            break;

            case 2:
                strcpy(error_message,"Exit doesn't take arguments\n");
            break;
            
            case 3:
                strcpy(error_message,"usage: cd directory\n");
            break;

            case 4:
                strcpy(error_message,"Couldn't move to directory\n");
            break;

            case 5:
                strcpy(error_message,"Couldn't execute command\n");
            break;

            default:
                strcpy(error_message,"An error has occurred\n");
        }
        
        write(STDERR_FILENO, error_message, strlen(error_message)); 
    }

    char* read_input(FILE *input);
    char **parse_arguments(char *line, FILE*);
    void execute(char *args[], char *line, FILE*);
    void redirect();
    int search_path(char path[], char *firstArg);
#endif