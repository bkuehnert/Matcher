
//TODO: Make this code make sense

#ifndef _parser_h
#define _parser_h

#include <stdbool.h>
#include "Tree.h"

extern bool match(char* s, const char *token);

extern bool Regex(char* s, tr_Node parent);
extern bool Atom(char* s, tr_Node parent);
extern bool Union(char* s, tr_Node parent);
extern bool Concat(char* s, tr_Node parent);
extern bool Closure(char* s, tr_Node parent);
extern bool ParenRegex(char* s, tr_Node parent);
extern bool LeftParen(char* s, tr_Node parent);
extern bool RightParen(char* s, tr_Node parent);


#endif
