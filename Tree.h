/*
 * Author: Ben Kuehnert
 *
 * Tree datastructure
 */

#ifndef _tree_h
#define _tree_h

#include <stdbool.h>

struct TREE_NODE
{
	struct TREE_NODE** children;
	int num_children;
	bool terminal;
	char c;
};

typedef struct TREE_NODE* Node;

extern Node new_Node(bool terminal, char c);
extern void Node_addNewChild(Node parent, bool terminal, char c);

#endif
