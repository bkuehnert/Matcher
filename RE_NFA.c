#include "RE_NFA.h"
#include "NFA.h"

NFA create_Atomic(char x)
{
	NFA ret = new_NFA(2, "atomic");
	Set_insert(ret->trans_table[0][(int)x],1);
	NFA_set_accepting(ret, 1, true);
	return ret;
}

NFA create_Concat(NFA a, NFA b)
{
	//malloc out a new trans table
	int new_size = a->num_states+b->num_states;
	NFA ret = new_NFA(new_size, "");
	NFA_add_transition(ret, a->num_states-1, 0, a->num_states);
	for(int i=0; i<new_size; i++)
	{
		for(int j=0; j<128; j++)
		{
			if(i<a->num_states)
				Set_union(ret->trans_table[i][j], a->trans_table[i][j]);
			if(i>=a->num_states){
				Set_incr(b->trans_table[i-a->num_states][j], a->num_states);
				Set_union(ret->trans_table[i][j], b->trans_table[i-a->num_states][j]);
			}
		}		
	}
	NFA_set_accepting(ret, new_size-1, true);
	NFA_free(a);
	NFA_free(b);
	return ret;
}

NFA create_Union(NFA a, NFA b)
{
	int new_size = a->num_states + b->num_states + 2;
	NFA ret = new_NFA(new_size, "");
	NFA_add_transition(ret, 0, 0, 1);
	NFA_add_transition(ret, 0, 0, a->num_states+1);
	NFA_add_transition(ret, a->num_states, 0, a->num_states+b->num_states+1);
	NFA_add_transition(ret, a->num_states+b->num_states, 0, a->num_states+b->num_states+1);
	for (int i = 0; i < new_size;i++) {
		for (int j = 0; j<128; j++) {
			if(i > 0 && i < a->num_states+1){
				Set_incr(a->trans_table[i-1][j],1);
				Set_union(ret->trans_table[i][j], a->trans_table[i-1][j]);
			}
			if(i>a->num_states && i<a->num_states+b->num_states+1){
				Set_incr(b->trans_table[i-a->num_states-1][j],a->num_states+1);
				Set_union(ret->trans_table[i][j], b->trans_table[i-a->num_states-1][j]);
			}
		}
	}
	NFA_set_accepting(ret, new_size-1, true);
	NFA_free(a);
	NFA_free(b);
	return ret;
}
