#include "Parser.h"

#include <string.h>
#include <stdlib.h>

bool match(char** s, const char *token)
{
	if(strncmp(*s, token, strlen(token)) == 0) {
		*s+=1;
		return true;
	}
	return false;
}


