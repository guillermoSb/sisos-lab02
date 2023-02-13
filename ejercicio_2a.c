/**
 * @file ejercicio_2a.c
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

int main(void) {
	int total_iterations = 1000000;
	clock_t c1;
	clock_t c2;

	c1 = clock();
	for (int i = 0; i < total_iterations; i++)
	{
	}
	for (int i = 0; i < total_iterations; i++)
	{
	}
	for (int i = 0; i < total_iterations; i++)
	{
	}
	c2 = clock();
	double time_difference = (double)c2 - c1;
	printf("Exec time: %f\n", time_difference);
	return 0;
}