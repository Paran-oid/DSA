#include "funcs.h"
#include "logs.h"
#include "matrix.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {

  init_logger(ALL);

  destroy_logger();
  exit(EXIT_SUCCESS);
}