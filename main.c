#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int pid = fork();

	if(pid != 0) {
		execl("./ipc", "./ipc", "2", "b", (char*) NULL);
		wait(NULL);
	} else {
		execl("./ipc", "./ipc", "2","a", (char*) NULL);
	}
}