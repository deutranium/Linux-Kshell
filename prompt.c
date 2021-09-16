#include "prompt.h"
#include "shell.h"

void prompt(){
    char* abs_path = getcwd(NULL, 0);
    // char* path = get_relative_pwd(abs_path);

    printf("%s@%s | %s →  ", logged_user_name, host_name, abs_path);

    free(abs_path);
}