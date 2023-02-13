/**
 * @file ejercicio_1b.c
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


int main(void) {
	for (int i = 0; i < 4; i++)
	{
		int p = fork();
	}
	int pid = getpid();
	printf("Hello from %d\n", pid);	// Verificar que se crean 16 procesos.
	return 0;
}