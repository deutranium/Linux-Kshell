#include "shell.h"
#include "utils.h"
#include "command_cd.h"


bool cd(char* path){

    int cd_err = -2;

    printf("CD: %s\n", path);

    if(!strcmp(&path[0], "~")){
        cd_err = chdir(root_dir);
        path += 2;

        if(strlen(path) > 0){
            cd_err = chdir(path);
        }
    }
    else{
        cd_err = chdir(path);
    }

    if(cd_err < 0){
        perror("There was an error while executing cd");
        return false;
    }

    return true;
}
