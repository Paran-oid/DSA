#pragma once

#include "funcs.h"

#include <pthread.h>
#include <stdio.h>

typedef struct Logger {
  FILE *file;
  pthread_mutex_t logMutex;
} Logger;

typedef enum LogType { logInformation, logWarning, logDanger } LogType;
typedef enum LogDate { SESSION, ALL } LogDate;

static Logger logger;

#define INFO(message) (log_message(logInformation, __FILE__, __LINE__, message))
#define WARN(message) (log_message(logWarning, __FILE__, __LINE__, message))
#define DANGER(message) (log_message(logDanger, __FILE__, __LINE__, message))

void init_logger(LogDate date);
void log_message(LogType type, char *file, i32 line, char *mess);
void destroy_logger(void);
