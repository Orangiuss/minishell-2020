#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <string.h>
#include <unistd.h>

/*
    Fichier builtin.h : En-tête des fonctions des commandes
                        internes du minishell
    Groupe : n° 34
    Auteur : DUFOUR Richard
    Dépendances : stdio.h, stdlib.h, linux/limits.h, string.h, unistd.h
 */

// Variables d'environnements
extern char **environ;

// Liste des commandes internes du minishell
static const char *built_in[] = {"cd", "export", "unset", "env", "exit", "cwd"};

/*
  	Fonction cd : Se déplace dans un dossier grâce à la fonction chdir()
  	Paramètre path : le chemin du dossier
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int cd(const char* path);

/*
  	Fonction export : Définit ou modifie une variable d'environnment
  	Paramètre env : Le nom de la variable d'environnement 
  					à exporter avec sa valeur (de la forme variable=valeur)
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int export(char* env);

/*
  	Fonction unset : Détruit une variable d'environnement
  	Paramètre env : Le nom de la variable d'environnement 
  	Paramètre fderr : Descripteur de la sortie d'erreur
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int unset(const char* env, int fderr);

/*
  	Fonction env : Affiche toutes les variables d'environnement
  	Paramètre fdout : Descripteur de la sortie
  	Paramètre fderr : Descripteur de la sortie d'erreur
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int env(int fdout, int fderr);

/*
  	Fonction exitbuilt : Quitte le processus en cours
  	Paramètre val : La valeur du code de retour du programme
  	Paramètre fdout : Descripteur de la sortie
  	Paramètre fderr : Descripteur de la sortie d'erreur
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int exitbuilt(int val, int fdout, int fderr);

/*
  	Fonction cwd : Affiche le répertoire courant
  	Paramètre fdout : Descripteur de la sortie
  	Paramètre fderr : Descripteur de la sortie d'erreur
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int cwd(int fdout, int fderr);

/*
  	Fonction is_builtin : Permet de savoir si la commande executée 
  						  est une commande interne du minishell
  	Paramètre cmd : Commande executée
    Retourne 0 si la commande n'est pas une commande interne
    et 1 si la commande est une commande interne
*/
int is_builtin(char *cmd);

/*
  	Fonction exec_builtin : Exécute une commande interne
  	Paramètre cmd : Commande executée avec tout ses paramètres
  	Paramètre fdout : Descripteur de la sortie
  	Paramètre fderr : Descripteur de la sortie d'erreur
*/
void exec_builtin(char **cmd, int fdout, int fderr);

#endif
