#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
		this->trans_table[i] = (Set*)malloc(128*sizeof(Set));
		memleft(this->trans_table[i]);
		for (int j = 0; j<128; j++)
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
		for ( int j = 0; j < 128; j++ )
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

void closureSearch(NFA nfa, bool* seen, Set* closure, int state)
{
	if(seen[state]) return;
	//printf("Computing closure for %d\n",state);
	for (int i=0; i<SIZE; i++) {
		if(Set_in(nfa->trans_table[state][0],i) && i!=state){
			closureSearch(nfa,seen,closure,i);
			Set_union(closure[state], closure[i]);	
		}
	}
	Set_insert(closure[state],state);
	//printf("Set: %d: ", state);
	//Set_print(closure[state]);
	seen[state] = true;

}

NFA
NFA_removeEpsilon(NFA nfa)
{
	//seen array for DFS
	bool* seen = (bool*)calloc(nfa->num_states,sizeof(bool));

	//First compute epsilon-closure of the nfa
	Set* closure = (Set*)malloc(nfa->num_states*sizeof(Set));
	for (int i = 0; i<nfa->num_states; i++) closure[i] = new_Set(); 

	for (int i = 0; i<nfa->num_states; i++) {
		closureSearch(nfa, seen, closure, i);
	}
	free(seen);

	//array for tracking important states
	Set important = new_Set();
	Set_insert(important, 0);
	for(int i =0; i<nfa->num_states; i++)
		for(int j = 1; j<128; j++)
			if(Set_nonEmpty(nfa->trans_table[i][j]))
				Set_union(important, nfa->trans_table[i][j]);
	Set_print(important);
	for(int i = 0; i<nfa->num_states; i++) {
		Set_print(closure[i]);
	}

	NFA ret = new_NFA(nfa->num_states, "");

	for(int i = 0; i<SIZE; i++) {
		if(Set_in(important,i)) {
			for(int j = 0; j < SIZE; j++) {
				if(Set_in(closure[i],j) && i!=j) {
					printf("transfering transitions from %d to %d",j,i);
					for(int k = 1; k<128; k++)
						Set_union(ret->trans_table[i][k], nfa->trans_table[j][k]);
					if(nfa->accept_table[j]) ret->accept_table[i] = true;
				}
			}
			for(int j = 1; j < 128; j++) {
				Set_union(ret->trans_table[i][j], nfa->trans_table[i][j]);
				if(nfa->accept_table[i]) ret->accept_table[i] = true;
			}
		}
	}
	
	//compress this NFA, get rid of useless states
	int index = 0;
	int* map = (int*)calloc(nfa->num_states,sizeof(int));
	for(int i = 0; i<nfa->num_states; i++)
		if(Set_in(important,i)){
			map[i] = index++;
		}

	NFA compressed = new_NFA(Set_size(important),"");

	for(int i = 0; i<nfa->num_states; i++){
		for(int j = 1; j<128; j++)
			for(int k = 0; k<SIZE; k++)
				if(Set_in(ret->trans_table[i][j],k))
					Set_insert(compressed->trans_table[map[i]][j],map[k]);
		if(ret->accept_table[i]) compressed->accept_table[map[i]]=true;
	}

	free_Set(important);
	free(map);
	for(int i = 0; i<nfa->num_states; i++) free_Set(closure[i]);
	free(closure);


	NFA_free(ret);
	NFA_free(nfa);

	return compressed;
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
NFA_print(NFA nfa)
{
	printf("This is an NFA that %s\n", nfa->description);
	for(int i = 0; i<nfa->num_states; i++)
	{
		printf("State %d %s:\n",i, nfa->accept_table[i] ? "(accepting)" : "");
		for(int j = 0; j<128; j++)
		{
			if(Set_nonEmpty(nfa->trans_table[i][j])) {
				if(j==0) printf("\t eps :---> ");
				else printf("\t %c :---> ",(char)j);
				Set_print(nfa->trans_table[i][j]);
			}
		}
	}

}

void
NFA_reset(NFA nfa)
{
	free_Set(nfa->cur_states);
	nfa->cur_states = new_Set();
	Set_insert(nfa->cur_states, 0);
}
