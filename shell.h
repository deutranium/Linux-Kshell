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

char relative_path[PATH_MAX + 1];
char* absolute_path;
char* prev_path;


#endif