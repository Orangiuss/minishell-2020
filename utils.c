#include "utils.h"

size_t count_tokens(char* tokens[])
{
	size_t count = 0;

	for(int i = 0; i < MAX_ARGS; i++) {
		if(tokens[i] != NULL) count++;
	}

	return count;
}

char **clear_tokens(char* tokens[])
{
	for(int i = 0; i < MAX_ARGS; i++) {
		if(tokens[i] != NULL) tokens[i] = NULL;
	}
}

char **insert(char* tokens[], char* elts[], size_t pos);

char **del_token(char* tokens[], size_t pos);