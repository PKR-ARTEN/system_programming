#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "txt_opt_header.h"

void print_prompt();
void m_ls();
void get_command(); //separate the command to type and path
void m_mkdir();
void m_cat();
void m_cd();
void m_rmdir();

int main(){

	char *e = "exit";
	char *ls = "ls";
	char *mkdir = "mkdir";
	char *cat = "cat";
	char *cd = "cd";
	char *rmdir = "rmdir";

	char *hello1 = "hello";
	char *hello2 = "hello?";

	char *clear1 = "clear";
	char *clear2 = "cls";
	char *help1 = "help";
	char *help2 = "-h";

	char *command_t; //command_type
	char *command_p; //command_path or option
	char *command_o; //command_original

	system("clear");

	while(1){

		print_prompt();

		get_command(&command_t, &command_p, &command_o);

		if(strcmp(command_t, e)==0){
			system("clear");
			exit(0);
		} else if(strcmp(command_t, clear1)==0 || strcmp(command_t, clear2)==0){
			system("clear");
			continue;
		} else if(strcmp(command_t, ls)==0){
			m_ls(command_p);
		} else if(strcmp(command_t, hello1)==0 || strcmp(command_t, hello2)==0){
			printf("hello!\n");
		} else if(strcmp(command_t, mkdir)==0){
			m_mkdir(command_p);
		} else if(strcmp(command_t, cat)==0){
			m_cat(command_p);
		} else if(strcmp(command_t, cd)==0){
			m_cd(command_p);
		} else if(strcmp(command_t, rmdir)==0){
			m_rmdir(command_p);
		} else if(strcmp(command_t, help1)==0 || strcmp(command_t, help2)==0){
			printf("ls - show content of this directory\n");
			printf("ls [path] - show content of path\n");
			printf("mkdir [directory name] - create directory\n");
			printf("rmdir [directory name] - delete directory\n");
			printf("cat [filename] - show content of file\n");
			printf("cat [file1] [file2] ... - show content of files\n");
			printf("cd [path] - change directory\n");
			printf("cls or clear - clear window\b");
			printf("hello?\n");
			printf("exit - close this shell\n");
		} else {
			printf("no command\n");
			printf("if you need help, please enter" ANSI_ITALIC_TEXT " help" ANSI_RESET_TEXT " or" ANSI_ITALIC_TEXT " -h" ANSI_RESET_TEXT"\n");
		}

		printf("\n");
	}
	
	return 0;
}
