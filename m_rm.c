#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

#include "txt_opt_header.h"

int get_path();
int remove_directory();

void m_rm(char *original){
	char *path[50];
	int n;
	
	if((n=get_path(original, &path)) == 0) {
		printf(ANSI_COLOR_RED "please input file name or directory name" ANSI_COLOR_RESET "\n");
		return;
	}

	if(strcmp(path[0], "-r")==0){
		if(strcmp(path[1], "-d")==0){
			for(int i=2; i<n; i++){
				struct stat sb;
				stat(path[i], &sb);
				if(S_ISDIR(sb.st_mode)){
					if(remove_directory(path[i])<0){
						printf(ANSI_COLOR_RED "%s : this directory was using or not empty, or please check directory name is correct" ANSI_COLOR_RESET "\n", path[i]);
					} else {
						printf(ANSI_COLOR_GREEN "%s : successfully removed" ANSI_COLOR_RESET "\n", path[i]);
					}
				} else {
					printf(ANSI_COLOR_RED "%s : this is not a directory" ANSI_COLOR_RESET "\n", path[i]);
				}
			}
		} else {
			for(int i=1; i<n; i++){
            	struct stat sb;
            	stat(path[i], &sb);
            	if(S_ISDIR(sb.st_mode)){
            	    if(remove_directory(path[i])<0){
               	    	printf(ANSI_COLOR_RED "%s : this directory was using or not empty, or please check directory name is correct" ANSI_COLOR_RESET "\n", path[i]);
                	} else{
                	    printf(ANSI_COLOR_GREEN "%s : successfully removed" ANSI_COLOR_RESET "\n", path[i]);
            	    }
            	} else {
            	    if(unlink(path[i])<0){
            	        printf(ANSI_COLOR_RED "%s : error in removing" ANSI_COLOR_RESET "\n", path[i]);
            	    } else {
            	        printf(ANSI_COLOR_GREEN "%s : successfully removed" ANSI_COLOR_RESET "\n", path[i]);
            	    }
            	}
        	}
		}
	} else if(strcmp(path[0], "-d")==0){
		if(strcmp(path[1], "-r")==0){
		
		} else{
			for(int i=1; i<n; i++){
				struct stat sb;
				stat(path[i], &sb);
				if(S_ISDIR(sb.st_mode)){
                	if(rmdir(path[i])<0){
                	    printf(ANSI_COLOR_RED "%s : this directory was using or not empty, or please check directory name is correct" ANSI_COLOR_RESET "\n", path[i]);
                	} else{
                    	printf(ANSI_COLOR_GREEN "%s : successfully removed" ANSI_COLOR_RESET "\n", path[i]);
                	}
            	} else {
                	printf(ANSI_COLOR_RED "%s : this is not a directory" ANSI_COLOR_RESET "\n", path[i]);
            	}
			}
		}
		
	} else if(strcmp(path[0], "-f")==0){
		for(int i=1; i<n; i++){
            struct stat sb;
            stat(path[i], &sb);
            if(S_ISDIR(sb.st_mode)){
                printf(ANSI_COLOR_RED "%s : this is a directory" ANSI_COLOR_RESET "\n", path[i]);
            } else {
                if(unlink(path[i])<0){
                    printf(ANSI_COLOR_RED "%s : error in removing" ANSI_COLOR_RESET "\n", path[i]);
                } else {
                    printf(ANSI_COLOR_GREEN "%s : successfully removed" ANSI_COLOR_RESET "\n", path[i]);
                }
            }
        }
	} else{
		for(int i=0; i<n; i++){
			struct stat sb;
			stat(path[i], &sb);
			if(S_ISDIR(sb.st_mode)){
				if(rmdir(path[i])<0){
					printf(ANSI_COLOR_RED "%s : this directory was using or not empty, or please check directory name is correct" ANSI_COLOR_RESET "\n", path[i]);
				} else{
					printf(ANSI_COLOR_GREEN "%s : successfully removed" ANSI_COLOR_RESET "\n", path[i]);
				}
			} else {
				if(unlink(path[i])<0){
					printf(ANSI_COLOR_RED "%s : error in removing" ANSI_COLOR_RESET "\n", path[i]);
				} else {
					printf(ANSI_COLOR_GREEN "%s : successfully removed" ANSI_COLOR_RESET "\n", path[i]);
				}
			}
		}
	}
}

int m_rm2(char *path){
	struct stat sb;
	stat(path, &sb);

	if(S_ISDIR(sb.st_mode)){
		if(remove_directory(path)<0){
			return -1;
		}
	} else {
		if(unlink(path)<0){
			return -1;
		}
	}

	return 0;
}

int remove_directory(const char *path){
	DIR *d = opendir(path);
	size_t path_len = strlen(path);
	int r = -1;

	if(d){
		struct dirent *p;

		r=0;

		while(!r && (p=readdir(d))){
			int r2 = -1;
			char *buf;
			size_t len;

			if(!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) continue;

			len = path_len + strlen(p->d_name)+2;
			buf = malloc(len);

			if(buf){
				struct stat statbuf;

				snprintf(buf, len, "%s/%s", path, p->d_name);

				if(!stat(buf, &statbuf)) {
					if(S_ISDIR(statbuf.st_mode)){
						r2=remove_directory(buf);
					} else {
						r2=unlink(buf);
					}
				}

				free(buf);
			}
			r=r2;
		}
		closedir(d);
	}

	if(!r){
		r=rmdir(path);
	}

	return r;
}
