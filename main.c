#include "set.h"
#include <stdio.h>
#include <stdlib.h>

void print_set(const Set* set)
{
    ListNode* node = list_head(set);
    printf("{ ");
    while (node) {
        printf("%d ", *(int*)list_data(node));
        node = list_next(node);
    }
    printf("}\n");
}

int match_int(const void* key1, const void* key2)
{
    return (*(int*)key1 - *(int*)key2);
}

void destroy_int(void* data)
{
    free(data);
}

int main()
{
    Set set1, set2, result_set;
    set_create(&set1, match_int, destroy_int);
    set_create(&set2, match_int, destroy_int);
    set_create(&result_set, match_int, destroy_int);

    // Insert elements into set1
    int* value;
    for (int i = 1; i <= 5; i++) {
        value = malloc(sizeof(int));
        *value = i;
        set_insert(&set1, value);
    }

    // Insert elements into set2
    for (int i = 3; i <= 7; i++) {
        value = malloc(sizeof(int));
        *value = i;
        set_insert(&set2, value);
    }

    printf("Set 1: ");
    print_set(&set1);

    printf("Set 2: ");
    print_set(&set2);

    // Test union
    set_union(&result_set, &set1, &set2);
    printf("Union: ");
    print_set(&result_set);
    set_destroy(&result_set);

    // Test intersection
    set_intersection(&result_set, &set1, &set2);
    printf("Intersection: ");
    print_set(&result_set);
    set_destroy(&result_set);

    // Test difference (set1 - set2)
    set_difference(&result_set, &set1, &set2);
    printf("Difference (Set1 - Set2): ");
    print_set(&result_set);
    set_destroy(&result_set);

    // Test membership
    int key = 3;
    printf("Is %d in Set1? %s\n", key, set_is_member(&set1, &key) ? "Yes" : "No");

    key = 10;
    printf("Is %d in Set1? %s\n", key, set_is_member(&set1, &key) ? "Yes" : "No");

    // Test subset
    printf("Is Set2 a subset of Set1? %s\n", set_is_subset(&set2, &set1) ? "Yes" : "No");

    // Test equality
    printf("Are Set1 and Set2 equal? %s\n", set_is_equal(&set1, &set2) ? "Yes" : "No");

    // Clean up
    set_destroy(&set1);
    set_destroy(&set2);

    return 0;
}
