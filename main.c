#include "hash.h"
#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {

  logger_create(LOG_DATE_ALL);

  HashTable ht = hash_table_create(DATATYPE_CHAR, DATATYPE_INT);

  // make it display the hash_table
  hash_table_insert(&ht, "aziz", 20);
  hash_table_insert(&ht, "damn", 50);
  hash_table_delete

  logger_destroy();
  exit(EXIT_SUCCESS);
}

// TODO: CREATE TESTS