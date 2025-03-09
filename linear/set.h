#ifndef SET_H
#define SET_H

#include <list.h>

typedef List Set;

#define set_create list_create
#define set_destroy list_destroy

int set_insert(Set* set, const void* data);
int set_rem(Set* set, void** data);

int set_union(Set* seti, const Set* set1, const Set* set2);
int set_intersection(Set* seti, const Set* set1, const Set* set2);
int set_difference(Set* seti, const Set* set1, const Set* set2);
int set_is_member(Set* set_dest, Set* set_src);
int set_is_subset(Set* set_dest, Set* set_src);
int set_is_equal(Set* set1, Set* set2);

#define set_size(set) ((set)->size)

#endif