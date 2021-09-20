#include "shell.h"
#include "utils.h"
#include "external_commands.h"

#include <signal.h>
#include <sys/types.h> 
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>



void handle_bg_terminate(int sig, siginfo_t *info, void *ucontext)
{
    char proc_file[PATH_MAX], proc_name[PATH_MAX];
    int wstatus;
    pid_t pid = info->si_pid;


    sprintf(proc_file, "/proc/%d/comm", pid);


    int success_read = 0;
    sprintf(proc_file, "/proc/%d/comm", info->si_pid);
    int stat_file = open(proc_file, O_RDONLY, 0);
    read(stat_file, proc_name, PATH_MAX);
    basename(proc_name);
    proc_name[strlen(proc_name) - 1] = '\0';
    close(stat_file);


    pid = waitpid(pid, &wstatus, WNOHANG);
    if (pid > 0){
        if (success_read)
            fprintf(stderr, "\n%s with pid %d exited %s\n", proc_name, pid, info->si_status ? "abnormally" : "normally");
        
        else
            fprintf(stderr, "\nProcess with pid %d exited %s\n", pid, info->si_status ? "abnormally" : "normally");
        
        fflush(stderr);
    }
}




void handle_external(char* str){

    str = trim_str(str);
    int position = 0;
    int is_bg = 0;

    int this_buf_size = TOK_BUFFER_SIZE;

    char **tokens = malloc(this_buf_size * sizeof(char*));
    char *token;

    if(!tokens){
        fprintf(stderr, "allocation error");
    }

    token = strtok(str, " ");

    while(token != NULL){
        tokens[position] = token;
        position++;
        token = strtok(NULL, " ");
    }

    tokens[position] = NULL;

    if(!(strcmp(tokens[position-1], "&"))){
        tokens[position-1] = NULL;
        is_bg = 1;
    }



    pid_t pid;
    pid = fork();


    if(pid < 0){
        perror("Fork error");
        printf("There was an error in creating the process");
        return;
    }
    else if(pid == 0){
        setpgid(0, 0);

        int blah = execvp(tokens[0], tokens);
        if( blah < 0){
            perror("Error with execvp");
            return;
        }

        exit(1);
    }
    else{
        setpgid(pid, pid);

        if(is_bg){
            printf("%d\n", pid);
            struct sigaction sa;
            sa.sa_sigaction = &handle_bg_terminate;
            sa.sa_flags = SA_NOCLDSTOP | SA_RESTART | SA_SIGINFO;
            sigaction(SIGCHLD, &sa, NULL);
            return;
        }
        else {
            int par_pid = getpgrp();
            int status;

            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(STDIN_FILENO, pid);

            waitpid(pid,&status,WUNTRACED);

            tcsetpgrp(STDIN_FILENO, par_pid);
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

        }
    }


    return;
}
