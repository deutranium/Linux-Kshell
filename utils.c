#include "utils.h"
#include "shell.h"


// initialise the main variables
void init(){
    root_dir = getcwd(NULL, 0);
    absolute_path = getcwd(NULL, 0);
    prev_path = getcwd(NULL, 0);

    logged_user_name = getlogin();
    host_name = (char*)malloc(sizeof(char) * (HOST_NAME_MAX + 1));
    gethostname(host_name, HOST_NAME_MAX);
}

bool str_prefix(const char* pre, const char* str){
    return strncmp(pre, str, strlen(pre)) == 0;
}

void get_relative_path(char* path){

    char temp_root_dir[PATH_MAX];
    char temp_ch = '/';
    strcpy(temp_root_dir, root_dir);
    strncat(temp_root_dir, &temp_ch, 1);

    if(!strcmp(root_dir, path)){
        strcpy(relative_path, "~");
    }
    else if(!str_prefix(temp_root_dir, path)){
        strcpy(relative_path, path);
    }
    else{
        strncpy(relative_path, &path[strlen(root_dir)], (strlen(path) - strlen(root_dir) + 2));
    }
}
