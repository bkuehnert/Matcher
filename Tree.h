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

struct TREE
{
	struct TREE_NODE* root;
};

typedef struct TREE_NODE* tr_Node;
typedef struct TREE* Tree;

extern tr_Node new_tr_Node(bool terminal, char c);

#endif
