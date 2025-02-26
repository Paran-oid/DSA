#include "logs.h"
#include "funcs.h"
#include "models.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include <pthread.h>
#include <unistd.h>

static Logger logger;

void logger_create(LogDateType date) {
  time_t t;
  time(&t);
  char dateBuf[255];
  strftime(dateBuf, sizeof(dateBuf), "%a %b %d %H:%M:%S %Y", localtime(&t));

  char *type;
  char logPath[1000];

  if (date == LOG_DATE_ALL) {
    snprintf(logPath, sizeof(logPath), "../logs/all-logs.txt");
    type = "a";
  } else if (date == LOG_DATE_SESSION) {
    snprintf(logPath, sizeof(logPath), "../logs/session/[%s]-logs.txt",
             dateBuf);
  }
  DIR *d;
  struct dirent *dir;
  d = opendir("../logs/session");
  if (d) {
    while ((dir = readdir(d)) != NULL)
      ASSERT(strcmp(dir->d_name, logPath) != 0, "Logger already exists\n");
    closedir(d);
  } else if (d == NULL) {
    mkdir("../logs", 0777);
    mkdir("../logs/session", 0777);
  }

  if (access(logPath, F_OK) == 0) {
    type = "a";
  } else {
    type = "w";
  }

  logger.file = fopen(logPath, type);
  pthread_mutex_init(&logger.log_mutex, NULL);
}
void logger_message(LogType type, const char *file, int line,
                    const char *mess) {
  pthread_mutex_lock(&logger.log_mutex);

  ASSERT(logger.file != NULL, "logger wasn't properly createialized...\n");
  ASSERT(mess != NULL, "please enter a logging message...\n");

  char *typeStr = "";

  switch (type) {
  case LOG_TYPE_INFORMATION:
    typeStr = "INFO";
    break;

  case LOG_TYPE_WARNING:
    typeStr = "WARN";
    break;

  case LOG_TYPE_DANGER:
    typeStr = "DANGER";
    break;
  default:
    perror("Invalid logging type\n");
    exit(EXIT_FAILURE);
  }

  time_t t;
  time(&t);
  char dateBuf[255];
  strftime(dateBuf, sizeof(dateBuf), "%a %b %d %H:%M:%S %Y", localtime(&t));

  char outputBuff[1000];

  snprintf(outputBuff, sizeof(outputBuff), "[%s] [%s] [%s:%d] %s\n", dateBuf,
           typeStr, file, line, mess);

  fprintf(logger.file, "%s", outputBuff);
  pthread_mutex_unlock(&logger.log_mutex);
}
void logger_destroy() {
  if (logger.file) {
    fclose(logger.file);
    logger.file = NULL; // Prevent use-after-free
  }

  if (pthread_mutex_trylock(&logger.log_mutex) == 0) {
    pthread_mutex_unlock(&logger.log_mutex);
    pthread_mutex_destroy(&logger.log_mutex);
  }
}