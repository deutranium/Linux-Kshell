#ifndef __UTILS_H
#define __UTILS_H

#include <stdbool.h>

void init();
void get_relative_path(char* path);
bool str_prefix(const char* pre, const char* str);

#endif