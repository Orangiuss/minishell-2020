#include "parser.h"
#include "processus.h"

int main(int argc, char **argv)
{
	char str[MAX_ARGS];
	char *tokens[MAX_ARGS];
    processus_t proc;

    while(1) {
    	printf("karim@minishell:~$ ");
    	fgets(str, MAX_ARGS, stdin);
    	strtok(str, "\n");
    	int nombreArgs = tokenize_str(str, tokens);

	    for(int i = 0; i < nombreArgs; i++) {
	    	proc.argv[i] = tokens[i];
	    }

	    int file = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0440);
	    proc.background = 0;

	    exec_processus(&proc);
    }

	return 0;
}