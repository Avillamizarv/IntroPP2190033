// C program to multiply two matrices
#include <stdio.h>
#include <stdlib.h>
//Agrego la biblioteca omp
#include <omp.h>

void multiplyMatrix(int R1, int C1, int R2,int C2,int m1[R1][C1], int m2[R2][C2])
{
	int result[R1][C2];

	printf("Matriz resultante:\n");

        // Se empieza a contabilizar el tiempo
        double inicio = omp_get_wtime();
	#pragma omp parallel for // Esto paraleliza el bucle externo (filas de la matriz resultante)
	for (int i = 0; i < R1; i++) {

		for (int j = 0; j < C2; j++) {
			result[i][j] = 0;
			for (int k = 0; k < R1; k++) {
				result[i][j] += m1[i][k] * m2[k][j];
			}
			printf("%d\t", result[i][j]);
		}
		printf("\n");
	}
    // Se termina de contabilizar el tiempo
    double fin = omp_get_wtime();
    printf("Tiempo gastado: %lf ms\n", (fin - inicio)*1000);
}

//Función para llena una matriz con números aleatorios dadas las dimensiones
void generarMatrizAleatoria(int R, int C, int m[R][C]) {
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            m[i][j] = rand() % 10; // Genera números aleatorios entre 0 y 10
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
}

//Función principal
int main()
{
    //Pido las dimensiones de las matrices por entrada de teclado
    int R1, R2, C1, C2;

    printf("Ingrese la cantidad de filas de la matriz 1: ");
    scanf("%d", &R1);

    printf("Ingrese la cantidad de columnas de la matriz 1: ");
    scanf("%d", &C1);

    printf("Ingrese la cantidad de filas de la matriz 2: ");
    scanf("%d", &R2);

    printf("Ingrese la cantidad de columnas de la matriz 2: ");
    scanf("%d", &C2);

    //Hago primero la validación de que coincidan las columnas de 1 con las filas de 2
	// if coloumn of m1 not equal to rows of m2
	if (C1 != R2) {
		printf("La cantidad de filas de la matriz 1 debe ser igual a la cantidad de columnas de la matriz 2");

		exit(EXIT_FAILURE);
	}

	//Declaro y lleno las matrices con números aleatorios
	int m1[R1][C1];
	int m2[R2][C2];
	printf("Matriz 1:\n");
	generarMatrizAleatoria(R1, C1, m1);
	printf("Matriz 2:\n");
	generarMatrizAleatoria(R2, C2, m2);

	// Function call
	//Le paso más parámetros (números de filas y columnas de cada matriz)
	multiplyMatrix(R1, C1, R2, C2, m1, m2);
	return 0;
}
