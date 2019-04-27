#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "txt_opt_header.h"

int get_path();

void m_execute(char *command_t, char *command_p){
	char *list[50];

	int n = get_path(command_p, &list);
	
	list[n]=NULL;
	
	if(execv(command_t, list)==-1)
		printf(ANSI_COLOR_RED "error in execute program" ANSI_COLOR_RESET "\n");
}
