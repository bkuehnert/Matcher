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
	struct TREE_NODE* left;
	struct TREE_NODE* right;
	bool terminal;
	char c;
};

typedef struct TREE_NODE* Node;

extern Node new_Node(bool terminal, char c);
extern void Node_addChild(Node parent, bool terminal, char c);

#endif
