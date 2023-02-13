/**
 * @file ejercicio_2b.c
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

int main(void) {
	pid_t p1;
	pid_t p2;
	pid_t p3;
	clock_t c1;
	clock_t c2;
	c1 = clock();
	p1 = fork();
	int total_iterations = 1000000;


	if ((int)p1 == 0)
	{
		// From child
		p2 = fork();
		if ((int)p2 == 0)
		{
			p3 = fork();
			if ((int)p3 == 0)
			{
				for (int i = 0; i < total_iterations; i++)
				{
				}
				printf("Bisnieto ha terminado \n");
			}
			else
			{
				for (int i = 0; i < total_iterations; i++)
				{
				}
				wait(NULL);	// Esperar al bisnieto
				printf("Nieto ha terminado \n");
			}
		} else {
			for (int i = 0; i < total_iterations; i++)
			{
			}
			wait(NULL);
			printf("Hijo ha terminado\n");
		}
	} else {
		wait(NULL);
		printf("Padre ha terminado\n");
		c2 = clock();
		double time_difference = (double)c2 - c1;
		printf("Exec time: %f\n", time_difference);
	}

	return 0;
}