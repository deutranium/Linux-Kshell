#include "utils.h"
#include "shell.h"


// initialise the main variables
void init(){
    logged_user_name = getlogin();
    host_name = (char*)malloc(sizeof(char) * (HOST_NAME_MAX + 1));
    gethostname(host_name, HOST_NAME_MAX);
}
