#include "builtin.h"

/*
    Fichier builtin.c : Fonctions des commandes internes du minishell
    Groupe : n° 34
    Auteur : DUFOUR Richard
    Dépendances : builtin.h
 */

int cd(const char* path) {
	if (chdir(path) == -1) {
		perror("cd");
		return 1;
	}
	return 0;
}

int export(char* env) {
	printf("EXPORT\n");
	char *p;
	if(p = strtok(env,"=")) {
		if(p = strtok(NULL, "")) {
			setenv(env, p, 0);
		}
		else {
			perror("export");
			return 1;
		}
	}
	else {
		perror("export");
			return 1;
	}
	return 0;
}

int unset(const char* env, int fderr) {
	printf("UNSET\n");
	if (fderr!=0)
	{
		return fderr;
		printf("Erreur %s du builtin unset\n", fderr);
	}
	else {
		if (env!=NULL)
		{
			env=NULL;
			perror("unset");
		}
		return 0;
	}
}

int env(int fdout, int fderr) {
	if (fderr==0)
	{
		printf("ENV\n");
		int i;
	   	for (i=0 ; environ[i]!=NULL ; i++)
	      puts(environ[i]);
	   	return 0;
	}
	else {
		return fderr;
	}
}

int exitbuilt(int val, int fdout, int fderr) {
	if (fderr!=0)
	{
		return fderr;
		printf("Erreur %s du builtin exit\n", fderr);
	}
	else {
		printf("exit : %d\n", val);
		exit(val);
		perror("exit");
		return 0;
	}
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
		exitbuilt(cmd[1],2,0);
	else if (!strcmp(cmd[0], "cd"))
		cd(cmd[1]);
	else if (!strcmp(cmd[0], "export"))
		export(cmd[1]);
	else if (!strcmp(cmd[0], "cwd"))
		cwd(NULL,NULL);
	else if (!strcmp(cmd[0], "env"))
		env(0,0);
	else if (!strcmp(cmd[0], "unset"))
		unset(cmd[1],0);
}