#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_prompt();
void m_ls();

int main(){

	char *e = "exit";
	char *ls = "ls";
	char *hello = "hello";
	char *help1 = "help";
	char *help2 = "-h";
	char *command;
	char *command_c;

	system("clear");

	while(1){

		print_prompt();
		
		scanf("%s", command);
		command_c = strdup(command);

		if(strcmp(command_c, e)==0){
			system("clear");
			exit(0);
		} else if(strcmp(command_c, ls)==0){
			printf("show direcory\n");
			m_ls(NULL);
		} else if(strcmp(command_c, hello)==0){
			printf("hello!\n");
		} else if(strcmp(command_c, help1)==0 || strcmp(command_c, help2)==0){
			printf("ls - show content of this folder\n");
			printf("ls [path] - show content of path\n");
			printf("exit - close this shell\n");
		} else {
			printf("no command\n");
			printf("If you need help, please enter \"help\" or \"-h\"\n");
		}
	}
	
	return 0;
}
