#include "builtin.h"

/*
    Fichier builtin.c : Fonctions des commandes internes du minishell
    Groupe : n° 34
    Auteur : DUFOUR Richard
    Dépendances : builtin.h
 */

/*
  	Fonction cd : Se déplace dans un dossier grâce à la fonction chdir()
  	Paramètre path : le chemin du dossier
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int cd(const char* path) {
	if (chdir(path) == -1) { // chdir pour se déplacer dans le chemin path
		perror("cd"); // Affiche l'erreur s'il y en a une
		return 1;
	}
	return 0;
}

/*
  	Fonction export : Définit ou modifie une variable d'environnment
  	Paramètre env : Le nom de la variable d'environnement 
  					à exporter avec sa valeur (de la forme variable=valeur)
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int export(char* env) {
	char *p;
	// Découpe la chaine pour séparer le nom de la variable et la valeur (var=valeur)
	if(p = strtok(env,"=")) { 
		// Met la valeur dans p
		if(p = strtok(NULL, "")) {
			setenv(env, p, 0);
			return 0;
		}
		else {
			perror("export"); // Erreur du strtok
			return 1;
		}
	}
	else {
		perror("export"); // Erreur du strtok
			return 1;
	}
	return 1;
}

/*
  	Fonction unset : Détruit une variable d'environnement
  	Paramètre env : Le nom de la variable d'environnement 
  	Paramètre fderr : Descripteur de la sortie d'erreur
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int unset(const char* env, int fderr) {
	// Détruit la variable
	if(unsetenv(env)!=0) { 
		// Affiche sur la sortie d'erreur s'il y a une erreur
		write(fderr, "Erreur de unset", strlen("Erreur de unset")); 
		return 1;
	} 
	else {
		return 0;
	}
}

/*
  	Fonction env : Affiche toutes les variables d'environnement
  	Paramètre fdout : Descripteur de la sortie
  	Paramètre fderr : Descripteur de la sortie d'erreur
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int env(int fdout, int fderr) {
	for (int i=0 ; environ[i]!=NULL ; i++){
	   	write(fdout, environ[i], strlen(environ[i]));
	    write(fdout, "\n", strlen("\n"));
	}
	return 0;
}

/*
  	Fonction exitbuilt : Quitte le processus en cours
  	Paramètre val : La valeur du code de retour du programme
  	Paramètre fdout : Descripteur de la sortie
  	Paramètre fderr : Descripteur de la sortie d'erreur
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int exitbuilt(int val, int fdout, int fderr) {
		if(val==0) {
			write(fdout, "Exit Success : 0", strlen("Exit Success : 0"));
	    	write(fdout, "\n", strlen("\n"));
	    	exit(val);
	    	return 0;
		}
		else {
			write(fderr, "Exit Failure : ", strlen("Exit Failure : "));
	    	write(fderr, "\n", strlen("\n"));
	    	exit(val);
	    	return 1;
		}
		return 1;
}

/*
  	Fonction cwd : Affiche le répertoire courant
  	Paramètre fdout : Descripteur de la sortie
  	Paramètre fderr : Descripteur de la sortie d'erreur
    Retourne 0 en cas de succès, 1 en cas d'échec
*/
int cwd(int fdout, int fderr)
{	
	char cwd[PATH_MAX];
	for (int i = 0; i < sizeof(cwd); ++i)
	{
		cwd[i] = '\0'; // Initialise tout le tableau avec des caractères nuls
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL) { // On obtient le répertoire courant
	    write(fdout, cwd, strlen(cwd)); // Affiche le résultat sur la sortie
	    write(fdout, "\n", strlen("\n"));
	    return 0;
	} else {
		write(fderr, "Erreur de cwd", strlen("Erreur de cwd")); // Affiche sur la sortie d'erreur s'il y a une erreur
		write(fdout, "\n", strlen("\n"));
		return 1;
	}
}

/*
  	Fonction is_builtin : Permet de savoir si la commande executée 
  						  est une commande interne du minishell
  	Paramètre cmd : Commande executée
    Retourne 0 si la commande n'est pas une commande interne
    et 1 si la commande est une commande interne
*/
int	is_builtin(char *cmd)
{
	for (int i = 0; built_in[i]; i++) {
		if (!strcmp(built_in[i], cmd)) // On regarde si la commande est dans la liste des commandes internes
			return 1;
	}
	return 0;
}

/*
  	Fonction exec_builtin : Exécute une commande interne
  	Paramètre cmd : Commande executée avec tout ses paramètres
  	Paramètre fdout : Descripteur de la sortie
  	Paramètre fderr : Descripteur de la sortie d'erreur
*/
void exec_builtin(char **cmd, int fdout, int fderr)
{
	if (!strcmp(cmd[0], "exit")) {
	    int exitvalue=0;
	    if(cmd[1]!=NULL) {
	    	sscanf(cmd[1], "%d", &exitvalue); 
	    	// Convertir la valeur de sortie en entier
	    }
		exitbuilt(exitvalue,fdout,fderr);
	}
	else if (!strcmp(cmd[0], "cd")) {
		cd(cmd[1]);
	}
	else if (!strcmp(cmd[0], "export")) {
		export(cmd[1]);
	}
	else if (!strcmp(cmd[0], "cwd")) {
		cwd(fdout,fderr);
	}
	else if (!strcmp(cmd[0], "env")) {
		env(fdout,fderr);
	}
	else if (!strcmp(cmd[0], "unset")) {
		unset(cmd[1],fderr);
	}
} 