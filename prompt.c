#include "prompt.h"
#include "shell.h"
#include "utils.h"

void prompt(){
    // char* abs_path = getcwd(NULL, 0);
    // get_relative_path(abs_path);

    absolute_path = getcwd(NULL, 0);

    printf("%s@%s | %s →  ", logged_user_name, host_name, absolute_path);

    // free(abs_path);
}