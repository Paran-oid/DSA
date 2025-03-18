#include "bistree.h"
#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

void destroy(void* data)
{
    free(data); // Free dynamically allocated memory
}

int match(const void* key1, const void* key2)
{
    return (*(int*)key1 - *(int*)key2);
}

// Helper function to insert an integer into the AVL tree
void insert_test(AvlTree* tree, int value)
{
    int* data = malloc(sizeof(int));
    *data = value;
    if (bistree_insert(tree, (void*)data) == 0) {
        printf("Inserted: %d\n", value);
    } else {
        printf("Failed to insert: %d\n", value);
        free(data); // Prevent memory leak
    }
}

// Helper function to look up an integer
void lookup_test(AvlTree* tree, int value)
{
    int* data = &value;

    if (bistree_lookup(tree, (void**)&data) == 0) {
        printf("Found: %d\n", *data);
    } else {
        printf("Not found: %d\n", value);
    }
}

// Helper function to remove an integer
void remove_test(AvlTree* tree, int value)
{
    if (bistree_remove(tree, &value) == 0) {
        printf("Removed: %d\n", value);
    } else {
        printf("Failed to remove: %d\n", value);
    }
}

int main()
{
    AvlTree tree;

    // Initialize the AVL tree
    bistree_create(&tree, destroy, match);

    // Insert test values
    insert_test(&tree, 50);
    insert_test(&tree, 30);
    insert_test(&tree, 70);
    insert_test(&tree, 20);
    insert_test(&tree, 40);
    insert_test(&tree, 60);
    insert_test(&tree, 80);

    printf("\nTree size: %d\n\n", bistree_size(&tree));

    // Look up values
    lookup_test(&tree, 30);
    lookup_test(&tree, 100); // Should not be found

    // Remove values
    remove_test(&tree, 30);
    remove_test(&tree, 100); // Should fail

    printf("\nTree size after deletion: %d\n", bistree_size(&tree));

    // Destroy the tree
    bistree_destroy(&tree);

    return 0;
}
