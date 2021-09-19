#include "shell.h"
#include "utils.h"
#include "command_pinfo.h"

#include <stdio.h>

void pinfo(char* str){

    int pid;
    char file_stat[MAX_STAT_LEN + 1] = {'\0'};
    char file_path[PATH_MAX];

    str = trim_str(str);

    if(strlen(str) < 1){
        pid = getpid();
    }
    else {
        pid = atoi(str);
    }


    if(!pid){
        perror("Enter a correct process ID");
        return;
    }

    char* stat_path = (char*)malloc(sizeof(char) * 25);
    sprintf(stat_path, "/proc/%d/status", pid);

    FILE* proc_file = fopen(stat_path, "r");

    if(!proc_file){
        perror("There was an error while getting proccess info");
        return;
    }

    fread(file_stat, MAX_STAT_LEN, 1, proc_file);
    fclose(proc_file);

    char* attrs[STAT_COUNT] = {NULL};
    attrs[0] = strtok(file_stat, " ");

    for(int i = 1; attrs[i-1] != NULL; i++)
        attrs[i] = strtok(NULL, " ");

    printf("pid -- %d\n", (int)pid);
    printf("Process Status -- %s\n", attrs[2]);
    printf("memory -- %s\n", attrs[22]);

    sprintf(file_path, "/proc/%d/exe", pid);
    char execPath[PATH_MAX + 1];
    memset(execPath, 0, PATH_MAX);
    int readStat = readlink(file_path, execPath, PATH_MAX);

    // if (readStat != -1)
    //     shortenPath(INVOC_LOC, execPath);
    // printf("Executable Path -- %s\n", readStat == -1 ? "Doesn't exist" : execPath);
    // return 0;

    printf("Executable Path -- %s\n", get_relative_path(execPath));
    
}
