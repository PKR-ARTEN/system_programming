#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

void m_ls(char *path){
	DIR *d;
	struct dirent *ent;
	
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
		
		if(strcmp(dir,"..")!=0 && strcmp(dir, ".")!=0){
			printf("%s\t",dir);
		}
		n++;
		if(n==5){
			n=0;
			printf("\n");
		}

	}
	
	printf("\n");
}
