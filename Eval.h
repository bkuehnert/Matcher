#ifndef _eval_h
#define _eval_h

#include "Tree.h"
#include "RE_NFA.h"
#include "NFA.h"

NFA buildNFA(Node root);

NFA build_R(Node root);
NFA build_A(Node root);
NFA build_C(Node root);

#endif
