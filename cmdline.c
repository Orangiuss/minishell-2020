#include "cmdline.h"

/*
    Fichier cmdline.c : Fonctions de gestion de
                        la ligne de commande.
    Groupe : n° 34
    Auteur : FERKIOUI Karim - DUFOUR Richard
    Dépendances : cmdline.h
*/

/*
  Fonction init_process : Crée l'enchaînement de processus à partir du
                          tableau tokens
  Paramètre proc : pointeur sur la structure à remplir
      Paramètre tokens :  tableau (NULL-terminated) contenant les chaînes
                          de la ligne de commande à analyser
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int init_process(processus_t *proc, char *tokens[])
{
    // On reinitialise tous les processus
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

    // On regarde si la chaine actuelle est un mot clé
    // Pour les redirections, on ouvre le fichier avec les permissions necessaires
    // puis on le definit en tant que stdin/stdout/stderr du processus
    // Si c'est un enchainement de commande, on met le processus suivant dans les champs next
    while(tokens[tok_idx] != NULL) {
        if(!strcmp(tokens[tok_idx], "<")) {
            int fd = open(tokens[tok_idx+1], O_RDONLY);
            proc[proc_idx].stdin = fd;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], ">")) {
            int fd = open(tokens[tok_idx+1], O_WRONLY | O_CREAT | O_TRUNC, 0660);
            proc[proc_idx].stdout = fd;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], "2>")) {
            int fd = open(tokens[tok_idx+1], O_WRONLY | O_CREAT | O_TRUNC, 0660);
            proc[proc_idx].stderr = fd;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], ">>")) {
            int fd = open(tokens[tok_idx+1], O_WRONLY | O_CREAT | O_APPEND, 0660);
            proc[proc_idx].stdout = fd;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], "2>>")) {
            int fd = open(tokens[tok_idx+1], O_WRONLY | O_CREAT | O_APPEND, 0660);
            proc[proc_idx].stderr = fd;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], "2>&1")) {
            proc[proc_idx].stderr = proc[proc_idx].stdout;
            tok_idx+=2;
            continue;
        }
        if(!strcmp(tokens[tok_idx], ">&2")) {
            proc[proc_idx].stdout = proc[proc_idx].stderr;
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
        proc[proc_idx].argv[i++] = tokens[tok_idx++];
    }
    return 0;
}

/*
  Fonction exec_cmdline : Lance les processus de la ligne de commande dans
                          l'ordre attendu en respect des conditions demandées
      Paramètre proc : la structure décrivant les processus à lancer
      Retroune 0 en cas de succés et une autre valeur en cas d'échec
 */
int exec_cmdline(processus_t *proc)
{
    int i = 0;
    // Si l'utilisateur n'a pas entrer une ligne vide
    while(proc[i].argv[0]!=NULL) {
        // On execute le processus
        exec_processus(&proc[i]);
        // On verifie si c'est un enchainement de processus
        if(proc[i].next != NULL) {
            exec_processus(proc[i].next);
            i++;
        }

        // On recupere le status du processus courant pour executer ou non l'enchainement
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