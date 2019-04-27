#include <stdio.h>
#include <string.h>

int get_path(char *path, char *list[]){
	char *token;
	int n=0;

	if(path == NULL){
		return 0;
	}

	while(1){
		list[n] = path;
		n++;

        token = strchr(path, ' ');
		if(token == NULL) {
            break;
        } else {
            path = token+1;
            *token = '\0';
        }
	}

	return n;
}
