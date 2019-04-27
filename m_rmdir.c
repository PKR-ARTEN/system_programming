#include <stdio.h>
#include <unistd.h>

void m_rmdir(char *path){

	if(rmdir(path) < 0) {
		printf("this directory was using or directory not empty\n");
		printf("or please check directory name is correct\n");
	} else {
		printf("delete directory successfully\n");
	}
}
