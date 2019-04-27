#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "txt_opt_header.h"

static void die(const char *s);

void m_mkdir(const char *path){
	if(mkdir(path, 0755)==0){
		printf(ANSI_COLOR_GREEN "%s was created successfully" ANSI_COLOR_RESET "\n", path);
		return ;
	}
	else{
		if(errno == EEXIST){
			struct stat st;
			if(stat(path, &st) < 0) die("stat");
			if(!S_ISDIR(st.st_mode)){
				printf("[%s] is not a directory\n", path);
			}
	
			return;
		}
		else if(errno == ENOENT){
			char *parent_path = strdup(path);
			if(!parent_path) die("strdup");

			char *last=parent_path+strlen(parent_path)-1;
			while(*last=='/' && last != parent_path){
				*last-- = '\0';
			}
	
			if(strcmp(parent_path,"/") == 0){
				fprintf(stderr, "error: root directory is not a directory???\n");
				return;
			}
	
			char *sep=strrchr(parent_path, '/');
			if(!sep){
				fprintf(stderr, "error:current directory is not a directory???\n");
				return;
			}
			else 
			if(sep==parent_path){
				fprintf(stderr, "error: root directory is not a directory???\n");
				return;
			}
			
			*sep='\0';
			m_mkdir(parent_path);
			mkdir(path,0744);
			printf(ANSI_COLOR_GREEN "%s was created successfully" ANSI_COLOR_RESET "\n", path);

			return;
		}
		else{
			perror(path);
			exit(1);
		}
	}
}

static void die(const char *s){
	perror(s);
	exit(1);
}
