# Proyecto final 

## Regresión lineal

### Integrantes:

Gysselis Vásquez.

César Hurtado

Adriana Villamizar 


En este directorio se encuentra el planteamiento y desarrollo del proyecto final de la materia Introducción a la computación paralela. El tema que se trata es Aprendizae automático paralelo, específicamente, un algoritmo de regresión lineal.

## Regresión Lineal

La Regresión Lineal es un método estadístico para modelar las relaciones entre una variable dependiente y un conjunto dado de variables independientes. 

Existen dos tipos de regresión lineal:

### Regresión lineal simple:

Es un método para predecir una respuesta utilizando una única característica. Es uno de los modelos de aprendizaje automático más básicos 
Trata de encontrar una función lineal que prediga el valor de la respuesta (y) con la mayor precisión posible en función de la característica o variable independiente (x).

Para crear el modelo, se debe "aprender" o estimar los valores de los coeficientes de regresión b_0 y b_1, una vez estimados estos coeficientes, se puede usar el modelo para predecir las respuestas de otros casos.


### Regresión lineal múltiple:

Intenta modelar la relación entre dos o más características y una respuesta ajustando una ecuación lineal a los datos observados.

Considere un conjunto de datos con p características (o variables independientes) y una respuesta (o variable dependiente).
Además, el conjunto de datos contiene n filas/observaciones. Dada X como una matriz de características:

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/14ef98b1-1c02-4157-ab4c-0ce961a6e653)

 y un vector con las respuestas para cada observación:

 ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/d75826d0-08f8-4590-a794-85d0a35211c6)

 La línea de regresión para p características es representada como:
 
 ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/02ac499a-d5a6-44b9-9f0e-9ef4d7f44163)

donde h(x_i) es el valor predecido para cada caso y b_0, b_1, ... b_p son los coeficientes de regresión.


De forma resumida, el modelo de regresión puede representarse como:

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/0401559e-80a9-4f80-bd6d-3b38e3628aaa)


### Algoritmo

### Implementación en C

### Compilación y ejecución

### Paralelización con OpenMP

### Resultados

### Conclusiones



Mientras que, al ejecutar la solución con omp, el tiempo empleado es de 2.000093 ms

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/aa99526f-37da-4d7e-af81-4b22cc88f85f)



