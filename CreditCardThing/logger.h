#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

struct timespec startTime;

enum LogLevel {
	LOG_INFO,
	LOG_WARNING,
	LOG_ERROR
};

void logMessage(char* message, enum LogLevel level);
void initLogger();

#endif