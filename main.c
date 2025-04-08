#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Destroy function for keys/values if needed

int main()
{
    Dictionary dict;
    dict_create(&dict, free);

    // Set key-value pairs
    dict_set(&dict, "name", "Aziz");
    dict_set(&dict, "language", "C");
    dict_set(&dict, "editor", "vim");

    // Get values
    char* val;
    if (dict_get_value(&dict, "name", &val) == 0)
        printf("name: %s\n", val);
    else
        printf("Key 'name' not found\n");

    if (dict_get_value(&dict, "language", &val) == 0)
        printf("language: %s\n", val);

    // Remove key
    if (dict_remove_key(&dict, "editor", &val) == 0) {
        printf("Removed editor: %s\n", val);
        free(val); // Because dict_remove_key returns ownership
    }

    // Try to get a removed key
    if (dict_get_value(&dict, "editor", &val) != 0)
        printf("Key 'editor' not found (as expected)\n");

    // Clean up
    dict_destroy(&dict);
    return 0;
}
