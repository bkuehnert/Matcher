#include "Parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Grammar spec
 * <R> -> <T><S>
 * <T> -> <F><T>
 * <S> -> '|'<R><S>|e
 * <F> -> <B><C>
 * <C> -> '*'<C>|e
 * <B> -> char | (<R>)
 *
 * <R> -> <A><B>
 * <B> -> '|'<R> | e
 * <A> -> <C><D>
 * <D> -> <A> | e
 * <C> -> (<R>) | char
 */

bool match(char** s, char token)
{
	if(*s[0]==token) {
		printf("parsed token %c \n",*s[0]);
		*s+=1;
		return true;
	}
	return false;
}

//just upper and lowercase letters for now
bool isInAlphabet(char s)
{
	if((s >64 && s<91 )|| (s>96 && s<123)) return 1;
	return 0;

}

char lookahead(char** s)
{
	//printf("%c\n",*s[0]);
	if(*s[0] == '\0') return 0;
	return *s[0];
}

bool wrap(char* s)
{
	if(R(s)) {
		if(s[0] == '\0') return true;
		printf("token %c is dangling\n",s[0]);
		return false;
	}
	return false;
}

Node R(char* input)
{
	Node n1 = A(input);
	Node n2 = B(input);
	if(n1 == NULL || n2 == NULL) return NULL;

	Node out = new_Node(false, 'A');
	tree_addChild(out, n1);
	tree_addChild(out, n2);

	return out;
}

Node A(char* input)
{
	Node n1 = A(input);
	Node n2 = B(input);
	if(n1 == NULL || n2 == NULL) return NULL;

	Node out = new_Node(false, 'A');
	tree_addChild(out, n1);
	tree_addChild(out, n2);
}

Node B(char* input)
{
	if(lookahead(input) == '|') {
		Node n1 = R(input);
		Node out = new_Node(false, 'B');
		tree_addChild(out, n1);
		return out;
	}
	Node eps = new_Node(true, 'e');
	Node out = new_Node(false, 'B');
	tree_addChild(out,eps);
	return out;
}

