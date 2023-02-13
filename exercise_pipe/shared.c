#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>

int main(int argc, char* argv[]) {
	int memory_size = 2048;
	char *mem = mmap(NULL, memory_size, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	
	if (fork() == 0)
	{
		strncat(mem, "abcd", 1);
	}
	else
	{
		wait(NULL);
	}
	printf("SHARED: %s\n", mem);

	return 0;
}