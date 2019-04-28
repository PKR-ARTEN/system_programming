//this function do separate each path and option
//input is one string of option and path list
//output is separated option and path list
//return value is number of option and path

#include <stdio.h>
#include <string.h>

char* trim();

int get_path(char *path, char *list[]){	//separated option and path will be saved in list
	char *token;
	int n=0;

	if(path == NULL) return 0;

	while(1){

		path = trim(path);
		list[n] = path;
		n++;

        token = strchr(path, ' ');	//find point to separate
		
		if(token == NULL) break;	//does not exist other option or path
        else {
            path = token+1;
            *token = '\0';		//separate
        }
	}

	return n;
}
