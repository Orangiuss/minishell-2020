#ifndef BUILTIN_H
#define BUILTIN_H

/*
    Fichier builtin.h : En-tête des fonctions des commandes
                        internes du minishell
    Groupe : n° X
    Auteur :
    Dépendances :
 */


int cd(const char* path);

int export(const char* env);

int unset(const char* env, int fderr);

int env(int fdout, int fderr);

int exit(int val, int fdout, int fderr);

int cwd(int fdout, int fderr);

#endif
