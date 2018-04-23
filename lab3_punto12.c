#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	//Creación del hijo
	int pid = fork();

	if (pid == 0) {
		//Ruta del proceso
		char ruta[20];
		char args[20];
		printf("Por favor Ingrese la ruta del proceso a ejecutar: ");
		scanf("%s", ruta);
		printf("Por favor Ingrese los argumentos: ");
		scanf("%s", args);
		//Se asigna ruta y argumentos al nuevo exec
		char const *argv[] = args;
		execv(ruta,argv);
	} else if (pid < 0){
		printf("Error en el proceso\n");
	} else {
		waitpid(pid,0,0); // Espera al hijo
	}
	return 0;
}