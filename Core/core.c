#include "core.h"

#include <stdlib.h>
#include <string.h>

void data_destroy(void *data) { free(data); }