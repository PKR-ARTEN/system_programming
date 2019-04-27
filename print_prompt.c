#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "color_header.h"

void print_prompt() {	

	char *user_name;
	char host_name[30];

	extern char dir[];

	user_name  = (char*)getenv("USER");
	gethostname(host_name, sizeof(host_name));

	printf(ANSI_COLOR_YELLOW "%s@%s:"	ANSI_COLOR_RED "~%s $" ANSI_COLOR_RESET " ", user_name, host_name, dir);

}
