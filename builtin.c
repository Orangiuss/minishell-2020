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
			printf("%s\n", p);
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
	
		unsetenv(env);
		return 0;

}

int env(int fdout, int fderr) {

		printf("ENV\n");
		int i;
	   	for (i=0 ; environ[i]!=NULL ; i++)
	      puts(environ[i]);
	   	return 0;

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
	    fprintf(fdout,"%s\n", cwd);
	} else {
		fprintf(fderr,"%s\n", cwd);
	}
	return 0;
}

int	is_builtin(char *cmd)
{
	for (int i = 0; built_in[i]; i++) {
		if (!strcmp(built_in[i], cmd))
			return 1;
	}
	return 0;
}

void exec_builtin(char **cmd, int fdout, int fderr)
{
	if (!strcmp(cmd[0], "exit"))
		exitbuilt(cmd[1],fdout,fderr);
	else if (!strcmp(cmd[0], "cd"))
		cd(cmd[1]);
	else if (!strcmp(cmd[0], "export"))
		export(cmd[1]);
	else if (!strcmp(cmd[0], "cwd"))
		cwd(fdout,fderr);
	else if (!strcmp(cmd[0], "env"))
		env(fdout,fderr);
	else if (!strcmp(cmd[0], "unset"))
		unset(cmd[1],fderr);
}