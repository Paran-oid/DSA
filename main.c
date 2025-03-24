#include "pair.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_int_pair()
{
    Pair p;
    int key = 42;
    int val = 99;

    pair_create(&p, NULL, sizeof(int), sizeof(int));
    assert(pair_set(&p, &key, &val) == 0);

    assert(*(int*)pair_key(&p) == 42);
    assert(*(int*)pair_val(&p) == 99);

    pair_destroy(&p);
    printf("✅ test_int_pair passed!\n");
}

void test_double_pair()
{
    Pair p;
    double key = 3.14;
    double val = 2.71;

    pair_create(&p, NULL, sizeof(double), sizeof(double));
    assert(pair_set(&p, &key, &val) == 0);

    assert(*(double*)pair_key(&p) == 3.14);
    assert(*(double*)pair_val(&p) == 2.71);

    pair_destroy(&p);
    printf("✅ test_double_pair passed!\n");
}

void test_string_pair()
{
    Pair p;
    char key[] = "hello";
    char val[] = "world";

    pair_create(&p, NULL, strlen(key) + 1, strlen(val) + 1);
    assert(pair_set(&p, key, val) == 0);

    assert(strcmp((char*)pair_key(&p), "hello") == 0);
    assert(strcmp((char*)pair_val(&p), "world") == 0);

    pair_destroy(&p);
    printf("✅ test_string_pair passed!\n");
}

void test_reassignment()
{
    Pair p;
    int key1 = 10, key2 = 20;
    int val1 = 100, val2 = 200;

    pair_create(&p, NULL, sizeof(int), sizeof(int));

    assert(pair_set(&p, &key1, &val1) == 0);
    assert(*(int*)pair_key(&p) == 10);
    assert(*(int*)pair_val(&p) == 100);

    assert(pair_set(&p, &key2, &val2) == 0); // Reassign new values
    assert(*(int*)pair_key(&p) == 20);
    assert(*(int*)pair_val(&p) == 200);

    pair_destroy(&p);
    printf("✅ test_reassignment passed!\n");
}

void test_null_handling()
{
    Pair p;
    pair_create(&p, NULL, sizeof(int), sizeof(int));

    assert(pair_set(&p, NULL, NULL) == -1); // Should fail safely

    pair_destroy(&p);
    printf("✅ test_null_handling passed!\n");
}

int main()
{
    test_int_pair();
    test_double_pair();
    test_string_pair();
    test_reassignment();
    test_null_handling();

    printf("\nAll tests passed successfully! 🎉\n");
    return 0;
}
