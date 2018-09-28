/*
 * Author: Ben Kuehnert
 *
 * Header for converting RE's to e-NFA's
 */

//todo: need better names for these functions?

//Note that all accepting states are the last state, so
//accept_table[i] = true 
//if and only if 
//i = nfa->num_states-1

#ifndef _RE_NFA
#define _RE_NFA

#include "NFA.h"
#include <stdlib.h>
#include <stdio.h>

//Create an e-NFA for an atomic character
extern NFA create_Atomic(char x);

//Create an e-NFA from the concatenation of two NFA's
//This also frees the two given NFA's?
extern NFA create_Concat(NFA a, NFA b);

//Create an e-NFA from the union of two NFA's
extern NFA create_Union(NFA a, NFA b);

//Create an e-NFA from the closure of one NFA
extern NFA create_Closure(NFA a);

#endif
