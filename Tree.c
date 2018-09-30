#include "Tree.h"

#include <stdio.h>
#include <stdlib.h>

tr_Node new_tr_Node(bool terminal, char c)
{
	tr_Node ret = (struct TREE_NODE*)malloc(sizeof(struct TREE_NODE));
	ret->terminal = terminal;
	ret->c = c;
	return ret;
}
