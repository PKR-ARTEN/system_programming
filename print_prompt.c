#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_prompt() {	

	char *user_name;
	char host_name[100];

	user_name  = (char*)getenv("USER");
	gethostname(host_name, sizeof(host_name));

	printf("%s@%s:~$ ",user_name, host_name);

}
