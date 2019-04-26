#include <stdio.h>
#include <string.h>

void get_command(char **c_t, char **c_p){
	char command[300];
    char *command_t;
    char *command_p;

    gets(command);
    command_t = strdup(command);
    command_t = strtok(command_t, " ");
    command_p = strtok(NULL, " ");

    *c_t = command_t;
    *c_p = command_p;
}
