#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define BUF_SIZE 2048

static void die(const char *s);
static void do_cat(const char *s);

void m_cat(char *original){
	char *path;
	char *token;

	while(1) {
		path = original;
		token = strchr(original, ' ');
		if(token == NULL) {
			do_cat(path);
			break;
		} else {
			original = token+1;
			*token = '\0';
			do_cat(path);
		}
	}

}

static void do_cat(const char *path){
	int fd, n;
	unsigned char  buf[BUF_SIZE];

	fd=open(path, O_RDONLY);
	if(fd <0) die(path);
	for(;;){
		n = read(fd,buf,sizeof(buf));
		if(n<0) die(path);
		if(n==0) break;
		if(write(STDOUT_FILENO, buf, n)<0) die (path);
	}

	if(close(fd) < 0) die(path);
}

static void die(const char *s){
	perror(s);
	exit(1);
}
