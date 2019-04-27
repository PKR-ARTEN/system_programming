#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#include "txt_opt_header.h"

int get_path();
int dir_copy();
int file_copy();
int m_rm2();
mode_t get_st_mode();

void m_mv(char *path){
	char *list[2];
	int n;

	if((n=get_path(path,&list))<2){
		printf(ANSI_COLOR_RED "requires two arguments" ANSI_COLOR_RESET "\n");
		return;
	}

	if(S_ISDIR(get_st_mode(list[0]))){
		if(dir_copy(list[0], list[1]) < 0) printf(ANSI_COLOR_RED "error in move" ANSI_COLOR_RESET "\n");
		else{
			if(m_rm2(list[0])<0) printf(ANSI_COLOR_RED "error in delete" ANSI_COLOR_RESET "\n");
			printf(ANSI_COLOR_GREEN "move successfully" ANSI_COLOR_RESET"\n");
		}
	} else {
		if(file_copy(list[0],list[1])<0) printf(ANSI_COLOR_RED "error in move" ANSI_COLOR_RESET "\n");
		else {
			if(m_rm2(list[0])<0) printf(ANSI_COLOR_RED "error in delete" ANSI_COLOR_RESET "\n");
			printf(ANSI_COLOR_GREEN "move successfully" ANSI_COLOR_RESET"\n");
		}
	}
}
