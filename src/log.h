#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>

FILE *__file_handle;

void open_log_file();
void close_log_file();
#define LOG(...) \
	fprintf(__file_handle, __VA_ARGS__)

#endif // LOG_H
