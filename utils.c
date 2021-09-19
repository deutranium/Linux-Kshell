#include "utils.h"
#include "shell.h"

#include "command_cd.h"
#include "command_pwd.h"
#include "command_echo.h"
#include "command_ls.h"


// initialise the main variables
void init(){
    root_dir = getcwd(NULL, 0);
    absolute_path = getcwd(NULL, 0);
    prev_path = getcwd(NULL, 0);

    logged_user_name = getlogin();
    host_name = (char*)malloc(sizeof(char) * (HOST_NAME_MAX + 1));
    gethostname(host_name, HOST_NAME_MAX);
}

// check if pre is a prefix of str
bool str_prefix(const char* pre, const char* str){
    return strncmp(pre, str, strlen(pre)) == 0;
}

// get relative path
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

char* trim_str(char* orig_str){

    char new_orig[PATH_MAX + 1] = "";
    strcpy(new_orig, orig_str);

    int count = 0;
    static char str[1000] = "";

    for(int i = 0; i < 1000; i++)
        str[i] = 0;

    for(int i = 0; new_orig[i] != '\0'; i++){
        if(new_orig[i] == '\t')
            new_orig[i] = ' ';
    }

    while(new_orig[count] == ' '){
        count++;
    }

    for(int i = count, j = 0; new_orig[i] != 0; i++, j++){
        str[j] = new_orig[i];
    }
    int new_len = strlen(str);

    for(int i = new_len - 1; i > 0; i--){
        if(str[i] != ' '){
            break;
        }
        else{
            str[i] = 0;
        }
    }
    return(str);
}

void run_command(char* command){
    if(str_prefix("cd", command)){
        cd(&command[3]);
    }
    else if(str_prefix("pwd", command)){
        pwd();
    }
    else if(str_prefix("echo", command)){
        echo(&command[5]);
    }
    else if(str_prefix("ls", command)){
        ls(&command[2]);
    }

    return;
}

// parse input string
void parse_input_string(char* str){
    
    const char s[2] = ";";
    char *token;

    char* trimmed_token;
   
    /* get the first token */
    token = strtok(str, s);

    /* walk through other tokens */
    while( token != NULL ) {
        trimmed_token = trim_str(token);

        run_command(trimmed_token);

        token = strtok(NULL, s);
    }

    return;
}
