#include "shell.h"
#include "utils.h"
#include "command_echo.h"

void echo(char* str){
    size_t l = strlen(str);
    for(int i = 0; i < l; i++){
        if((str[i] == ' ') && (str[i+1] == ' '))
            i++;
        else
            printf("%c", str[i]);
    }
    printf("\n");

    return;
}
