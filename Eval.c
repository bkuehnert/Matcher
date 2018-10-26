
#include "Eval.h"

NFA build_R(Node root) {
	if(root->children[1]->children[0]->c != 'e') {
		return create_Union(build_A(root->children[0]), build_R(root->children[1]->children[0]));
	}
	else {
		return build_A(root->children[0]);
	}
}

NFA build_A(Node root) {
	if(root->children[1]->children[0]->c != 'e') {
		return create_Concat(build_C(root->children[0]),build_A(root->children[1]->children[0]));
	}
	else {
		return build_C(root->children[0]);
	}
}



NFA build_C(Node root) {
	if(root->children[0]->c == 'R') {
//		return build_R(root->children[0]);
		if(root->children[1]->children[0]->c == '*') {
			return create_Closure(build_R(root->children[0]));
		}
		return build_R(root->children[0]);
	}
	if(root->children[1]->children[0]->c == 'e')
		return create_Atomic(root->children[0]->c);
	return create_Closure(create_Atomic(root->children[0]->c));
}
