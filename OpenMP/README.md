# OpenMP
En este directorio se encuentra implementación de un programa para multiplicación de matrices en lenguaje C secuencial (multiplyMatrix.c) y la misma solución pero con programación paralela (omp_multiplyMatrix.c) y el análisis comparativo entre los tiempos de ejecución de ambas soluciones.

Al ejecutar la solución programada secuencialmente, el tiempo de ejecución es de   3.000000 ms
![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/daad72b5-d6d0-4730-9dfa-a0e8e618ba35)


Mientras que, al ejecutar la solución con omp, el tiempo empleado es de 2.000093 ms
![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/aa99526f-37da-4d7e-af81-4b22cc88f85f)



Evidentemente, hacerlo de forma paralela tiene ventaja de tiempo.


Ahora, si se hace la misma prueba aumentando la cantidad de datos, es decir, con matrices de mayor dimensión (100x100 y 100 x 200), los resultados son los siguientes:

Secuencial:  15 ms
![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/3034fdd0-98a2-453c-aad9-a90224f7ffdc)

Paralelo:   4.999876 ms
![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/f3bf5c5e-5376-4a4a-a7a3-6ef4b8e7a151)

En este caso, se hace un poco más notable la diferencia en los tiempos, evidenciando que a medida que crece la data, el rendimiento en paralelo es mejor.
