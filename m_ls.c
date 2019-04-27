#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "color_header.h"

void m_ls(char *path){
	DIR *d;
	struct dirent *ent;

	printf("show directory.\n\n");


	if(path==NULL){
		path=".";
	}
	
	d = opendir(path);
	if(!d){
		perror(path);
		exit(1);
	}
	int n=0;
	while(ent = readdir(d)){
		char *dir = ent->d_name;
		struct stat buf;
		stat(dir, &buf);

		if(strcmp(dir,"..")!=0 && strcmp(dir, ".")!=0){
			if(S_ISDIR(buf.st_mode)){
				printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\t\t",dir);
			} else{
				printf("%s\t\t", dir);
			}
			n++;
		}

		if(n==5){
			n=0;
			printf("\n");
		}

	}
	
	printf("\n");
}
