#ifndef INC_MEMORYLOG_H
#define INC_MEMORYLOG_H

void log_malloc(int object_type);
void log_delete(int object_type);
void print_log_to_file();

#endif INC_MEMORYLOG_H