#include "array.h"
#include "funcs.h"
#include "logs.h"
#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {

  logger_create(LOG_DATE_ALL);

  logger_destroy();
  exit(EXIT_SUCCESS);
}

// TODO: CREATE TESTS