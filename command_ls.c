#include "shell.h"
#include "utils.h"
#include "command_ls.h"
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>


void print_ls_perms(mode_t bits){
    char file_perms[] = "----------";

    if (S_ISDIR(bits))
        file_perms[0] = 'd';
    else if (S_ISLNK(bits))
        file_perms[0] = 'l';
    else if (S_ISBLK(bits))
        file_perms[0] = 'b';
    else if (S_ISCHR(bits))
        file_perms[0] = 'c';
    else if (S_ISSOCK(bits))
        file_perms[0] = 's';
    else if (S_ISFIFO(bits))
        file_perms[0] = 'f';
    else if (S_ISREG(bits))
        file_perms[0] = '-';
    else
        file_perms[0] = '?';

    if (bits & S_IRUSR)
        file_perms[1] = 'r';
    if (bits & S_IWUSR)
        file_perms[2] = 'w';
    if (bits & S_IXUSR)
        file_perms[3] = 'x';
    if (bits & S_IRGRP)
        file_perms[4] = 'r';
    if (bits & S_IWGRP)
        file_perms[5] = 'w';
    if (bits & S_IXGRP)
        file_perms[6] = 'x';
    if (bits & S_IROTH)
        file_perms[7] = 'r';
    if (bits & S_IWOTH)
        file_perms[8] = 'w';
    if (bits & S_IXOTH)
        file_perms[9] = 'x';

    printf("%s ", file_perms);
}

void ls(char* str){
    int l = strlen(str);
    int has_l = 0;
    int has_a = 0;
    char* path;
    // strcpy(parsed_string, str);
    // printf("blah: %s\n", str);


    for(int i= 0; i < l; i++){
        if((str[i] == '-') && (i > 0)){
            str[i] = ' ';
            if(str[i-1] == ' '){
                do {
                    if(str[i] == 'a'){
                        has_a = 1;
                        str[i] = ' ';
                    }
                    else if(str[i] == 'l'){
                        has_l = 1;
                        str[i] = ' ';
                    }
                    i++;
                } while((str[i] != ' ') && (i < l));
            }
        }
    }

    path = trim_str(str);

    if(strlen(path) < 1)
        path = ".";

    if(!(strcmp(path, "~")))
        strcpy(path, root_dir);



    DIR *mydir = opendir(path);
    struct dirent *myfile;
    struct stat mystat;

    long int file_size;
    char* file_name;
    struct passwd *pwd;
    struct group *grp;
    char* file_time;

    while((myfile = readdir(mydir)) != NULL){
        stat(myfile->d_name, &mystat);

        pwd = getpwuid(mystat.st_uid);
        grp = getgrgid(mystat.st_gid);
        file_name = myfile->d_name;

        if(!has_a)
            if(file_name[0] == '.'){
                continue;
            }

        if(!has_l){
            printf(" %s\t", file_name);
            continue;
        }

        print_ls_perms(mystat.st_mode);
        printf("%3lu ", mystat.st_nlink);

        if(pwd)
            printf("%10s ", pwd->pw_name);
        else
            // printf("%10ld ", (long)mystat.st_uid);
            printf("     shared");

        if(grp)
            printf("%10s ", grp->gr_name);
        else
            printf("     shared");

        printf("%6ld ", mystat.st_size);


        file_time = asctime(localtime(&(mystat.st_mtime)));
        file_time[strlen(file_time) - 1] = 0;

        printf(" %s ", file_time);
            
        printf(" %s\n", file_name);
    }

    printf("\n");



}
