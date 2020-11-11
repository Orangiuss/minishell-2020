#include "processus.h"

/*
    Fichier process.h : En-tête des fonctions de gestion des
                        processus indépendants.
    Groupe : n° 23
    Auteur : FERKIOUI Karim
    Dépendances : unistd
 */

int exec_processus(processus_t *proc)
{
    printf("%s executed\n", proc->argv[0]);
    if((proc->pid = fork()) == 0) {
        dup2(proc->stdin, 0);
        dup2(proc->stdout, 1);
        dup2(proc->stderr, 2);
        if(proc->stdin != 0) close(proc->stdin);
        if(proc->stdout != 1) close(proc->stdout);
        if(proc->stderr != 2) close(proc->stderr);
        /*for(int i = 0; i < MAX_ARGS; i++) {
            if(proc->argv[i] != NULL) printf("%s\n", proc->argv[i]);
        }*/
        execvp(proc->argv[0], proc->argv);
    } else {
        if(proc->background == 0) waitpid(proc->pid, &proc->status, 0);
    }

    return 0;
}

int status_processus(processus_t *proc)
{
    int status = 0;
    waitpid(proc->pid, &proc->status, WNOHANG);
    return proc->status;
}