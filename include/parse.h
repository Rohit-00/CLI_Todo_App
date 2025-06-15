#ifndef PARSE_F
#define PARSE_F
#include "common.h"

int add_task(char *task, int file_desc, file_header *header);
int read_tasks(int file_desc, file_header *header, todo **all_tasks);
int remove_task(int id, int file_desc, file_header *header);
int toggle_task(int id, int file_desc, file_header *header);
file_header get_header(int file_desc);
void write_header(int file_desc, int total_tasks);
#endif