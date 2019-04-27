#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "txt_opt_header.h"

void print_prompt();
void m_ls();
int get_command(); //separate the command to type and path
void m_mkdir();
void m_cat();
void m_cd();
void m_rm();
void m_cp();
void m_execute();
void m_kill();

int main(){

	char *e = "exit";
	char *ls = "ls";
	char *mkdir = "mkdir";
	char *cat = "cat";
	char *cd = "cd";
	char *rm = "rm";
	char *cp = "cp";

	char *hello1 = "hello";
	char *hello2 = "hello?";

	char *vim = "vim";
	char *execute = "./";
	char *kill = "kill";
	char *clear1 = "clear";
	char *clear2 = "cls";
	char *help1 = "help";
	char *help2 = "-h";

	char *command_t; //command_type
	char *command_p; //command_path or option
	char *command_o; //command_original

	pid_t pid;
	int status;
	int background;

	system("clear");

	while(1){

		print_prompt();

		background = get_command(&command_t, &command_p, &command_o);

		if(strcmp(command_t, cd)==0){
			m_cd(command_p);
		} else if(strcmp(command_t, e)==0){
			system("clear");
			exit(0);
		} else{
			switch(pid=fork()){
				case -1 :
					printf(ANSI_COLOR_RED "error in fork" ANSI_COLOR_RESET "\n");
					break;

				case 0 :
        			if(strcmp(command_t, clear1)==0 || strcmp(command_t, clear2)==0){
    			        system("clear");
        			} else if(strcmp(command_t, vim)==0){
            			system(command_o);
        			} else if(strcmp(command_t, ls)==0){
            			m_ls(command_p);
					} else if(strncmp(command_t, execute, 2)==0){
						m_execute(command_t, command_p);
					} else if(strcmp(command_t, cp)==0){
						m_cp(command_p);
					} else if(strcmp(command_t, kill)==0){
						m_kill(atoi(command_p));
        			} else if(strcmp(command_t, hello1)==0 || strcmp(command_t, hello2)==0){
            			printf("hello!\n");
        			} else if(strcmp(command_t, mkdir)==0){
            			m_mkdir(command_p);
        			} else if(strcmp(command_t, cat)==0){
            			m_cat(command_p);
					} else if(strcmp(command_t, rm)==0){
            			m_rm(command_p);
        			} else if(strcmp(command_t, help1)==0 || strcmp(command_t, help2)==0){
			            printf("ls - show content of this directory\n");
			            printf("ls [path] - show content of path\n");
			            printf("mkdir [directory name] [name2] ... - create directory\n");
			            printf("rm [directory name or file name] [name2] ... - delete directory or file\n");
			            printf("\t -r delete all, including non-empty directories\n");
            			printf("\t -d delete only directory\n");
			            printf("\t -f delete only file\n");
			            printf("cat [file1] [file2] ... - show content of files\n");
			            printf("cd [path] - change directory\n");
			            printf("cls or clear - clear window\n");
			            printf("hello?\n");
			            printf("exit - close this shell\n");
			        } else {
			            printf("no command\n");
            			printf("if you need help, please enter" ANSI_ITALIC_TEXT " help" ANSI_RESET_TEXT " or" ANSI_ITALIC_TEXT " -h" ANSI_RESET_TEXT"\n");
        			}
					_exit(0);
					break;

				default :
					sighold(SIGINT);
					if(!background) (void)waitpid(pid, &status, 0);
					else printf("[pid] %d\n", pid);
					sighold(SIGINT);
					break;
			}
		}

		printf("\n");
	}
	
	return 0;
}
