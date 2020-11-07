#ifndef CMDLINE_H
#define CMDLINE_H

/*
    Fichier cmdline.h : En-tête des fonctions de gestion de
                        la ligne de commande.
    Groupe : n° X
    Auteur :
    Dépendances :
 */


#include "processus.h"

/*
  Fonction init_process : Crée l'enchaînement de processus à partir du
                          tableau tokens
      Paramètre proc : pointeur sur la structure à remplir
      Paramètre tokens :  tableau (NULL-terminated) contenant les chaînes
                          de la ligne de commande à analyser
      Retourne 0 en cas de succés et une autre valeur en cas d'échec
 */
int init_process(process_t *proc, char *tokens[]);

/*
  Fonction exec_cmdline : Lance les processus de la ligne de commande dans
                          l'ordre attendu en respect des conditions demandées
      Paramètre proc : la structure décrivant les processus à lancer
      Retroune 0 en cas de succés et une autre valeur en cas d'échec
 */
int exec_cmdline(process_t *proc);


#endif

