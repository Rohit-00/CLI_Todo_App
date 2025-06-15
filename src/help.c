#include "help.h"
#include <stdio.h>
#include "common.h"

void help(){
	printf("\t -l \t \t list all tasks \n");
	printf("\t -a \t \t add a new task \n");
	printf("\t -r <id> \t remove a task \n");
	printf("\t -t <id> \t toggle status of a task \n");
}

void print_tasks(todo *all_tasks, file_header *header){
	printf("+----+------------------------------------------+---------+\n");
	printf("| ID | Task                    			 | Status |\n");
		for (int i = 0; i < header->total_tasks; i++) {
									    
			printf("+----+------------------------------------------+---------+\n");
			printf("| %-2d | %-40s | %-6s |\n", all_tasks[i].id, all_tasks[i].task, all_tasks[i].status ? "Done" : "Pending");
				     }
	printf("+----+------------------------------------------+---------+\n");
}