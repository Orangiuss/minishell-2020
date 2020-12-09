#include "processus.h"

/*
    Fichier processus.c : Fonctions de gestion des
                          processus indépendants.
    Groupe : n° 34
    Auteur : FERKIOUI Karim - DUFOUR Richard
    Dépendances : processus.h
*/

/*
  Fonction exec_processus : Permet le lancement d'un processu avec les
  propriétés choisies (redirections, lancement en "arrière plan", ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int exec_processus(processus_t *proc)
{
    // On vérifie si c'est une commande interne
    if(is_builtin(proc->argv[0]))
    {
    	exec_builtin(proc->argv,proc->stdout,proc->stderr);
    	if(proc->stdin != 0) close(proc->stdin);
	    if(proc->stdout != 1) close(proc->stdout);
	    if(proc->stderr != 2) close(proc->stderr);
    } else {
        if((proc->pid = fork()) == 0) {
            dup2(proc->stdin, 0);
            dup2(proc->stdout, 1);
            dup2(proc->stderr, 2);
            // Si la fonction n'a pas pu executer le processus, on ferme les descripteurs
            // puis on quitte le processus fils
           	if(execvp(proc->argv[0], proc->argv) == -1) {
           		if(proc->stdin != 0) close(proc->stdin);
		        if(proc->stdout != 1) close(proc->stdout);
		        if(proc->stderr != 2) close(proc->stderr);
           		exit(0);
           	}
        } else {
        	if(proc->stdin != 0) close(proc->stdin);
	        if(proc->stdout != 1) close(proc->stdout);
	        if(proc->stderr != 2) close(proc->stderr);
            // Si le processus n'est pas lancé en arriere plan, on l'attend
            if(proc->background == 0) {
            	waitpid(proc->pid, &proc->status, 0);
            }
        }
   	}
    return 0;
}

/*
 Fonction status_processus :  récupérer le status d'un processus (en cours,
                              terminé, ...)
      Paramètre proc : pointeur sur une structure décrivant le processus
      Retourne le "status" d'un processus lancé en arrière plan
 */
int status_processus(processus_t *proc)
{
    // On recupere le status du processus sans attendre sa fin
    waitpid(proc->pid, &proc->status, WNOHANG);
    return proc->status;
}