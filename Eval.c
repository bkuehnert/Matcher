
#include "Eval.h"

NFA buildNFA(Node root) {
	
}

NFA build_R(Node root) {
	if(root->children[1]->children[0]->c != 'e') {
		printf("building UNION\n");
		return create_Union(build_A(root->children[0]), build_R(root->children[1]->children[0]));
	}
	else {
		return build_A(root->children[0]);
	}
}

NFA build_A(Node root) {
	if(root->children[1]->children[0]->c != 'e') {
		printf("building CONCAT\n");
		return create_Concat(build_C(root->children[0]),build_A(root->children[1]->children[0]));
	}
	else {
		return build_C(root->children[0]);
	}
}



NFA build_C(Node root) {
	if(root->children[0]->c == 'R') {
		return build_R(root->children[0]);
	}
	printf("building atomic of %c\n",root->children[0]->c);
	return create_Atomic(root->children[0]->c);
}







