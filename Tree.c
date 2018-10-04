#include "Tree.h"

#include <stdio.h>
#include <stdlib.h>

Node new_Node(bool terminal, char c)
{
	Node ret = (struct TREE_NODE*)malloc(sizeof(struct TREE_NODE));
	ret->terminal = terminal;
	ret->c = c;
	return ret;
}

void Node_addChild(Node parent, bool terminal, char c)
{
	Node ret = new_Node(terminal, c);
	if(parent->left == NULL) parent->left = ret;
	Node ptr = parent;
	while(ptr->right != NULL) ptr = ptr->right;
	ptr->right = ret;
}


