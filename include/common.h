#ifndef COMMON_H
#define COMMON_H
#include <stdbool.h>

typedef struct file_metadata{
	unsigned int total_tasks;
} file_header;

typedef struct {
	int id;
	char task[100];
	bool status;

}todo;

#endif