/**
 * @file ejercicio_4b.c
 * @author Guillermo
 * @brief 
 * @version 0.1
 * @date 2023-02-08
 * 
 * @copyright Copyright (c) 2023
 * 
 * Cree un programa en C que ejecute cuatro fork()s consecutivos.
 */

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <stdbool.h> 


int main(void) {
	pid_t p1;

	p1 = fork();

	if((double)p1 == 0) {
		printf("Hello from child %d\n", getpid());
		for (int i = 0; i < 80000000; i++)
		{
			printf(" %d\n", i);
		}
		
	} else {
		while (true)
		{
			printf("Hello from parent %d\n", getpid());
		}
	}
	return 0;
}