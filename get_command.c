//this function do separate command into command type and option/path list
//input is address for save separated command
//return value is check value for background program

#include <stdio.h>
#include <string.h>

char* trim();

int get_command(char **c_t, char **c_p, char **c_o){ //separated command will be saved in c_t, c_p, c_o
	char command_i[300];	//input command
	char *command; 			//trim(input command)
	char *command_t;		//type of command
    char *command_p;		//option or path of command
	char *token;
	int background=0;		//input command has & option?

	gets(command_i);
	command=trim(command_i);		//delete blank before and after input command

    command_t = strdup(command);
    token = strchr(command_t, ' '); //find separate point

    if(token == NULL){ 			//input command has option or path?
		command_p=NULL;
	} else{
		command_p = token;
		command_p++;
		*token='\0';			//separate into command type and command option/path

		if(strcmp(command_p, "&")==0){	//command_p is just &?
			background=1;
			command_p=NULL;
		} else {
			token = strrchr(command_p, ' ');
			if(token != NULL && strcmp(token+1, "&")==0){	//command_p has & option in tail?
				background=1;
				*token='\0';		//then cut &
			}
			command_p=trim(command_p);
		}
	}

    *c_t = command_t;
    *c_p = command_p;
	*c_o = strdup(command);

	return background;
}
