#include "hash.h"
#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {

  logger_create(LOG_DATE_ALL);

  HashTable ht = hash_table_create(DATATYPE_STRING, DATATYPE_INT);

  // make it display the hash_table
  int x = 30;

  hash_table_insert(&ht, "aziz", &x);
  hash_table_insert(&ht, "damn", &x);
  void *res = hash_table_lookup(&ht, "aziz");
  printf("address of res is %p\n", res);

  logger_destroy();
  exit(EXIT_SUCCESS);
}

// TODO: CREATE TESTS