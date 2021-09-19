#include "shell.h"
#include "utils.h"
#include "external_commands.h"


void handle_external(char* str){

    str = trim_str(str);
    int position = 0;

    int this_buf_size = TOK_BUFFER_SIZE;

    char **tokens = malloc(this_buf_size * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "allocation error");
    }

    token = strtok(str, " ");

    while(token != NULL){
        tokens[position] = token;
        position++;

        if(position >= this_buf_size){
            this_buf_size += TOK_BUFFER_SIZE;
            tokens = realloc(tokens, this_buf_size * sizeof(char*));

            if(!tokens){
                fprintf(stderr, "allocation error");
            }
        }

        token = strtok(NULL, " ");
    }

    tokens[position] = NULL;

    execvp(tokens[0], tokens);


    return;
}
