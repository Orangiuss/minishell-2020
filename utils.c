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
		if(tokens[i] != NULL) tokens[i] = NULL;
	}

    return tokens;
}

// elts must be null terminated
char **insert(char *tokens[], char *elts[], size_t pos)
{
    //char *str2 = tokens[pos];
    int length = 0;
    int a = 0;
    
    while(elts[length] != NULL) length++;
    
    if(MAX_ARGS-length <= 0) return NULL;
    
    for(int i = 0; i < length; i++) {
        for(int j = MAX_ARGS-1; j > pos; j--) {
            tokens[j] = tokens[j-1];
        }
    }
    
    for(int i = pos; i < pos+length; i++) {
        tokens[i] = elts[a];
        a++;
    }
    
    return tokens;
}

char **del_token(char *tokens[], size_t pos)
{
    for(int i = pos; i < MAX_ARGS-1; i++) tokens[i] = tokens[i+1];
    tokens[MAX_ARGS] = NULL;
    
    return tokens;
}