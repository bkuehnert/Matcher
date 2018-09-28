/*
 * Author: Ben Kuehnert
 *
 * Header for an  IntSet that can store ints 0-128
 */

#ifndef _set_h
#define _set_h

#define SIZE (sizeof(unsigned long int)*8)
#include <stdbool.h>

struct SET 
{
	unsigned long int data;
};

typedef struct SET* Set;

extern Set new_Set(void);
extern void free_Set(Set set);
extern void Set_insert(Set set, int x);
extern bool Set_in(Set set, int x);
extern void Set_remove(Set set, int x);
extern void Set_union(Set set, Set other);
extern bool Set_equals(Set set, Set other);

#endif
