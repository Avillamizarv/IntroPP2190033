# Proyecto final 

## Regresión lineal

## Link del video en youtube: 
https://youtu.be/IEMx5UARpYQ 

### Integrantes:

Gysselis Vásquez

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


### Implementación en C++

Se generan los datos de input para el programa principal a través de otro programa (entrada.cpp) y se guardan en un archivo de texto.

Desde el programa principal (regression.cpp) se lee el txt de entrada previamente generado, se entrena el modelo con parámetros (epochs y learning rate) definidos y se guarda el modelo generado en un archivo de salida.

### Compilación y ejecución

La compilación y ejecución del programa se hizo en Guane, usando 4 como número de procesos. Para compilar se ejecuta el siguiente comando:

    g++ -std=c++11 regresion.cpp -o regresion 

Para ejecutar el programa se ejecuta:

    ./regresion

### Paralelización con OpenMP

Se utiliza la directiva 

   #pragma omp parallel for

para paralelizar el bucle for que entrena el modelo. Las directivas 

    #pragma omp atomic

se utilizan para asegurar que las operaciones de actualización de la pendiente y la intersección se realicen de manera atómica.

Se obtienen los siguientes resultados:

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/738e7e04-1fc1-4454-b45c-f57ac019008e)


### Paralelización con CUDA

Al hacer uso de CUDA con el programa original (sin paralelización con OMP) se obtienen los siguientes resultados:

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/2b84dccb-92fe-452f-a94c-a5ddd58fdba5)

Usando el código paralelizado con omp y con CUDA se obtiene lo siguiente:

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/e06b957d-f8fd-4c3d-b167-e2ef758ca02a)

Para compilar y ejecutar se ejecuta lo siguiente:

    export PATH=/opt/ohpc/pub/devtools/cuda/12.1/bin:$PATH
    nvcc -o Reg_Parall Reg_Parall.cu
    ./Reg_Parall
    
### Paralelización con MPI:

Se realiza la compilación con el siguiente comando:

    mpic++ RecressionMPI.cpp -o regresionmpi

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/5f485890-9687-4dd5-b7e1-fa023af6249e)


### Resultados

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/869975aa-bf61-4510-a25b-f461e1209a53)


### Conclusiones

De manera general observamos que la mejor opción para paralelizar algotimos de este tipo es CUDA, ya que reduce significamente los tiempos de ejecución en comparación a MPI u OMP. Esto se evidenció tanto para entradas pequeñas como para entradas bastante grandes. 






