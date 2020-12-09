#include "utils.h"

size_t count_tokens(char* tokens[])
{
	size_t count = 0;

	for(int i = 0; i < MAX_ARGS; i++) {
		if(tokens[i] != NULL) count++;
	}

	return count;
}

char **clear_tokens(char *tokens[])
{
	for(int i = 0; i < MAX_ARGS; i++) {
		if(tokens[i] != NULL) { tokens[i] = NULL; }
	}
    return tokens;
}

// elts must be null terminated
char **insert(char *tokens[], char *elts[], size_t pos)
{
    //char *str2 = tokens[pos];
    int length = 0;
    int a = 0;
    
    while(elts[length] != NULL) length++; // On calcul la taille du tableau
    
    //Si on a pas assez de place dans le tokens, on retourne NULL
    if(MAX_ARGS-count_tokens(tokens)-length <= 0) return NULL;
    
    // On décale vers la droite chaque element de tokens, a partir de la position d'insertion, vers la droite
    for(int i = 0; i < length; i++) {
        for(int j = MAX_ARGS-1; j > pos; j--) {
            tokens[j] = tokens[j-1];
        }
    }
    
    // On ajoute les éléments de elts à tokens à partir de la position d'insertion
    for(int i = pos; i < pos+length; i++) {
        tokens[i] = elts[a];
        a++;
    }
    
    return tokens;
}

char **del_token(char *tokens[], size_t pos)
{
    // On décale vers la gauche tous les éléments du tableau à partir de la position
    for(int i = pos; i < MAX_ARGS-1; i++) tokens[i] = tokens[i+1];
    // On met la dernière case du tableau à NULL
    tokens[MAX_ARGS] = NULL;
    
    return tokens;
}