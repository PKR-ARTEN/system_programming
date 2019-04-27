#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "txt_opt_header.h"

void print_prompt() {	

	char *user_name;
	char host_name[30];

	extern char dir[];

	user_name  = (char*)getenv("USER");
	gethostname(host_name, sizeof(host_name));

	printf(ANSI_BOLD_TEXT ANSI_COLOR_YELLOW "%s@%s:"	ANSI_COLOR_CYAN "%s $" ANSI_COLOR_RESET ANSI_RESET_TEXT " ", user_name, host_name, dir);

}
