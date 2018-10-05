#include "Set.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

Set new_Set(void)
{
	Set this = (struct SET*)malloc(sizeof(struct SET));
	this->data = 0;
	return this;
}

void free_Set(Set this)
{
	free(this);
}

void Set_insert(Set this, int x)
{
	if (x<0 || x>=SIZE) {
		return;
	}
	this->data |= (1L << x);
}

bool Set_in(Set this, int x)
{
	if (x<0 || x>=SIZE) {
		return 0;
	}
	return this->data & (1L<<x);
}

void Set_union(Set this, Set other)
{
	this->data |= other->data;
}

void Set_intersection(Set this, Set other)
{
	this->data &= other->data;
}

bool Set_equals(Set this, Set other)
{
	return this->data == other->data;
}

bool Set_contains(Set big, Set small)
{
	for(int i=0; i<SIZE; i++)
		if(!Set_in(big,i) && Set_in(small, i)) return false;
	return true;
}

void Set_incr(Set set, int incr)
{
	set->data = set->data<<incr;
}

bool Set_nonEmpty(Set set)
{
	return set->data!=0L;
}

int Set_size(Set set)
{
	int count = 0;
	for(int i = 0; i<SIZE; i++) {
		if(Set_in(set,i)) count++;
	}
	return count;
}

void Set_print(Set set)
{
	printf("{");
	for(int i=0;i<SIZE; i++)
	{
		if(Set_in(set, i))
			printf("%d, ",i);
	}
	printf("}\n");
}
