#include "utils.h"
#include "shell.h"


// initialise the main variables
void init(){
    root_dir = getcwd(NULL, 0);
    absolute_path = getcwd(NULL, 0);
    // strcpy(relative_path, root_dir);

    logged_user_name = getlogin();
    host_name = (char*)malloc(sizeof(char) * (HOST_NAME_MAX + 1));
    gethostname(host_name, HOST_NAME_MAX);
}

bool str_prefix(const char* pre, const char* str){
    return strncmp(pre, str, strlen(pre)) == 0;
}

void get_relative_path(char* path){

    // root_dir = getcwd(NULL, 0);
    printf("Root: %s\n", root_dir);
    printf("Path: %s\n", path);

    if(strlen(path) < strlen(root_dir)){
        relative_path = path;
        printf("%d", 1);
    }
    else if(!(strcmp(path, root_dir) == 0)){
        relative_path = "~";
        printf("%d", 2);
    }
    else{
        strncpy(relative_path, &path[strlen(root_dir)], (strlen(path) - strlen(root_dir) + 1));
        printf("%d", 3);
    }

    printf("New: %s\n", relative_path);
}
