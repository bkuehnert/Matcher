/*
 * Author: Ben Kuehnert
 *
 * NFA (epsilon-less or not);
 */

#ifndef _nfa_h
#define _nfa_h

#include "Set.h"

struct _NFA {
	int num_states;
	char* description;
	Set cur_states;
	Set** trans_table;
	bool* accept_table;
	bool epsilon;
};

typedef struct _NFA* NFA;

/**
 * Allocate and return a new NFA containing the given number of states.
 */
extern NFA new_NFA(int nstates, char* desc);

/**
 * Free the given NFA.
 */
extern void NFA_free(NFA nfa);

/**
 * Return the number of states in the given NFA.
 */
extern int NFA_get_size(NFA nfa);

/**
 * Return the set of next states specified by the given NFA's transition
 * function from the given state on input symbol sym.
 */
extern Set NFA_get_transitions(NFA nfa, int state, char sym);

/**
 * For the given NFA, add the state dst to the set of next states from
 * state src on input symbol sym.
 */
extern void NFA_add_transition(NFA nfa, int src, char sym, int dst);

/**
 * Add a transition for the given NFA for each symbol in the given str.
 */
extern void NFA_add_transition_str(NFA nfa, int src, char *str, int dst);


/**
 * Add a transition for the given NFA for each input symbol.
 */
extern void NFA_add_transition_all(NFA nfa, int src, int dst);

/**
 * Add a transition for all chars except for the given symbol
 */
extern void NFA_add_transition_except(NFA nfa, int src, char sym, int dst);

/**
 * Set whether the given NFA's state is accepting or not.
 */
extern void NFA_set_accepting(NFA nfa, int state, bool value);

/**
 * Return true if the given NFA's state is an accepting state.
 */
extern bool NFA_get_accepting(NFA nfa, int state);

/**
 * Remove epsilon transitions
 */
extern NFA NFA_removeEpsilon(NFA nfa);

/**
 * Run the given NFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
extern bool NFA_execute(NFA nfa, char *input);

/**
 * Print the given NFA to System.out.
 */
extern void NFA_print(NFA nfa);

extern void NFA_reset(NFA nfa);

#endif
