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
    ListNode *prev = NULL, *curr;

    for (curr = list_head(set); curr != NULL; curr = list_next(curr)) {
        if (set->match(curr->data, data) == 0) {
            break;
        }
        prev = curr;
    }

    if (curr == NULL) {
        return -1;
    }

    return list_rem_next(set, prev, data);
}

int set_union(Set* seti, const Set* set1, const Set* set2)
{
    ListNode* curr;
    void* data;

    set_create(seti, set1->match, set1->destroy);

    for (curr = list_head(set1); curr != NULL; curr = list_next(curr)) {
        data = list_data(curr);
        if (list_ins_next(seti, list_tail(seti), data) != 0) {
            set_destroy(seti);
            return -1;
        }
    }

    for (curr = list_head(set2); curr != NULL; curr = list_next(curr)) {
        data = list_data(curr);
        if (set_is_member(set1, data)) {
            continue;
        } else {
            if (list_ins_next(seti, list_tail(seti), data) != 0) {
                set_destroy(seti);
                return -1;
            }
        }
    }

    return 0;
}

int set_intersection(Set* seti, const Set* set1, const Set* set2)
{
    ListNode* curr;
    void* data;

    set_create(seti, set1->match, set1->destroy);

    for (curr = list_head(set1); curr != NULL; curr = list_next(curr)) {
        data = list_data(curr);
        if (set_is_member(set2, data) == 0) {
            continue;
        } else {
            if (list_ins_next(seti, list_head(seti), data) != 0) {
                set_destroy(seti);
                return -1;
            }
        }
    }

    return 0;
}

int set_difference(Set* seti, const Set* set_comp_from, const Set* set_comp_to)
{
    set_create(seti, set_comp_from->match, set_comp_to->destroy);

    ListNode* curr;
    void* data;

    for (curr = list_head(set_comp_from); curr != NULL; curr = list_next(curr)) {
        data = list_data(curr);
        if (set_is_member(set_comp_to, data) != 0) {
            continue;
        } else {
            if (list_ins_next(seti, list_tail(seti), data) != 0) {
                list_destroy(seti);
                return -1;
            }
        }
    }

    return 0;
}

int set_is_member(const Set* set_dest, const void* item)
{
    if (list_size(set_dest) == 0) {
        return 0;
    }

    ListNode* curr;
    for (curr = list_head(set_dest); curr != NULL; curr = list_next(curr)) {
        if (set_dest->match(item, list_data(curr)) == 0) {
            return 1;
        }
    }

    return 0;
}

int set_is_subset(const Set* set_comp_from, const Set* set_comp_to)
{
    if (list_size(set_comp_from) > list_size(set_comp_to)) {
        return 0;
    }

    ListNode* curr;
    void* data;

    for (curr = list_head(set_comp_from); curr != NULL; curr = list_next(curr)) {
        data = list_data(curr);
        if (set_is_member(set_comp_to, data) != 1) {
            return 0;
        }
    }

    return 1;
}

int set_is_equal(const Set* set1, const Set* set2)
{
    if (list_size(set1) != list_size(set2)) {
        return 0;
    }

    ListNode* curr;
    void* data;

    for (curr = list_head(set1); curr != NULL; curr = list_next(curr)) {
        data = list_data(curr);
        if (set_is_member(set2, data) != 1) {
            return 0;
        }
    }

    return 1;
}