#include <stdio.h>
#include <string.h>

int get_command(char **c_t, char **c_p, char **c_o){
	char command[300];
    char *command_t;
    char *command_p;
	char *token;
	int background=0;

    gets(command);
    command_t = strdup(command);
    token = strchr(command_t, ' ');
    if(token == NULL){
		command_p=NULL;
	} else{
		command_p = token;
		command_p++;
		*token='\0';

		if(strcmp(command_p, "&")==0){
			background=1;
			command_p=NULL;
		} else {
			token = strrchr(command_p, ' ');
			if(token != NULL && strcmp(token+1, "&")==0){
				background=1;
				*token='\0';
			}
		}
	}

    *c_t = command_t;
    *c_p = command_p;
	*c_o = strdup(command);

	return background;
}
