#include "funcs.h"
#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {

  logger_init(ALL);

  logger_destroy();
  exit(EXIT_SUCCESS);
}

// TODO: CREATE TEST