#include "NFA.h"
#include "RE_NFA.h"
#include "Tree.h"
#include "Eval.h"
#include "Parser.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void test_nfa(NFA nfa)
{
	printf("This is a NFA that %s\n", nfa->description);
	bool cont = true;
	while(cont)
	{
		printf("Enter input (type \"quit\" to quit):");

		char input[250];
		fgets(input, 250, stdin);
		char* ptr = input;
		while(*ptr != '\0'){
			if(*ptr == '\n') *ptr = '\0';
			ptr+=1;
	}
		if(!strcmp(input, "quit")){
			cont = false;
			break;
		}
		else{
			printf("Input \"%s\" resulted in: %s\n", input, NFA_execute(nfa, input) ? "true" : "false");
			NFA_reset(nfa);
		}
	}
	printf("\n");
}

int main(void)
{
	/*
	NFA atomA = create_Atomic('a');
	NFA atomB = create_Atomic('b');
	NFA concatAB = create_Concat(atomA, atomB);
	NFA atomC = create_Atomic('c');
	NFA closeC = create_Closure(atomC);

	NFA this = create_Union(concatAB, closeC);

	NFA final = NFA_removeEpsilon(this);
	final->description="matches ab|c*";

	test_nfa(final);

	NFA_free(final);

	NFA this = create_Union(create_Concat(create_Closure(create_Atomic('1')),create_Atomic('0')),create_Closure(create_Concat(create_Concat(create_Atomic('1'),create_Closure(create_Atomic('1'))),create_Atomic('0'))));

	NFA final = NFA_removeEpsilon(this);

	test_nfa(final);

	NFA_free(final);
	*/

	/*
	char input[1000];
	char* copy;

	while(fgets(input, 999, stdin)!=NULL) {
		copy = input;
		if(R(&copy))	
			printf("this is a regex\n");
		else
			printf("this is not a regex\n");
	}*/

	char* input ="(a)*";
	Node out = wrap(&input);
	if(out != NULL)	{
		printf("this is a regex\n");
		tree_print(out);
		NFA eNFA = build_R(out);
		NFA final = NFA_removeEpsilon(eNFA);
		NFA_print(final);
		test_nfa(final);
	}
	else
		printf("this is not a regex\n");


	return 0;
}
