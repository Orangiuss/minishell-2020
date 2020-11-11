#include "cmdline.h"

int init_process(processus_t *proc, char *tokens[])
{
    for(int i = 0; i < MAX_ARGS; i++) {
        clear_tokens(proc[i].argv);
        proc[i].stdin = 0;
        proc[i].stdout = 1;
        proc[i].stderr = 2;
        proc[i].next = NULL;
        proc[i].next_success = NULL;
        proc[i].next_failure = NULL;
    }
    int proc_idx = 0;
    int tok_idx = 0;
    int i = 0;

    while(tokens[tok_idx] != NULL) {
        if(!strcmp(tokens[tok_idx], "<")) {
            int fd = open(tokens[tok_idx+1], O_RDONLY);
            proc[proc_idx].stdin = fd;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], ">")) {
            int fd = open(tokens[tok_idx+1], O_WRONLY | O_CREAT | O_TRUNC, 0440);
            proc[proc_idx].stdout = fd;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], ">>")) {
            int fd = open(tokens[tok_idx+1], O_WRONLY | O_CREAT | O_APPEND, 0440);
            proc[proc_idx].stdout = fd;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], "|")) {
            proc[proc_idx].background = 1;
            int fd[2];
            pipe(fd);
            proc[proc_idx].stdout = fd[1];
            proc[proc_idx+1].stdin = fd[0];
            proc[proc_idx].next = &proc[proc_idx+1];
            ++proc_idx;
            tok_idx++;
            i=0;
            continue;
        }
        if(!strcmp(tokens[tok_idx], ";")) {
            proc[proc_idx].next = &proc[proc_idx+1];
            ++proc_idx;
            tok_idx++;
            i=0;
            continue;
        }
        if(!strcmp(tokens[tok_idx], "&&")) {
            proc[proc_idx].next_success = &proc[proc_idx+1];
            ++proc_idx;
            tok_idx++;
            i=0;
            continue;
        }
        if(!strcmp(tokens[tok_idx], "||")) {
            proc[proc_idx].next_failure = &proc[proc_idx+1];
            ++proc_idx;
            tok_idx++;
            i=0;
            continue;
        }
        if(!strcmp(tokens[tok_idx], "&")) {
            proc[proc_idx].background = 1;
            ++proc_idx;
            tok_idx++;
            i=0;
            continue;
        }
        // << : créer un fichier temporaire, fgets() tant que != chaine utilisateur, re-ouvrir et mettre en entrer standard
        // "ls -l > test | ls"
        proc[proc_idx].argv[i++] = tokens[tok_idx++];
    }
    return 0;
}

int exec_cmdline(processus_t *proc)
{
    // exec_processus()
    /*for(int i = 0; i < MAX_ARGS; i++) {
        printf("%d. %s\n", i, proc[i].argv[0]);
    }*/
    int i = 0;
    while(i < MAX_ARGS) {
        printf("Executing %s...\n", proc[i].argv[0]);
        exec_processus(&proc[i]);
        sleep(1);
        if(proc[i].next != NULL) {
            printf("Executing %s...\n", proc[i].next->argv[0]);
            exec_processus(proc[i].next);
            i++;
        }
        int status = status_processus(&proc[i]);
        if(proc[i].next_success != NULL) {
            if(status == 0) exec_processus(proc[i].next_success);
            i++;
        }
        if(proc[i].next_failure != NULL) {
            if(status != 0) exec_processus(proc[i].next_failure);
            i++;
        }
        if(proc[i].next == NULL && proc[i].next_success == NULL && proc[i].next_failure == NULL) {
            break;
        }
        i++;
    }
    return 0;
}