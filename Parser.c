#include "Parser.h"

#include <string.h>
#include <stdlib.h>

bool match(char** s, const char *token)
{
	if(strncmp(*s, token, strlen(token)) == 0) {
		*s+=1;
		return true;
	}
	return false;
}

bool Regex(char** s, tr_Node link, bool child)
{
	char* original = *s;
	tr_Node ret = new_tr_Node(false, ' ');
	if(ParenRegex(s, link, true) || Atom(s, link, true) || Union(s, link, true) || Concat(s, link, true) || Closure(s, link, true)){
		if(child) link->left = ret;
		else link->right = ret;
		return true;
	}
	*s = original;
	return false;		
}

bool Atom (char** s, tr_Node link, bool child)
{
	char* original = *s;
	for(int i = 0; i<128; i++)
	{
		if((i>47 && i<58) || (i>64 && i<91) || (i>96 && i<123)) {
			if(match(s, (char*)&i)) {
				if(child) link->left = new_tr_Node(true, i);
				else link->right = new_tr_Node(true, i);
				return true;
			} 
		}
	}
	*s = original;
	return false;
}

bool Union(char** s, tr_Node link, bool child)
{
	char* original = *s;
	tr_Node ret = new_tr_Node(false, ' ');
	if(Regex(s, ret, true) & unionSign(s, ret->left, false) & Regex(s, ret->left->right, false)) {
		if(child) link->left = ret;
		else link->right = ret;
		return true;
	}
	*s = original;
	return false;
}

bool Concat(char** s, tr_Node link, bool child)
{
	char* original = *s;
	tr_Node ret = new_tr_Node(false, ' ');
	if(Regex(s, ret, true) & Regex(s, ret->left, false)) {
		if(child) link-> left = ret;
		else link->right = ret;
		return true;
	}
	*s = original;
	return false;
}

bool Closure(char** s, tr_Node link, bool child)
{
	char* original = *s;
	tr_Node ret = new_tr_Node(false, ' ');
	if(Regex(s, ret, true) & closureSign(s, ret->left, false)) {
		if(child) link-> left = ret;
		else link->right = ret;
		return true;
	}
	*s = original;
	return false;
}

bool LeftParen(char** s, tr_Node parent, bool child)
{
	char* original = *s;
	if(match(s, "(")) {
		parent->left = new_tr_Node(true, '(');
		return true;
	}
	*s = original;
	return false;
}

bool RightParen(char** s, tr_Node parent, bool child)
{
	char* original = *s;
	if(match(s, ")")) {
		parent->right = new_tr_Node(true, ')');
		return true;
	}
	*s = original;
	return false;
}

bool ParenRegex(char** s, tr_Node link, bool child)
{
	char* original = *s;
	tr_Node ret = new_tr_Node(false, ' ');
	if(LeftParen(s, ret, true) & Regex(s, ret->left, false) & RightParen(s, ret->left->right, false)) {
		if(child) link->left = ret;
		else link->right = ret;	
		return true;
	}
	*s = original;
	return false;
}

bool unionSign(char** s, tr_Node link, bool child)
{
	char* original = *s;
	tr_Node ret = new_tr_Node(true, ' ');
	if(match(s, "|")) {
		if(child) link->left = ret;
		else link->right = ret;
		return true;
	}
	*s = original;
	return false;
}

bool closureSign(char** s, tr_Node link, bool child)
{
	char* original = *s;
	tr_Node ret = new_tr_Node(true, ' ');
	if(match(s, "*")) {
		if(child) link->left = ret;
		else link->right = ret;
		return true;
	}
	*s = original;
	return false;
}
