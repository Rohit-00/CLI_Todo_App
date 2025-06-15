#include <stdio.h>
#include <unistd.h>
#include "help.h"
#include "file.h"
#include "parse.h"
#include "common.h"
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	int c;
	char task[100];
	char *filepath = "../file/todo.txt";
	int fd;
	file_header header = {0};
	fd = create_file(filepath);
	todo *all_tasks;

	while((c = getopt(argc, argv, "hla:r:t:")) != -1){
			switch(c){
			case 'h':
				help();
				break;
			case 'a':
				strncpy(task,optarg,99);
				header = get_header(fd);
				header.total_tasks += 1;     
				write_header(fd, header.total_tasks);         
				add_task(task, fd, &header);
				
				break;
			case 'l':
				header = get_header(fd);
				read_tasks(fd,&header,&all_tasks);
				print_tasks(all_tasks,&header);
    			free(all_tasks);
				break;
			case 't':
				header = get_header(fd);
				int toggle_id =  atoi(optarg);
				toggle_task(toggle_id, fd, &header);
				break;
			case 'r':
				int id = atoi(optarg);
				header = get_header(fd);
				remove_task(id, fd, &header);
				header.total_tasks -= 1;     
				write_header(fd, header.total_tasks); 
				break;
			default:
				help();
				break;
			}
}
close(fd);
}
