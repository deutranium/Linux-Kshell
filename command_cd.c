#include "shell.h"
#include "utils.h"
#include "command_cd.h"


bool cd(char* path){

    char* temp_prev = getcwd(NULL, 0);

    int cd_err = -2;

    if(path[0] == '-'){
        cd_err = chdir(prev_path);
    }

    else if(*path == 0){
        cd_err = chdir(root_dir);
    }
    else{
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
    }
    
    if(cd_err < 0){
        perror("There was an error while executing cd");
        return false;
    }

    absolute_path = getcwd(NULL, 0);
    strcpy(prev_path, temp_prev);
    return true;
}
