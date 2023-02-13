/**
 * @file ipc.c
 * @author Guillermo Santos (san191517@uvg.edu.gt)
 * @brief Ejercicio 05 del Laboratorio 2 - Sistemas Operativos 2023.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h> /* For mode constants */
#include <fcntl.h>		/* For O_* constants */
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
	// Get the parameters from the command line
	char x = *argv[2];
	int n = atoi(argv[1]);
	// Define variables
	int size = 10;
	int fd;
	int fifofd;
	char *mem;
	char terminal = '-';

	char *mymemory = "/memoryipc";
	char *myfifo = "fifo";

	mkfifo(myfifo, 0777);

	// Print initial message
	printf("I am %c\n", x);

	fd = shm_open(mymemory, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR); // Open a shared memory space

	if (fd == -1)
	{
		int errsv = errno;
		// Indicate that the space is already opened.
		if (errsv == EEXIST)
		{
			printf("%c: Shared memory obj already created.\n", x);
		}
		// Indicate that the file descriptor is -1
		printf("%c: Received shm fd: -1.\n", x);
		// Get the file descriptor from the other process
		fifofd = open(myfifo, O_RDONLY);
		if (fifofd == -1)
		{
			printf("%c: Could not open fifo queue on process.", x);
			return 1;
		}
		int fdFromFifo;
		read(fifofd, &fdFromFifo, sizeof(int));
		printf("%c: Received fd from fifo queue: %d\n", x, fdFromFifo);
		fd = shm_open(mymemory, O_RDWR, S_IRUSR | S_IWUSR);

		if (fd == -1)
		{
			printf("%c: Could not open file descriptor.", x);
			return 1;
		}
	}
	else
	{
		printf("%c: Created new shared mem obj %d.\n", x, fd);
		if (ftruncate(fd, size) == -1)
		{
			printf("%c: Failed to allocate shared memory space", x);
			return 4;
		}
		int fifofd = open(myfifo, O_WRONLY);
		write(fifofd, &fd, sizeof(int));
	}
	mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (mem == MAP_FAILED)
	{
		printf("%c: Error creating shared space.\n", x);
	}

	printf("%c: Ptr created with value %p\n", x, &mem);

	int compipe[2];	// Pipe that allows parent-child communication
	if (pipe(compipe) == -1)
	{
		printf("An error ocurred while trying to create the pipe.\n");
		return 2;
	};

	int pid = fork();
	if (pid == -1) {
		printf("An error ocurred while trying to fork.\n");
		return 3;
	}
	if (pid == 0)
	{
		close(compipe[1]); // We are not writing, close the pipe
		while (1)
		{
			char received;
			read(compipe[0], &received, sizeof(char));

			if (received == terminal)
			{
				break;
			}
			else
			{
				strncat(mem, &received, 1);
			}
		}

		close(compipe[0]); // Stop reading
	}
	else
	{
		close(compipe[0]); // We are not reading, so close it at the beginning
		for (int i = 0; i < size; i++)
		{
			if (i % n == 0)
			{
				write(compipe[1], &x, sizeof(char));	
			}
		}
		write(compipe[1], &terminal, sizeof(char));
		wait(NULL);
		close(compipe[1]);
	}
	printf("%c: Shared memory has: %s\n", x, mem);
	munmap(mem, size);
	shm_unlink(mymemory);
	return 0;
}