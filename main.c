#include "funcs.h"
#include "logs.h"
#include "queue.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {

  // FIXME
  init_logger(ALL);

  Queue myqueue = init_queue();
  enqeue_queue(&myqueue, 5);
  peek_queue(&myqueue);
  print_queue(&myqueue);

  destroy_logger();

  exit(EXIT_SUCCESS);
}