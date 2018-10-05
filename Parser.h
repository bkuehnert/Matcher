
//TODO: Make this code make sense

#ifndef _parser_h
#define _parser_h

#include <stdbool.h>
#include "Tree.h"

extern bool match(char** s, char token);

extern bool R(char** s);
extern bool T(char** s);
extern bool F(char** s);
extern bool C(char** s);
extern bool B(char** s);
extern bool S(char** s);

extern bool wrap(char** s);

#endif
