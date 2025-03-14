#include "btree.h"
#include <stdio.h>
#include <stdlib.h>

// Simple function to destroy a node's data
void destroy(void* data)
{
    free(data);
}

// Simple function to compare integers
int match(const void* key1, const void* key2)
{
    return (*(int*)key1 == *(int*)key2);
}

// Utility function to create a new integer dynamically
int* create_int(int value)
{
    int* ptr = malloc(sizeof(int));
    if (!ptr) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    *ptr = value;
    return ptr;
}

// Recursive function to print tree structure
void print_tree(BiTreeNode* node, int depth)
{
    if (node == NULL) {
        return;
    }
    print_tree(node->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("   ");
    }
    printf("%d\n", *(int*)node->data);

    print_tree(node->left, depth + 1);
}

int main()
{
    BiTree bt1, bt2, merged;

    // Initialize trees
    bitree_create(&bt1, destroy, match);
    bitree_create(&bt2, destroy, match);

    printf("Testing binary tree operations...\n");

    // Insert root node in bt1
    int* root1 = create_int(10);
    bitree_ins_left(&bt1, NULL, root1);

    // Insert children
    bitree_ins_left(&bt1, bt1.root, create_int(5));
    bitree_ins_right(&bt1, bt1.root, create_int(15));

    // Insert deeper levels
    bitree_ins_left(&bt1, bt1.root->left, create_int(3));
    bitree_ins_right(&bt1, bt1.root->left, create_int(7));
    bitree_ins_left(&bt1, bt1.root->right, create_int(13));
    bitree_ins_right(&bt1, bt1.root->right, create_int(20));

    printf("Binary Tree 1:\n");
    print_tree(bt1.root, 0);

    // Insert into second tree
    int* root2 = create_int(50);
    bitree_ins_left(&bt2, NULL, root2);

    bitree_ins_left(&bt2, bt2.root, create_int(30));
    bitree_ins_right(&bt2, bt2.root, create_int(70));

    printf("\nBinary Tree 2:\n");
    print_tree(bt2.root, 0);

    // Merge trees
    int* merge_root = create_int(100);
    if (bitree_merge(&bt1, &bt2, &merged, merge_root) == 0) {
        printf("\nMerged Binary Tree:\n");
        print_tree(merged.root, 0);
    } else {
        printf("\nTree merge failed!\n");
    }

    // Remove a subtree
    printf("\nRemoving left subtree of merged tree...\n");
    bitree_rem_left(&merged, merged.root);

    printf("\nTree after removal:\n");
    print_tree(merged.root, 0);

    // Destroy everything
    printf("\nDestroying trees...\n");
    bitree_destroy(&merged);

    printf("All tests passed!\n");

    return 0;
}
