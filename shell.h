#ifndef __SHELL_H
#define __SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <stdbool.h>

char* logged_user_name;
char* host_name;
char* root_dir;

char* relative_path;
char* absolute_path;
char* prev_path;

char* command_list[100][1000];

#define MAX_STAT_LEN 1024
#define STAT_COUNT 52 


#endif