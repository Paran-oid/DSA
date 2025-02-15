#include "logs.h"
#include "funcs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>
#include <sys/stat.h>

#include <pthread.h>
#include <unistd.h>

static Logger logger;

void init_logger(LogDate date) {
  time_t t;
  time(&t);
  char dateBuf[255];
  strftime(dateBuf, sizeof(dateBuf), "%a %b %d %H:%M:%S %Y", localtime(&t));

  char *type;
  char logPath[1000];

  if (date == ALL) {
    snprintf(logPath, sizeof(logPath), "../logs/all-logs.txt");
    type = "a";
  } else if (date == SESSION) {
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
  pthread_mutex_init(&logger.logMutex, NULL);
}
void log_message(LogType type, char *file, i32 line, char *mess) {
  pthread_mutex_lock(&logger.logMutex);

  ASSERT(logger.file != NULL, "logger wasn't properly initialized...\n");
  ASSERT(mess != NULL, "please enter a logging message...\n");

  char *typeStr = "";

  switch (type) {
  case logInformation:
    typeStr = "INFO";
    break;

  case logWarning:
    typeStr = "WARN";
    break;

  case logDanger:
    typeStr = "DANGER";
    break;
  }

  time_t t;
  time(&t);
  char dateBuf[255];
  strftime(dateBuf, sizeof(dateBuf), "%a %b %d %H:%M:%S %Y", localtime(&t));

  char outputBuff[1000];

  snprintf(outputBuff, sizeof(outputBuff), "[%s] [%s] [%s:%d] %s\n", dateBuf,
           typeStr, file, line, mess);

  fprintf(logger.file, "%s", outputBuff);
  pthread_mutex_unlock(&logger.logMutex);
}
void destroy_logger(void) {
  if (logger.file) {
    fclose(logger.file);
    logger.file = NULL; // Prevent use-after-free
  }

  if (pthread_mutex_trylock(&logger.logMutex) == 0) {
    pthread_mutex_unlock(&logger.logMutex);
    pthread_mutex_destroy(&logger.logMutex);
  }
}