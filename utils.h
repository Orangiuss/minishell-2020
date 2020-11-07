#ifndef UTILS_H
#define UTILS_H

/*
    Fichier utils.h : En-tête des fonctions utilitaires
    Groupe : n° X
    Auteur :
    Dépendances :
 */

#include <stdlib.h>

#include "parser.h"

/*
 Fonction count_tokens :  Compte le nombre de tokens dans le tableau
                          NULL-terminated
      Paramètre tokens :  tableau NULL-terminated de chaînes de caractères
      Retourne le nombre de chaînes dans le tableau.
 */
size_t count_tokens(char *tokens[]);

/*
  Fonction clear_tokens : Vide le tableau tokens
      Paramètre tokens : le tableau à réinitialiser
      Retourne le pointeur sur le tableau ou NULL en cas d'erreur
 */
char **clear_tokens(char *tokens[]);

/*
  Fonction insert : Insert les éléments de elts dans tokens à partir
                    de la position pos
      Paramètre tokens : le tableau dans lequel on insert les valeurs
      Paramètre elts : le tableau des éléments à insérer
      Paramètre pos : la position à laquelle on insert les éléments
      Retourne le pointeur sur tokens ou NULL en cas d'erreur
 */
char **insert(char *tokens[], char *elts[], size_t pos);

/*
  Fonction del_token : Supprime un élément dans tokens
      Paramètre tokens : le tableau duquel on veut retirer l'élément
      Paramètre pos : la position de l'élément à supprimer
      Retourne le pointeur sur tokens ou NULL en cas d'erreur
 */
char **del_token(char *tokens[], size_t pos);

#endif
