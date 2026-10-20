#include <stdio.h>
#include <time.h>

#include "logger.h"

struct timespec startTime;

void logMessage(char* message, enum LogLevel level) {
	struct timespec now = { 0 };
	timespec_get(&now, TIME_UTC);

	double msAge = (now.tv_nsec - startTime.tv_nsec) / 100000000.0;
	switch (level) {
	case LOG_INFO:
		printf("%f [INFO] %s\n", msAge, message);
		break;
	case LOG_WARNING:
		printf("%f [WARNING] %s\n", msAge, message);
		break;
	case LOG_ERROR:
		printf("%f [ERROR] %s\n", msAge, message);
		break;
	}
}

void initLogger() {
	timespec_get(&startTime, TIME_UTC);
	logMessage("Logger initialized.", LOG_INFO);
}