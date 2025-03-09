#include "clist.h"
#include <stdio.h>
#include <stdlib.h>

void destroy_data(void* data)
{
    free(data);
}

int match_data(const void* key1, const void* key2)
{
    return (*(int*)key1 == *(int*)key2);
}

void print_list(CList* clist)
{
    CListNode* node = clist_head(clist);
    if (!node) {
        printf("List is empty.\n");
        return;
    }

    for (size_t i = 0; i < clist_size(clist); i++) {
        printf("%d -> ", *(int*)clist_data(node));
        node = clist_next(node);
    }
    printf("(head)\n");
}

int main()
{
    CList list;
    clist_create(&list, match_data, destroy_data);

    int* value;
    CListNode* curr = list.head;
    for (int i = 1; i <= 5; i++) {
        value = malloc(sizeof(int));
        *value = i;
        clist_ins_next(&list, (i == 1) ? NULL : curr, value);
        if (i == 1) {
            curr = list.head;
        }
        if (i != 1) {
            curr = curr->next;
        }
    }

    printf("Initial list:\n");
    print_list(&list); // Expected output: 1 -> 2 -> 3 -> 4 -> 5 -> (head)

    void* removed_data;
    clist_rem_next(&list, list.head, &removed_data);
    printf("After removing one element:\n");
    print_list(&list); // Expected output: 1 -> 3 -> 4 -> 5 -> (head)
    free(removed_data);

    clist_destroy(&list);
    printf("List destroyed.\n"); // Expected output: List destroyed.
    return 0;
}
