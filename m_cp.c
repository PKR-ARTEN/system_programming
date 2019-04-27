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
mode_t get_st_mode();

void m_cp(char *path){
	char *list[2];
	int n;

	if((n=get_path(path,&list))<2){
		printf(ANSI_COLOR_RED "requires two arguments" ANSI_COLOR_RESET "\n");
		return;
	}

	if(S_ISDIR(get_st_mode(list[0]))){
		int nnn = dir_copy(list[0], list[1]);
		if(nnn < 0) printf(ANSI_COLOR_RED "error in copy" ANSI_COLOR_RESET "\n");
		else printf(ANSI_COLOR_GREEN "copy successfully" ANSI_COLOR_RESET"\n");
	} else {
		if(file_copy(list[0],list[1])<0) printf(ANSI_COLOR_RED "error in copy" ANSI_COLOR_RESET "\n");
		else printf(ANSI_COLOR_GREEN "copy successfully" ANSI_COLOR_RESET"\n");
	}
}

int dir_copy(char *original, char *direction){
	DIR *dir_info=NULL;
	struct dirent *dir_entry=NULL;
	char filepath[1000];
	char newfilepath[1000];
	dir_info=opendir(original);

	int check_error=0;

	if(NULL==dir_info) return -1;

	while((dir_entry=readdir(dir_info)) != NULL) {
		mkdir(direction, get_st_mode(original));
		if((strcmp(dir_entry->d_name, ".") ==0) || strcmp(dir_entry->d_name, "..")==0) continue;
		sprintf(filepath, "%s/%s", original, dir_entry->d_name);
		sprintf(newfilepath, "%s/%s", direction, dir_entry->d_name);
		if(S_ISDIR(get_st_mode(filepath))){
			mkdir(direction, get_st_mode(filepath));
			if(dir_copy(filepath, newfilepath)<0) check_error=-1;
		} else {
			if(file_copy(filepath, newfilepath)<0) check_error=-1;
		}
	}	

	closedir(dir_info);
	
	return check_error;
}

int file_copy(char *filename, char *newfilename){

	FILE *f;
	FILE *g;
	int cnt=0;
	char buff[1];
	
	if((f=fopen(filename, "rb"))==NULL) return -1;
	if((g=fopen(newfilename, "wb"))==NULL) return -1;

	while(!feof(f)){
		fread(&buff,1,1,f);
		if(!feof(f)) fwrite(&buff,1,1,g); cnt++;
	}

	fclose(f);
	fclose(g);

	return 0;
}

mode_t get_st_mode(char *filepath){
	struct stat buf;
	stat(filepath, &buf);
	return (mode_t) buf.st_mode;
}
