#include "shell.h"
#include "utils.h"
#include "command_pwd.h"


void pwd(){
    char* pwd;
    pwd = getcwd(NULL, 0);

    if(!pwd){
        perror("There was an error in getting the current directory\n");
        return;
    }

    printf("%s\n", pwd);
}