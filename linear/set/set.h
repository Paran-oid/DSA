#ifndef SET_H
#define SET_H

#include <list.h>

typedef List Set;

#define set_create list_create
#define set_destroy list_destroy

int set_insert(Set* set, const void* data);
int set_rem(Set* set, void** data);

int set_union(Set* set_res, const Set* set1, const Set* set2);
int set_intersection(Set* set_res, const Set* set1, const Set* set2);
int set_difference(Set* set_res, const Set* set_comp_from,
                   const Set* set_comp_to);
int set_is_member(const Set* set_dest, const void* item);
int set_is_subset(const Set* set_comp_from, const Set* set_comp_to);
int set_is_equal(const Set* set1, const Set* set2);

#define set_size(set) ((set)->size)

#endif