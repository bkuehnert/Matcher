
//TODO: Make this code make sense

#ifndef _parser_h
#define _parser_h

#include <stdbool.h>
#include "Tree.h"

extern bool match(char** s, char token);

extern Node R(char** s);
extern Node A(char** s);
extern Node B(char** s);
extern Node C(char** s);
extern Node D(char** s);
extern Node E(char** s);

extern Node wrap(char** s);

#endif
