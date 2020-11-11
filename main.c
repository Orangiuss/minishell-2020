#include "parser.h"
#include "processus.h"
#include "utils.h"
#include "cmdline.h"

int main(int argc, char **argv, char **envp)
{
	char str[MAX_LINE_SIZE];
	char *tokens[MAX_ARGS];
    processus_t proc[MAX_ARGS];

    char cwd[PATH_MAX];

	while(1) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
           printf("karim@minishell:");
           printf("\033[31m\033[1m%s\033[0m~$", cwd);
        } else {
            perror("getcwd()");
        }
    	fgets(str, MAX_ARGS, stdin);
    	strtok(str, "\n");
    	int nombreArgs = tokenize_str(str, tokens);
    	env_str(tokens);

        /*clear_tokens(proc.argv);
        proc.stdin = 0;
        proc.stdout = 1;
        proc.stderr = 2;
        proc.next = NULL;
        proc.next_success = NULL;
        proc.next_failure = NULL;

	    for(int i = 0; i < nombreArgs; i++) {
	    	proc.argv[i] = tokens[i];
	    }

	    int file = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0440);
	    proc.background = 0;*/

        init_process(proc, tokens);
        exec_cmdline(proc);
    }

	return 0;
}
