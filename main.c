#include "funcs.h"
#include "logs.h"
#include "lstack.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  init_logger(ALL);

  LStack *mystack = init_lstack(3);
  print_lstack(mystack);

  destroy_lstack(mystack);
  destroy_logger();

  exit(EXIT_SUCCESS);
}