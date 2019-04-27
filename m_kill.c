#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

#include "txt_opt_header.h"

void m_kill(pid_t pid){
	kill(pid, SIGKILL);
	printf(ANSI_COLOR_GREEN "kill %d" ANSI_COLOR_RESET "\n", pid);
}
