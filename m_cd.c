//this function do change directory
//input is destination path

#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "txt_opt_header.h"

void m_cd(char *change_path){
	char *token;

	extern char dir[];

	if(change_path == NULL) {
		printf(ANSI_COLOR_RED "please enter path" ANSI_COLOR_RESET "/n");
		return;
	}
	if(strcmp(dir, "~")==0 && strcmp(change_path, "..")==0){
		printf(ANSI_COLOR_RED "current directory is top directory"ANSI_COLOR_RESET "\n");
		return;
	}

	if(chdir(change_path) < 0){ 
		printf(ANSI_COLOR_RED "please input correct path"ANSI_COLOR_RESET "\n");
		return;
	}

	printf(ANSI_COLOR_GREEN "change directory successfully"ANSI_COLOR_RESET "\n");
	if(strcmp(change_path, "..")==0) {
		token=strrchr(dir, '/');
		*token='\0';				//delete current directory for print
	} else if(strcmp(change_path, ".")!=0){
		strcat(dir, "/");
		strcat(dir, change_path);	//add change path to dir for print
	}	
}
