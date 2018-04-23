#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

unsigned long long int factorial(unsigned int i) {
	if(i <= 1) {
		return 1;
	}
	return i * factorial(i - 1);
}

int  main() {
	//Factorial de 10
	int numero = 10;
	//padre
	int p = getpid();

	//Crea 3 hijos
	for (int i = 1; i < 4; i++) {
		int hijo = fork();
		if (hijo == 0) {
			printf("Identificador del hijo #%d\t. resultado de 10!: = %lu\t\n", i, factorial(numero));
		} else if (hijo < 0){
			printf("Error en la creación del hijo\n");
		} else {
			waitpid(hijo, 0, 0);
		}
	}
	return 0;
}