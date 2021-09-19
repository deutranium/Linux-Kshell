#include "shell.h"
#include "prompt.h"
#include "utils.h"
#include "command_cd.h"
#include "command_pwd.h"
#include "command_echo.h"

int main(void){

    char* line_ptr = NULL;
    size_t line_buffer_size = 0;
    ssize_t line_size = 0;

    init();

    while(1){

        free(line_ptr);
        line_ptr = malloc(sizeof(char)*500);

        line_buffer_size = 0;
        line_size = 0;

        prompt();
        line_size = getline(&line_ptr, &line_buffer_size, stdin);

        if (line_size <= 0){
            free(line_ptr);
            break;
        }

        line_ptr[strlen(line_ptr) - 1] = 0;

        if(str_prefix("cd", line_ptr)){
            cd(&line_ptr[3]);
        }
        else if(str_prefix("pwd", line_ptr)){
            pwd();
        }
        else if(str_prefix("echo", line_ptr)){
            echo(&line_ptr[5]);
        }
    }

    return 0;
}