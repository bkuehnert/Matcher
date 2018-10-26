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

int main(int argc, char *argv[])
{
	/*
	char* input ="(a|b)*";
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

	*/
	if(argc != 3) {
		printf("2 arguments required.\n");
		abort();
	}
	
	Node out = wrap(&argv[1]);
	if(out == NULL) {
		printf("Invalid regex, try again\n");
		abort();
	}

	NFA nfa = NFA_removeEpsilon(build_R(out));

	FILE* fp;
	int i = 0;
	char buffer[128];

	fp = fopen(argv[2],"r");
	if(fp == NULL) {
		printf("Unknown file. \n");
		abort();
	}

	while(fgets(buffer, 128, fp) != NULL) {
		char copy[128];
		strcpy(copy, buffer);
		strtok(copy, "\n");
		i++;
		if(NFA_execute(nfa,copy)) {
			printf("%3d: %s\n",i,copy);
		}
		NFA_reset(nfa);
	}

	fclose(fp);	
	return 0;
}
