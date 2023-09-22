# OpenMP
En este directorio se encuentra implementación de un programa para multiplicación de matrices en lenguaje C secuencial (multiplyMatrix.c) y la misma solución pero con programación paralela (omp_multiplyMatrix.c) y el análisis comparativo entre los tiempos de ejecución de ambas soluciones.
Al ejecutar la solución programada secuencialmente, el tiempo de ejecución es de  3.778 s
![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/c82631fa-5c0d-4ba4-bd35-633d33440ad4)

Mientras que, al ejecutar la solución con omp, el tiempo empleado es de 2.648 s
![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/504578a2-6565-466f-8a24-e26cfb85a9fb)


Evidentemente, hacerlo de forma paralela tiene una gran ventaja de tiempo.

Ahora, si se hace la misma prueba aumentando la cantidad de datos, es decir, con matrices de mayor dimensión (100x100 y 100 x 200), los resultados son los siguientes:
Secuencial:  12.972 s
Paralelo:   12.964 s
En este caso, se reduce un poco la diferencia entre tiempos de ejecución.
