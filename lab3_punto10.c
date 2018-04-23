#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

	int hijoDerecho, hijoIzquierdo;
	//Crea al padre
	int p = getpid();
	printf("Hilo padre: \t%d\t padre del padre: \t%d\n" , p, getppid());

	for(int i = 0; i < 2; i++) {
		//Crea al hijo derecho
		hijoDerecho = fork();

		if(hijoDerecho == 0) {
			//Verifica si nos encontramos en primer nivel
			printf(" identificador del proceso: \t%d\t  padre: \t%d\n", getpid(), getppid());
			//Crea al hijo izquierdo
			hijoIzquierdo = fork();

			if(hijoIzquierdo == 0) {
				//Si lo crea
				//Imprime su info
				printf("identificador del proceso: \t%d\t  padre: \t%d\n", getpid(), getppid());
			} else if (hijoIzquierdo < 0){
				//Fallo la creacion del hijo Izq
				printf("Falla en creación del hilo izquierdo\n");
			} else {
				break;
			}
		} else if (hijoDerecho == 0 ) {
			//Verifica si estamos en segundo nivel
			printf("identificador del proceso: \t%d\t padre: \t%d\n", getpid(), getppid());
			//Crea al nieto Izq
			int nietoIzquierdo = fork();

			if (nietoIzquierdo == 0) {
				printf("identificador del proceso: \t%d\t padre: \t%d\n", getpid(), getppid());
				//Crea al nieto Derecho
				int nietoDerecho = fork();

				if (nietoDerecho == 0) {
					printf("identificador del proceso: \t%d\t padre: \t%d\n", getpid(), getppid());
				} else if (nietoDerecho < 0) {
					printf("Falla en la creación del nieto derecho\n");
				} else {
					//Espera ambos nietos
					waitpid(nietoDerecho, 0, 0);
					waitpid(nietoIzquierdo, 0, 0);
				}
			} else if (hijoIzquierdo < 0) {
				//Fallo la creacion del hijo Izquierdo
				printf("Falla en la creación del hijo izquierdo\n");
			} else {
				break;
			}
		} else if (hijoDerecho < 0){
			//Falló la creacion del hijo Derecho
			printf("Falla en la creación del hijo derecho\n");
		} else {
			//Espera ambos hijos
			waitpid(hijoDerecho, 0, 0);
			waitpid(hijoIzquierdo, 0, 0);
			return 0;
		}
	}
}