#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <string.h>

/*
    Fichier builtin.h : En-tête des fonctions des commandes
                        internes du minishell
    Groupe : n° X
    Auteur :
    Dépendances :
 */

extern char **environ;

static const char *built_in[] = {"cd", "export", "unset", "env", "exit", "cwd"};

int cd(const char* path);

int export(char* env);

int unset(const char* env, int fderr);

int env(int fdout, int fderr);

int exitbuilt(int val, int fdout, int fderr);

int cwd(int fdout, int fderr);

int is_builtin(char *cmd);

void exec_builtin(char **built_in);

#endif
