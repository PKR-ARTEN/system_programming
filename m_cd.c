#include <stdio.h>
#include <unistd.h>
#include <string.h>

void m_cd(char *change_path){
	char *token;

	extern char dir[];

	if(change_path == NULL) {
		printf("please input path/n");
	} else {
		if(strcmp(dir, "~")==0 && strcmp(change_path, "..")==0){
			printf("current directory is top directory\n");
		} else {
			if(chdir(change_path) < 0) printf("please input correct path\n");
			else {
				if(strcmp(change_path, "..")==0){
					token=strrchr(dir, '/');
					*token='\0';
				} else if(strcmp(change_path, ".") !=0){
					strcat(dir, "/");
					strcat(dir, change_path);
				}
			}
		}
	}
}
