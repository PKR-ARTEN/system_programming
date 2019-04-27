#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include "txt_opt_header.h"

int get_path();

void m_cp(char *path){
	char *list[3];
	int n;
	int fin;
	int fout;
	ssize_t nn;
	char *buf[2048];

	struct stat fdin;

	if((n=get_path(path,&list))<2){
		printf(ANSI_COLOR_RED "requires two arguments" ANSI_COLOR_RESET "\n");
		return;
	}

	if((fin=open(list[0], O_RDONLY))==-1) {
		printf(ANSI_COLOR_RED "error in open file" ANSI_COLOR_RESET "\n");
	    return;
	}

	fstat(fin, &fdin);

	if((fout=open(list[1], O_WRONLY|O_CREAT|O_TRUNC, fdin.st_mode&(S_IRWXU|S_IRWXG|S_IRWXO)))==-1){
		printf(ANSI_COLOR_RED "error in open file" ANSI_COLOR_RESET "\n");
		return;
	}

	while((nn=read(fin,buf,2048))>0){
		write(fout,buf,nn);
	}

	return;
}
