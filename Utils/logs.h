#pragma once

#include "models.h"

#define INFO(message)                                                          \
  (logger_message(logInformation, __FILE__, __LINE__, message))
#define WARN(message) (logger_message(logWarning, __FILE__, __LINE__, message))
#define DANGER(message) (logger_message(logDanger, __FILE__, __LINE__, message))

void logger_create(LogDateType date);
void logger_message(LogType type, const char *file, int line, const char *mess);
void logger_destroy();
