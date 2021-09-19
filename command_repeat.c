#include "shell.h"
#include "utils.h"
#include "command_ls.h"

void repeat(char* str){
    char num_str[PATH_MAX];
    char new_cmd[PATH_MAX];
    int count = 0;

    str = trim_str(str);

    strcpy(num_str, str);

    for(int i = 0; i < strlen(str) - 1; i++){
        if(str[i] == ' '){
            break;
            num_str[i] = 0;
        }

        count++;
    }

    int num_rep = atoi(num_str);

    strcpy(new_cmd, &str[count+1]);


    for(int j = 0; j < num_rep; j++){
        run_command(new_cmd);
    }

    return;
}
