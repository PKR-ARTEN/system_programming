//this function show content of directory

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

#include "txt_opt_header.h"

void m_ls(char *path){
	DIR *d;
	struct dirent *ent;

	if(path==NULL) path=".";
	
	d = opendir(path);
	if(!d){
		printf(ANSI_COLOR_RED "no such file or a directory" ANSI_COLOR_RESET "\n");
		return;
	}

	int n=0;
	
	if(strcmp(path, ".")==0) printf(ANSI_COLOR_GREEN "show content of this directory" ANSI_COLOR_RESET "\n\n");
	else printf(ANSI_COLOR_GREEN "show content of " ANSI_ITALIC_TEXT " %s" ANSI_RESET_TEXT ANSI_COLOR_RESET "\n\n", path);
	
	while(ent = readdir(d)){
		char *dir = ent->d_name;
		struct stat buf;
		stat(dir, &buf);

		if(strcmp(dir,"..")!=0 && strcmp(dir, ".")!=0){
			if(S_ISDIR(buf.st_mode)) printf(ANSI_BOLD_TEXT ANSI_COLOR_BLUE "%-25s" ANSI_COLOR_RESET ANSI_RESET_TEXT,dir);
			else printf("%-25s", dir);
			n++;
		}

		if(n==5){
			n=0;
			printf("\n");
		}

	}
	
	printf("\n");
}
