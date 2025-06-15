#include <fcntl.h>
#include "parse.h"
#include <unistd.h>
#include <string.h>
#include "common.h"
#include <stdio.h>
#include "file.h"
#include "help.h"
#include <stdlib.h>
#include <stdbool.h>

file_header get_header(int file_desc){
		file_header header;
		lseek(file_desc, 0, SEEK_SET);
		int r = read(file_desc, &header, sizeof(file_header));
		lseek(file_desc, 0, SEEK_SET);
		if(r == -1){
			perror("Header Open");
		}
		return header;
}

void write_header(int file_desc, int total_tasks){
	lseek(file_desc, 0, SEEK_SET);
	file_header header;
	header.total_tasks = total_tasks;
	int w = write(file_desc, &header, sizeof(file_header));
	lseek(file_desc, 0, SEEK_SET);
}


int add_task(char task[100], int file_desc, file_header *header){
	lseek(file_desc, 0, SEEK_END);
	todo *all_tasks = NULL;
	todo t;
	t.id = header->total_tasks;
	strncpy(t.task,task,99);
	t.status = false;
	int w = write(file_desc, &t, sizeof(todo));
	if(w == -1){
		perror("task write");
		return -1;
	}
	read_tasks(file_desc, header, &all_tasks);
	print_tasks(all_tasks,header);
	free(all_tasks);
	return 0;
}

int read_tasks(int file_desc, file_header *header, todo **all_tasks){
    int total = header->total_tasks;
    if (total == 0) {
        printf("No tasks found.\n");
        return 0;
    }

    todo *task_list = calloc(total, sizeof(todo));
    todo *temp = task_list;
    if (!task_list) {
        perror("calloc");
        return -1;
    }

    lseek(file_desc,sizeof(file_header),SEEK_SET);
    ssize_t bytes_read = read(file_desc, task_list, total * sizeof(todo));


    *all_tasks = task_list;
    temp = NULL;
    return 0;
}

int remove_task(int id, int file_desc, file_header *header){
	todo *all_tasks = NULL ;
	
	read_tasks(file_desc, header, &all_tasks);
	todo temp[100];
	for(int i = 0; i < header->total_tasks; i++){
	
		if(all_tasks[i].id >= id){
			temp[i].id = all_tasks[i].id;
			strncpy(temp[i].task,all_tasks[i+1].task,99);
			temp[i].status = all_tasks[i+1].status;
		}else{
			temp[i].id = all_tasks[i].id;
			strncpy(temp[i].task,all_tasks[i].task,99);
			temp[i].status = all_tasks[i].status;
		}
		
	}
	printf("+----+------------------------------------------+---------+\n");
	printf("| ID | Task                    			 | Status |\n");
	for (int i = 0; i < header->total_tasks-1; i++) {
		    
    
    printf("+----+------------------------------------------+---------+\n");
    printf("| %-2d | %-40s | %-6s |\n", temp[i].id, temp[i].task, temp[i].status ? "Done" : "Pending");
     }
     printf("+----+------------------------------------------+---------+\n");

	off_t header_size = sizeof(file_header);
	if (ftruncate(file_desc, header_size) == -1) {
		perror("ftruncate");
		free(all_tasks);
		return -1;
	}
	lseek(file_desc, sizeof(file_header), SEEK_SET);
	int w = write(file_desc, &temp, sizeof(todo)*header->total_tasks - sizeof(todo));
	if(w == -1){
		perror("writing");
	}

	free(all_tasks);
	all_tasks = NULL;
	return 0;
}

int toggle_task(int id, int file_desc, file_header *header){
	todo *all_tasks = NULL;
	read_tasks(file_desc, header, &all_tasks);

	for(int i = 0; i < header->total_tasks; i++){
		if(all_tasks[i].id == id){
			if( all_tasks[i].status == false ){
				all_tasks[i].status = true;
			}else{
				all_tasks[i].status = false;
			}
			
			break;
		}
	}
	print_tasks(all_tasks,header);
	lseek(file_desc, sizeof(file_header), SEEK_SET);
	int w = write(file_desc, all_tasks, sizeof(todo) * header->total_tasks);
	if(w == -1){
		perror("writing");
	}

	free(all_tasks);
	all_tasks = NULL;
	return 0;

}