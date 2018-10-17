#include "Tree.h"

#include <stdio.h>
#include <stdlib.h>

Node new_Node(bool terminal, char c)
{
	Node ret = (struct TREE_NODE*)malloc(sizeof(struct TREE_NODE));
	ret->terminal = terminal;
	ret->children = (struct TREE_NODE**)calloc(2,sizeof(struct TREE_NODE*));
	ret->c = c;
	ret->num_children=0;
	return ret;
}

void tree_addNewChild(Node parent, bool terminal, char c)
{
	Node ret = new_Node(terminal, c);
	parent->children[parent->num_children] = ret;
}

void tree_addChild(Node parent, Node child)
{
	parent->children[parent->num_children] = child;
}


