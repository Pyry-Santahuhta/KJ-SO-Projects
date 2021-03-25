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

    void print_error(){
        char error_message[30] = "An error has occurred\n";
        write(STDERR_FILENO, error_message, strlen(error_message)); 
    }

    char* read_input(FILE *input);
    char **parse_arguments(char *line, FILE*);
    void execute(char *args[], char *line, FILE*);
    void redirect();
    int search_path(char path[], char *firstArg);
#endif