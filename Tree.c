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
	parent->children[parent->num_children++] = ret;
}

void tree_addChild(Node parent, Node child)
{
	parent->children[parent->num_children++] = child;
}


void tree_print_level(Node parent, int n)
{
	if(parent == NULL) return;

	for(int i =0; i<n;i++) printf(" ");
	printf("%c\n",parent->c);
	for(int i = 0; i < parent->num_children; i++)
		tree_print_level(parent->children[i], n+1);
}

void tree_print(Node parent)
{
	tree_print_level(parent, 0);
}
