#include "log.h"

void open_log_file() {
	__file_handle = fopen("logs.txt", "a");
}

void close_log_file() {
	fclose(__file_handle);
}

