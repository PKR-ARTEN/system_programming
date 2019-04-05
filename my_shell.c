#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_prompt();

int main(){

	char *e = "exit";
	char *command;
	char *command_c;

	system("clear");
	
	print_prompt();

	while(1){
		
		scanf("%s", command);
		command_c = strdup(command);

		if(strcmp(command_c, e)==0){
			printf("shell close\n");
			system("clear");
			exit(0);
		} else {
			printf("no command\n");
			print_prompt();
		}
	}
	
	return 0;
}
