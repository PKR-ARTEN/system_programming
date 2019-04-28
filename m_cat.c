//this function do read file and print in console
//input is file name list

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include "txt_opt_header.h"

#define BUF_SIZE 2048

static void do_cat(const char *s);
int get_path();

void m_cat(char *original){
	char *path[50];
	int n;
	
	if((n=get_path(original, &path))==0) {	//if n=0, there is no name
		printf(ANSI_COLOR_RED "please input file name or path" ANSI_COLOR_RESET "\n");
		return;
	} 

	for(int i=0; i<n; i++){
		do_cat(path[i]);
	}
}

static void do_cat(const char *path){
	int fd, n;
	unsigned char  buf[BUF_SIZE];

	fd=open(path, O_RDONLY);
	if(fd <0) printf(ANSI_COLOR_RED "please input correct file name or path" ANSI_COLOR_RESET "\n");
	else {
		for(;;){
			n = read(fd,buf,sizeof(buf));
			if(n<0) {
				printf(ANSI_COLOR_RED "error in reading file" ANSI_COLOR_RESET "\n");
				break;
			}
			if(n==0) break;
			if(write(STDOUT_FILENO, buf, n)<0){
				printf(ANSI_COLOR_RED "error in writing file" ANSI_COLOR_RESET "\n");
				break;
			}
		}

		if(close(fd) < 0) {
			printf(ANSI_COLOR_RED "error occure while close file" ANSI_COLOR_RESET "\n");
			return;
		}
	}
}
