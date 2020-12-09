#include "parser.h"

/*
    Fichier parser.c : Fonctions de traitement de
                       la ligne de commande
    Groupe : n° 34
    Auteurs : FERKIOUI Karim
    Dépendances : parser.h
 */

/*
    Fonction clean_str : Supprime les doublons de caractères d'espacement (' '
                         et '\t') à l'intérieur de la chaîne
    Paramètre str : la chaîne à modifier
    Retourne 0 en cas de succés, une autre valeur en cas d'échec
*/
int clean_str(char *str)
{
    char *str2 = str;
    
    while(*str != '\0') {
        *str2++ = *str;

        // Si on tombe sur un espace
        if(isblank(*str)) {
            // On boucle jusqu'au dernier si il y a plusieurs espaces consecutifs
            while(isblank(*++str));
            --str;
        }
        str++;
    }
    
    *str2 = '\0';

    return 0;
}

/*
  Fonction trim_str : Supprime les caractères d'espacement (' ' et '\t') au
                      début et à la fin de la chaîne
      Paramètre str : la chaîne à modifier
      Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int trim_str(char *str){
    
    char *pos = str;
    char *fin = str;

    // Tant que l'on tombe sur un espace/tab, on avance de 1 caractère dans la chaine
    while(isblank(*pos)) {
        ++pos;              
    }

    // Tant que *pos est different de '\0'
    while(*pos) {
        // Si ce n'est pas un un espace/tab, on se déplace vers la droite de la chaine
        if (!isblank(*pos)) {
            fin = str+1;
        }
        *str++ = *pos++;
    }
    *fin = '\0'; // On ajoute le caractère de fin de chaine

    return 0;
}
 
/*
    Fonction tokenize_str : Découpe la ligne sur les caractères d'espacement
                          (' ' et '\t') et enregistre les pointeurs sur le
                          début de chaque mot dans tokens (NULL-terminated)
    Paramètre str : la chaîne à découper
    Paramètre tokens : le tableau dans lequel stocker les éléments de str
    Retourne le nombre de chaînes dans tokens
 */
int tokenize_str(char *str, char *tokens[]) {
    int i=0;
    char *pos;
    pos = strtok(str," "); // On tokenize grace à la fonction strtok
    while (pos != NULL)
    {
        tokens[i]=pos;
        pos = strtok(NULL, " ");
        i++;
    }
    return 0;
} 

/*
    Fonction env_str :  Remplace les noms des variables d'environnement par
                      leur contenu dans tokens (terminé par NULL)
    Paramètre tokens : le tableau dans lequel les substitutions sont faites
    Retourne 0 en cas de succés, une autre valeur en cas d'échec
 */
int env_str(char *tokens[])
{
    char *env;
    
    // Pour chaque élément de tokens, on vérifie si c'est une variable d'environnement
    for(int i = 0; i < MAX_ARGS; i++) {
        if(tokens[i] != NULL) {
            env = getenv(tokens[i]+1); // +1 pour ne pas prendre en compte le $
            if(env != NULL) {
                tokens[i] = env;
            }
        }
    }
}