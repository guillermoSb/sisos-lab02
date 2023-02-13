
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// A pipe is an in memory file
// It is a buffer saved to memory and we can write and read to it.
// A file descriptor is a key for access the file
int main(int argc, char* argv[]) {
	// two because the pipe has two ends fd[0] - read; fd[1] - write

	int fd[2];
	if(pipe(fd) == -1) {
		printf("An error ocurred on pipe");
		return 1;
	};

	// The file descriptors get copied to each instance
	// We need to close the file descriptors on both programs
	// We can open / close them independently of any other

	int id = fork();
	if(id == -1) {
		printf("An error ocurred on fork\n");
		return 4;
	}
	// on the child
	if(id == 0) {
		close(fd[0]);	// We are not reading, so close it at the beginning
		int x;
		printf("Input a number: ");
		scanf("%d", &x);
		// Write on the file descriptor
		if(write(fd[1], &x, sizeof(int)) == -1) {
			printf("An error ocurred on write\n");
			return 2;
		};
		// Close the descriptors
		close(fd[1]);
	} else {
		wait(NULL);
		close(fd[1]);
		int y;
		if(read(fd[0], &y, sizeof(int)) == -1) {
			printf("An error ocurred on read\n");
			return 2;
		};
		close(fd[0]);
		printf("Got from child process: %d\n", y);
	}

	return 0;
}