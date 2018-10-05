#include "Parser.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * Grammar spec
 * <R> -> <T><S>
 * <T> -> <F><T>
 * <S> -> '|'<R>|e
 * <F> -> <B><C>
 * <C> -> '*'<C>|e
 * <B> -> char | (<R>)
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

bool wrap(char** s)
{
	if(R(s)) {
		if(*s[0] == '\0') return true;
		printf("token %c is dangling\n",*s[0]);
		return false;
	}
	return false;
}

bool R(char** s)
{
	char* original = *s;
	if(!T(s)){
		*s = original;
		return 0;	
	}
	if(!S(s)) {
		*s = original;
		return 0;
	}
	return 1;
}

bool T(char** s)
{
	char* original = *s;
	if(lookahead(s) == '(' || isInAlphabet(lookahead(s))) {
		if(!F(s)) {
			*s = original;
			return 0;
		}
		if(!T(s)) {
			*s = original;
			return 0;
		} 
		printf("<T>--><F><T> matched\n");
		return 1;
	}
	else {
		return 1;
	}
	return 0;
}

bool S(char** s)
{
	char* original = *s;
	if(lookahead(s) == '|') {
		if(!match(s, '|')) {
			*s = original;
			return 0;
		}
		if(!R(s)) {
			*s = original;
			return 0;
		}
	}
	else {
		return 1;
	}
	return 0;
}

bool F(char** s)
{
	char* original = *s;
	if(!B(s)) {
		*s = original;
		return 0;
	}
	if(!C(s)) {
		*s = original;
		return 0;
	}
	printf("<F>--><B><C> matched\n");
	return 1;
}

bool C(char** s)
{
	char* original = *s;
	//printf("*s[0] = %c\n",*s[0]);
	//printf("lookahead(s) = %c\n", lookahead(s));
	//printf("lookeahed(s) == '*': %d\n", lookahead(s) == '*');
	if(lookahead(s) == '*') {
		if(!match(s, '*')) {
			*s = original;
			return 0;
		}
		if(!C(s)) {
			*s = original;
			return 0;
		}
		printf("<C>-->*<C> matched\n");
		return 1;
	}
	else {
		printf("<C>-->e matched\n");
		return 1;
	}
	return 0;
}

bool B(char** s)
{
	char* original = *s;
	if(isInAlphabet(lookahead(s))) {
		if(!match(s, **s)) {
			*s = original;
			return 0;
		}
		printf("<B>-->char matched\n");
		return 1;
	}
	if(lookahead(s)=='(') {
		if(!match(s, '(')) {
			*s = original;
			return 0;
		}
		if(!R(s)) {
			*s = original;
			return 0;
		}
		if(!match(s,')')) {
			*s = original;
			return 0;
		}
		printf("<B>-->(<R>) matched\n");
		return 1;
	}
	return 0;
}

