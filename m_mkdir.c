#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

static void die(const char *s);

void m_mkdir(const char *path){
	//printf("current %s\n", path);
	//mkdir(path, 0777);
	if(mkdir(path, 0777)==0){
		return ;
	}
	else{
		if(errno == EEXIST){
			struct stat st;
			if(stat(path, &st) < 0) die("stat");
			if(!S_ISDIR(st.st_mode)){
				fprintf(stderr, "file sxists but is not a directory : %s\n", path);
				exit(1);
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
				exit(1);
			}
	
			char *sep=strrchr(parent_path, '/');
			if(!sep){
				fprintf(stderr, "error:current directory is not a directory???\n");
				exit(1);
			}
			else 
			if(sep==parent_path){
				fprintf(stderr, "error: root directory is not a directory???\n");
				exit(1);
			}
			
			*sep='\0';
			m_mkdir(parent_path);
			mkdir(path,0777);
			
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
