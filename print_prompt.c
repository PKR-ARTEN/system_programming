#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "variables.h"

void print_prompt() {	

	char *user_name;
	char host_name[30];

	user_name  = (char*)getenv("USER");
	gethostname(host_name, sizeof(host_name));

	printf("%s@%s:~%s$ ",user_name, host_name, dir);

}
