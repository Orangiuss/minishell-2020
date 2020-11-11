#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main()
{
    char *ls_cmd[] = {"echo", "SUCCESS\nFAILURE", NULL};
    char *cw_cmd[] = {"wc", "-l", NULL};
    pid_t pid;
    int tube[2];
    
    pipe(tube);
    
    if(!(pid = fork())) {
        dup2(tube[1], STDOUT_FILENO);
        close(tube[0]);
        execvp(ls_cmd[0], ls_cmd);
    } else {
        dup2(tube[0], STDIN_FILENO);
        close(tube[1]);
        execvp(cw_cmd[0], cw_cmd);
    }

    return 0;
}