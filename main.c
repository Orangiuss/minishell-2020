#include "parser.h"
#include "processus.h"
#include "utils.h"
#include "cmdline.h"

/*
    Fichier utils.c : Fonctions utilitaires
    Groupe : n° 34
    Auteur : FERKIOUI Karim - DUFOUR Richard
    Dépendances : parser.h, processus.h, utils.h, cmdline.h
 */

int main(int argc, char **argv, char **envp)
{
	char str[MAX_LINE_SIZE];
	char *tokens[MAX_ARGS];
    processus_t proc[MAX_ARGS];

    char cwd[PATH_MAX];

	while(1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
        	char *USER;
        	if (USER=getenv("USER")) 
        	{
        		printf("\033[32m\033[1m%s\033[0m", USER); // Si on obtient l'user on l'affiche
        	}
 	        printf("\033[92m@minishell:\033[0m"); 
            printf("\033[34m\033[1m%s\033[0m~$ ", cwd); // On affiche le repertoire courant
        } else {
            perror("getcwd()");
        }
    	fgets(str, MAX_ARGS, stdin); // On obtient l'entrée standard
    	strtok(str, "\n");
    	trim_str(str);
    	clean_str(str);
    	tokenize_str(str, tokens);
    	env_str(tokens);

        init_process(proc, tokens);
        exec_cmdline(proc);
        clear_tokens(tokens);
    }

	return 0;
}
