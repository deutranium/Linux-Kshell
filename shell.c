#include "prompt.h"
#include "shell.h"

int main (void){

    char* line_ptr = NULL;
    size_t line_buffer_size = 0;
    ssize_t line_size = 0;

    while(1){

        free(line_ptr);

        line_buffer_size = 0;
        line_size = 0;

        prompt();
        line_size = getline(&line_ptr, &line_buffer_size, stdin);

        if (line_size <= 0){
            free(line_ptr);
            break;
        }
    }

    return 0;
}