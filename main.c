#include "funcs.h"
#include "logs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void) {

  init_logger(ALL);

  char str[] = "Andrew;New York;";
  char buff[100];

  sscanf(buff, "%s;%s", &str);

  destroy_logger();
  exit(EXIT_SUCCESS);
}

// TODO: CREATE TEST