#ifndef __UTILS_H
#define __UTILS_H

#include <stdbool.h>

void init();
char* get_relative_path(char* path);
bool str_prefix(const char* pre, const char* str);
char* trim_str(char* trim_str);
void parse_input_string(char* str);
void run_command(char* command);

#endif