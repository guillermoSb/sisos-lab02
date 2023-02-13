/**
 * @file ejercicio_1a.c
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
	int p1 = fork();
	int p2 = fork();
	int p3 = fork();
	int p4 = fork();
	int pid = getpid();
	printf("Hello from %d\n", pid);	// Verificar que se crean 16 procesos.
	return 0;
}