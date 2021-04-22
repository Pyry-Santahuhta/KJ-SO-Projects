/*
*   Pyry Santahuhta 0545254
*   CT30A3370 25.2.2021
*   Help from: https://brennan.io/2015/01/16/write-a-shell-in-c/
*/

#include "wish.h"

char* read_input(FILE *input){
    char *line = NULL;
    size_t len = 0;
    ssize_t lineLen = 0;
    /*Reading from input*/
    if((lineLen = getline(&line, &len, input)) > 0){
        /*Removing newline*/
        if(line[lineLen-1] == '\n'){
            line[lineLen-1] = '\0';
        }
    }
    if (lineLen == -1) {
        free(line);
        return NULL;
    }
    return line;
}

char **parse_arguments(char *line, FILE* input){
    char* token;
    int buffer = TOK_BUFF_SIZE; 
    /*Cut the input line into tokens*/
    token = strtok(line, TOK_DELIM);
    output = stdout;
    /*Store arguments in unsized doublepointer*/
    char **args = malloc(buffer*sizeof(char*));

    if(!args){
        print_error(0);
        exit(EXIT_FAILURE);
    }
  
    while(token != NULL){
        /*For using parallel commands, execute current command with args and continue reading line*/
        if(strcmp(token,"&") == 0){
            args[argcount] = NULL;
            execute(args, line, input);
            args = malloc(buffer*sizeof(char*));
            if(!args){
                print_error(0);
                exit(EXIT_FAILURE);
            }
        }
        /*Redirection implementation, change output to arg after >*/
        else if(strcmp(token, ">") == 0){
            token = strtok(NULL, TOK_DELIM);
            if ((output = fopen(token, "w")) == NULL){
                print_error(1);
                return NULL;
            }
        }
        else{
            /*Store token in args*/
            args[argcount] = token;
            argcount++;
        }
        /*Increase size dynamically*/
        if(argcount >= buffer){
            buffer += TOK_BUFF_SIZE;
            args = realloc(args, buffer*sizeof(char*));

            if(!args){
                print_error(0);
                exit(EXIT_FAILURE);
            }       
        }
        /*Get next token*/
        token = strtok(NULL, TOK_DELIM);
    }
    args[argcount] = NULL;
    return args;
}

void execute(char *args[], char *line, FILE* input){
    int i, status;
    if(args[0] != NULL){
        if(strcmp(args[0], "exit") == 0){
            if(argcount > 1){
                print_error(2);
            }
            else{
                /*Freeing and closing everything before exit*/
                free(args);
                free(line);
                if(path_changed){
                    free(*paths);
                }
                fclose(input);
                fclose(output);
                exit(EXIT_SUCCESS);
            }
        }
        /*Moving working directory with chdir*/
        else if(strcmp(args[0], "cd") == 0){
            if(argcount == 1 || argcount > 2){
                print_error(3);
            }
            else{
                if(chdir(args[1]) == -1){
                    print_error(4);
                }
            }
        }
        /*Changes path for runnable commands*/
        else if(strcmp(args[0], "path") == 0){
            paths[0] = NULL;
            path_changed = 1;
            for (i = 0; i < argcount - 1; i++){
                paths[i] = strdup(args[i+1]);
            }
            paths[i+1] = NULL;
        }
        else{
            char path[BUFF_SIZE];
            if(search_path(path, args[0]) == 0){
                pid_t pid; 
                pid = fork();
                if(pid == -1){
                    /*If fork fails, kill all processes from process group*/
                    killpg(getpgrp(), SIGKILL);
                    exit(1);
                }
                else if(pid == 0){
                    /*In child process*/
                    redirect();
                    if(execvp(args[0],args) == -1){
                        print_error(0);
                    }
                    
                }
                else{
                    /*Wait for child process to change status*/
                    waitpid(pid, &status, 0);
                    /*Also close output if input is ended*/
                    if(feof(input)){
                        fclose(output);
                    }
                    
                }
            }
            else{
                print_error(5);
            }
        }
    }
    free(args);
    argcount = 0;
}

void redirect(){
    int outputFileNo;
    if ((outputFileNo = fileno(output)) == -1){
        print_error(0);
        return;
    }
    /*Changing std output path*/
    if (outputFileNo != STDOUT_FILENO){
        if (dup2(outputFileNo, STDOUT_FILENO) == -1){
            print_error(0);
            return;
        }
        if (dup2(outputFileNo, STDERR_FILENO) == -1){
            print_error(0);
            return;
        }
    }
}

int search_path(char path[], char *firstArg){
    // search executable file in path
    int i = 0;
    while (paths[i] != NULL){
        snprintf(path, BUFF_SIZE, "%s/%s", paths[i], firstArg);
        if (access(path, X_OK) == 0)
            return 0;
        i++;
    }
    return -1;
}

int main(int argc, char *argv[]){
    /*Check for the mode, other mode is batch mode*/
    int interactive_mode = 1;
    
    FILE *input = stdin;
    char *line;
    char **args;

    /*If the user inputs more arguments than 1, use batch mode*/
    if(argc > 1) {
        /*Works only with two arguments.*/
        if(argc < 3) {
            interactive_mode = 0;
            if((input = fopen(argv[1],"r")) == NULL){
                exit(EXIT_FAILURE);
            }
        } else {
            exit(EXIT_FAILURE);
        }     
    }

    /*Loop running the shell*/
    while (1) {
        if(interactive_mode) {
            printf("wish> ");
        }
        /*EOF in input, exit succesfully*/
        if((line = read_input(input)) == NULL) {
            fclose(input);
            fclose(output);
            if(path_changed) {
                free(*paths);
            }
            exit(EXIT_SUCCESS);
        }
        args = parse_arguments(line, input);
        execute(args, line, input);
        free(line);     
    }
    return 0;
}
