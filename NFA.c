#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "NFA.h"
#include "Set.h"

#define memleft(x) if(x == NULL){printf("Out of memory...\n"); return NULL;}

NFA
new_NFA(int nstates, char* desc)
{
	NFA this = (struct _NFA*)malloc(sizeof(struct _NFA));	
	memleft(this);

	//allocate current states set, make sure to add 0 as initial state
	this->cur_states = new_Set();
	Set_insert(this->cur_states, 0);
	this->num_states = nstates;
	this->accept_table = (bool*)calloc(nstates, sizeof(bool));
	memleft(this->accept_table);

	this->trans_table = (Set**)malloc(nstates*sizeof(Set*));
	memleft(this->trans_table);	
	for (int i = 0; i<nstates; i++)
	{
		this->trans_table[i] = (Set*)malloc(129*sizeof(Set));
		memleft(this->trans_table[i]);
		for (int j = 0; j<129; j++)
		{
			this->trans_table[i][j] = new_Set();
		}
	}
	this->description = desc;

	return this;
}

void
NFA_free(NFA nfa)
{
	free_Set(nfa->cur_states);
	free(nfa->accept_table);
	for ( int i = 0; i < nfa->num_states; i++ ){
		for ( int j = 0; j < 129; j++ )
			free_Set(nfa->trans_table[i][j]);
		free(nfa->trans_table[i]);
	}
	free(nfa->trans_table);
	free(nfa);
}

int
NFA_get_size(NFA nfa)
{
	return nfa->num_states;
}

Set NFA_get_transitions(NFA nfa, int state, char sym)
{
	return nfa->trans_table[state][(int)sym];
}

void
NFA_add_transition(NFA nfa, int src, char sym, int dst)
{
	Set_insert(nfa->trans_table[src][(int)sym],dst);
}

void
NFA_add_transition_str(NFA nfa, int src, char *str, int dst)
{
	while (*str != '\0')
	{
		NFA_add_transition(nfa,src,*str,dst);
		str+=1;
	}
}

void
NFA_add_transition_all(NFA nfa, int src, int dst)
{
	for (int i = 0; i<128; i++)
	{
		Set_insert(nfa->trans_table[src][i], dst);
	}
}

void
NFA_add_transition_except(NFA nfa, int src, char sym, int dst)
{
	for(int i = 0; i<128; i++)
	{
		if(i != (int) sym)
			NFA_add_transition(nfa, src, (char) i, dst);
	}
}

void
NFA_set_accepting(NFA nfa, int state, bool value)
{
	nfa->accept_table[state] = value;	
}

bool
NFA_get_accepting(NFA nfa, int state)
{
	return nfa->accept_table[state];
}

//experimental
bool
NFA_execute(NFA nfa, char *input)
{
	while(*input != '\0')
	{
		Set next = new_Set();
		for(int i =0; i<SIZE; i++)
			if(Set_in(nfa->cur_states,i))
				Set_union(next, nfa->trans_table[i][(int)*input]);
		free_Set(nfa->cur_states);
		nfa->cur_states = next;
		input+=1;
	}
	
	for (int i=0; i<SIZE; i++)
		if(Set_in(nfa->cur_states,i))
			if(nfa->accept_table[i])
				return true;

	return false;
}

void
NFA_reset(NFA nfa)
{
	free_Set(nfa->cur_states);
	nfa->cur_states = new_Set();
	Set_insert(nfa->cur_states, 0);
}
