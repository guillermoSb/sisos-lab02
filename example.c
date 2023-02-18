
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>		/* For O_* constants */
#include <errno.h>
#include <string.h>

int main(void) {
	int x, y;

	x = fork();
	if(x != 0) {
		y = fork();
		if (y == 0) {
			fork();
			printf("x\n");
		}
	} else {
		fork();
	}
	fork();
	printf("x\n");
}
