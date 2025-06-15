#include "file.h"
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

//this one is just for file header operations

int create_file(char *filepath){

	int fd = open(filepath, O_RDWR | O_CREAT , 0644);

	if(fd == -1){
		perror("open");
		return -1;
	}
	return fd;
}

