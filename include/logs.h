#pragma once

#include "funcs.h"

#include <pthread.h>
#include <stdio.h>

typedef struct logger {
  FILE *file;
  pthread_mutex_t logMutex;
} logger_t;

enum logtype { INFORMATION, WARNING, DANGER };
enum logdate { SESSION, ALL };

#define INFO(message)                                                          \
  (logger_message(logInformation, __FILE__, __LINE__, message))
#define WARN(message) (logger_message(logWarning, __FILE__, __LINE__, message))
#define DANGER(message) (logger_message(logDanger, __FILE__, __LINE__, message))

void logger_init(enum logdate date);
void logger_message(enum logtype type, const char *file, i32 line,
                    const char *mess);
void logger_destroy();
