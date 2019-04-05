#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_prompt() {	

	char *user_name;
	char host_name[30];

	char dir_path[100];

	user_name  = (char*)getenv("USER");
	gethostname(host_name, sizeof(host_name));
	getcwd(dir_path, sizeof(dir_path));

	printf("%s@%s:~%s$ ",user_name, host_name, dir_path);

}
