#include "builtin.h"

/*
    Fichier builtin.c : Fonctions des commandes internes du minishell
    Groupe : n° 34
    Auteur : DUFOUR Richard
    Dépendances : builtin.h
 */

int cd(const char* path) {
	if (chdir(path) == -1) {
		perror("chdir()");
	}
	return 0;
}

int export(const char* env) {
	printf("EXPORT\n");
}

int unset(const char* env, int fderr) {
	printf("UNSET\n");
}

int env(int fdout, int fderr) {
	printf("ENV\n");
}

int exitbuilt(int val, int fdout, int fderr) {
	exit(0);
}

int cwd(int fdout, int fderr)
{	
	printf("CWD\n");
	char cwd[PATH_MAX];
	
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
	       printf("%s\n", cwd);
	} else {
		perror("getcwd()");
	}
}

int	is_builtin(char *cmd)
{
	for (int i = 0; built_in[i]; i++) {
		if (!strcmp(built_in[i], cmd))
			return 1;
	}
	return 0;
}

void exec_builtin(char **cmd)
{
	if (!strcmp(cmd[0], "exit"))
		exitbuilt(1,2,3);
	else if (!strcmp(cmd[0], "cd"))
		cd(cmd[1]);
	else if (!strcmp(cmd[0], "export"))
		export(cmd[1]);
	else if (!strcmp(cmd[0], "cwd"))
		cwd(NULL,NULL);
}