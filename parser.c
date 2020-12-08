#include "parser.h"

int trim_str(char *str)
{
    char *str2 = str;
    int length = strlen(str);
    int n = 0;
    
    while(isblank(*str2++)) n++; // Récupere le nombre d'espace en début de chaine
    
    while(n--) { // On effectue n décalage vers la gauche
        for(int i = 1; i < length; i++) {
            str[i-1] = str[i];
        }
    } 
    
    while(*++str != '\0'); // On se deplace à la fin de la chaine
    while(isblank(*--str)); // On avance vers la gauche tant qu'on tombe sur un espace
    *++str = '\0';
    
    return 0;
}

int clean_str(char *str)
{
    char *str2 = str;
    
    while(*str != '\0') {
        *str2++ = *str;
        
        if(isblank(*str)) {
            while(isblank(*++str));
            --str;
        }
        
        str++;
    }
    
    *str2 = '\0';

    return 0;
}

int tokenize_str(char *str, char *tokens[])
{
    char *str2 = str; // On fait une copie du pointeur
    int length;
    int argsCount = 0;

    trim_str(str); // On enleve les espaces de début et de fin
    clean_str(str); // On enleve les espaces en milieu de chaine
    length = strlen(str);

    for(int i = 0; i < length; i++) {
        // Si on tombe sur un espace, on le remplace par le char de fin de chaine
        // On met ensuite l'adresse de début du mot avant l'espace dans tokens[i]
        if(isblank(str[i])) {
            str[i] = '\0';
            tokens[argsCount] = str2;
            str2 = &str[i+1];
            argsCount++;
        }
    }

    tokens[argsCount] = str2;
    for(int i = argsCount+1; i < MAX_ARGS; i++) tokens[i] = NULL;
    return argsCount+1; // argsCount+1 car argsCount commence à 0
}

int env_str(char *tokens[]) {
    int i=0;
    char* temp;
    while(tokens[i]!=NULL) {    
        if (strncmp (tokens[i],"$",1) == 0)
        {
            temp = tokens[i]+1;
              if(getenv(temp)!=NULL) {
                tokens[i]=getenv(temp);
            }
        }
        i++;
    }
    return 0;    
}