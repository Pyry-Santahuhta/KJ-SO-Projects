//Pyry Santahuhta 0545254 04.02.2021
//Source for stack data structure: https://www.educative.io/edpresso/how-to-implement-a-stack-in-c-using-a-linked-list
//Using stack as our data structure allows us to reverse data automatically since stack functions by LIFO mechanism.

#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node {
    struct Node* next;
    char line[];
}node;

/*Stack functions*/
void push(char data[], node** stack);
const char* top(node* stack);
void pop(node** stack);

/*File functions*/
void readfile(node** stack, char filename[30]);
void writefile(node* stack, char filename[30]);
 
// Append the new element to the start of the stack
void push(char data[], node** stack) {
    /*Allocate memory for a new node*/
    node* pNew = (node*)malloc(sizeof(node));
    if (pNew == NULL) {
        fprintf(stderr, "Memory allocation failed");
        exit(1);
    }
    /*Set the values for a new node and make it the topmost element.*/
    strcpy(pNew->line, data);
    pNew->next = *stack;
    *stack = pNew;
}
 
const char* top(node* stack) {
    if (stack != NULL) {
        /*Skip empty line elements, which includes the root element*/
        if (stack->line == "") {
            return "";
        }
        /*Return only the printable/writable string*/
        return stack->line;
    }
    else {
        fprintf(stdout, "The stack is empty.\n");
    }
}
 
void pop(node** stack) {
    if (*stack != NULL) {
        node* tempPtr = *stack;
        *stack = (*stack)->next;
        free(tempPtr);
    }
    else {
        fprintf(stdout, "The stack is empty.\n");
    }
}
 
int main(int argc, char* argv[]) {
    /*Creating root node with empty line*/
    node* root = (node*)malloc(sizeof(node)); 
    if (root == NULL){
        fprintf(stderr, "Memory allocation failed");
        exit(1);
    }
    root->next = NULL;
    strcpy(root->line, "");

    /* Reversing from stdin file into stdout */
    if (argc == 1) {
        char *buffer;
        fprintf(stdout, "Write reversable lines, enter 0 to quit:\n");
        while (1){
            scanf("%s", buffer);
            strtok(buffer, "\n");
            /*Quit condition*/
            if(strcmp(buffer, "0") == 0){
                break;
            }
            /*Push string on top of stack*/
            push(buffer, &root); 
        }
        fprintf(stdout, "\n");
        /*Iterate through stack printing each topmost element.*/
        while (root != NULL) {
            fprintf(stdout, "%s", top(root));
            fprintf(stdout, "\n");
            pop(&root);
        }

    }
    /* Reversing from input file into stdout */
    else if (argc == 2) {
        readfile(&root, argv[1]);
        /*Iterate through stack printing each topmost element.*/
        while (root != NULL) {
            fprintf(stdout, "%s", top(root));
            fprintf(stdout, "\n");
            pop(&root);
        }
        
    }

    /* Reversing from input file into output file */
    else if (argc == 3) {
        if (strcmp(argv[1],  argv[2]) == 0) {
            fprintf(stderr, "Input and output file must differ\n");
            exit(1);
        }
        readfile(&root, argv[1]);
        writefile(root, argv[2]);
    }
    else {
        fprintf(stdout, "Usage: reverse <input> <output>");
    }
}
 
void readfile(node** stack, char filename[30]) {
    char *line_buffer = NULL;
    size_t line_buffer_size = 0;
    int line_size;
    FILE* file;

    file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: cannot open file\n");
        exit(1);
    }
    else {
        /*Reading file lines without restricting string length*/
        line_size = getline(&line_buffer, &line_buffer_size, file);
        while (line_size >= 0) {
            strtok(line_buffer, "\n");
            push(line_buffer, stack);
            line_size = getline(&line_buffer, &line_buffer_size, file);
            if (ferror(file)) {
                fprintf(stderr, "Failed reading file.");
                exit(1);
            }
        }
        /*Free the used buffer*/
        free(line_buffer);
        line_buffer = NULL;
    }
    fclose(file);
}

void writefile(node* stack, char filename[30]) {
    FILE* file;
    file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stdout, "Error: cannot open file");
        exit(1);
    }
    /*Iterate through stack, writing to file the topmost element.*/
    while (stack != NULL) {
        fprintf(file, "%s",stack->line);
        fprintf(file, "\n");
        pop(&stack);
    }
    fclose(file);
    fprintf(stdout, "Written to file %s succesfully.\n", filename);
}