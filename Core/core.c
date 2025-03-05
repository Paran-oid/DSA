#include "core.h"

#include <stdlib.h>

void data_destroy(void *data) { free(data); }