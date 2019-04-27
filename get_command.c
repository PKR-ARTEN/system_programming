#include <stdio.h>
#include <string.h>

void get_command(char **c_t, char **c_p, char **c_o){
	char command[300];
    char *command_t;
    char *command_p;
	char *token;

    gets(command);
    command_t = strdup(command);
    token = strchr(command_t, ' ');
    if(token == NULL){
		command_p=NULL;
	} else{
		command_p = token;
		command_p++;
		*token='\0';
	}

    *c_t = command_t;
    *c_p = command_p;
	*c_o = strdup(command);
}
