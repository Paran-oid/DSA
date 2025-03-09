#include "set.h"

int set_insert(Set* set, const void* data)
{
    if (set_is_member(set, data)) {
        return 1;
    }
    return list_ins_next(set, list_tail(set), data);
}
int set_rem(Set* set, void** data)
{

    return list_rem_next(set, data);
}

int set_union(Set* seti, const Set* set1, const Set* set2);
int set_intersection(Set* seti, const Set* set1, const Set* set2);
int set_difference(Set* seti, const Set* set1, const Set* set2);
int set_is_member(Set* set_dest, const void* set_src);
int set_is_subset(Set* set_dest, Set* set_src);
int set_is_equal(Set* set1, Set* set2);