#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

#include "txt_opt_header.h"

static void die(const char *s);
int make_directory();
int get_path();

void m_mkdir(char *path){
	char *name[50];
	int n;

	if((n=get_path(path, &name))==0){
		printf(ANSI_COLOR_RED "please input directory name" ANSI_COLOR_RESET "\n");
		return;
	}

	for(int i=0; i<n; i++){
		if(make_directory(name[i])<0){
			printf(ANSI_COLOR_RED "%s : error in make directory" ANSI_COLOR_RESET "\n", name[i]);
		} else {
			printf(ANSI_COLOR_GREEN "%s : successully make directory" ANSI_COLOR_RESET "\n", name[i]);
		}
	}
}

int make_directory(const char *path){
	if(mkdir(path, 0755)==0){
		return 0;
	}
	else{
		if(errno == EEXIST){
			struct stat st;
			if(stat(path, &st) < 0) die("stat");
			if(!S_ISDIR(st.st_mode)){
				printf("[%s] is not a directory\n", path);
			}
	
			return -1;
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
				return -1;
			}
	
			char *sep=strrchr(parent_path, '/');
			if(!sep){
				fprintf(stderr, "error:current directory is not a directory???\n");
				return -1;
			}
			else 
			if(sep==parent_path){
				fprintf(stderr, "error: root directory is not a directory???\n");
				return -1;
			}
			
			*sep='\0';
			if(make_directory(parent_path)<0) return -1;
			mkdir(path,0744);
		
			return 0;
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
