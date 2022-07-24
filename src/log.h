#ifndef LOG_H
#define LOG_H

#include <stdarg.h>
#include <stdio.h>

FILE *__file_handle;

void open_log_file();
void close_log_file();
#define LOG(str) \
	fprintf(__file_handle, str); \
	close_log_file(); \
	open_log_file()
#define LOG_VA(str, ...) \
	fprintf(__file_handle, str, __VA_ARGS__); \
	close_log_file(); \
	open_log_file()

#endif // LOG_H
