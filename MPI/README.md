# Solución evaluación 2: MPI

Integrantes:

Adriana Villamizar Vera - 2190033

Gysselis Vasquez Garcés 

INTRODUCCIÓN


MPI es un estándar de comunicación utilizado en programación paralela y computación de alto rendimiento para interconectar múltiples procesadores o nodos en un sistema distribuido. MPI permite que los procesadores se comuniquen y coordinen entre sí, lo que es fundamental para realizar cálculos complejos y intensivos en datos en sistemas distribuidos y supercomputadoras.


En el presente taller se realizan, con MPI, pruebas y modificaciones sobre un programa de referencia para la solución de la ecuación de calor mediante el método de Laplace por diferencias finitas. El objetivo es buscar una optimización del programa dado y comparar los resultados de las diferentes alternativas utilizadas.


Para una mayor comprensión del problema que se soluciona, cabe mencionar que la ecuación del calor, también conocida como la ecuación de difusión, es una ecuación diferencial parcial que describe cómo se propaga el calor en un medio. La ecuación general para la conducción del calor en una dimensión espacial y en función del tiempo (T(x, t)T(x,t)) es:

![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/4a0a5e8f-d0c2-4b43-b28b-82ebed1547d3)

Para resolver esta ecuación usando el método de las diferencias finitas, se discretiza tanto el espacio como el tiempo, este método proporciona una aproximación numérica a la solución de la ecuación del calor y se utiliza ampliamente en simulaciones computacionales para estudiar la propagación del calor en diversos contextos, como la física de materiales, la ingeniería térmica y muchos otros campos relacionados con la transferencia de calor.


DESARROLLO.

Estando conectados a guane (ssh guane):


1. Inicialmente descargamos el archivo .zip que contiene el programa en C, lo copiamos en el espacio de guane y lo descomprimimos con el siguiente comando:

      unzip  MPI-master-heat-equation-c.zip
   
2.  Nos ubicamos en un nodo:

      srun -n 8 --pty /bin/bash
   
3. Cargamos el módulo de mpi:

     module load devtools/mpi/openmpi/3.1.4
   
4.  Nos ubicamos en la subcarpeta /heat-equation/c que se encuentra dentro de la carpeta resultante de descomprimir el archivo cargado en el paso 1.
  
5.  Ejecutamos el comando "make" con el cual se compilará el programa con las opciones que se encuentran dentro del archivo Makefile. Originalmente se compila con opción de optimización -03 y el flag de mostrar los warnings activado.

   ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/66f545c3-69cc-4b95-87d7-83b96f8b11ed)

   
6.  Ejecutamos el programa con el siguiente comando (con 2 procesos):

        mpirun -np 2 ./heat_mpi
      
   ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/a51b0db4-8f1a-4b88-a467-bf8271c186a1)
      
        En este caso el tiempo fue de: 36.964 sg
  
7.  Ahora, hacemos la ejecución usando el campo inicial con el archivo  bottle.dat:

         mpirun -np 2 ./heat_mpi bottle.dat
      
   ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/7aa1a7f5-fc28-4266-944b-498b13830810)
      
         En este caso el tiempo fue de: 37.401 sg
 
8.  Probamos dando el número de pasos de tiempo:

          mpirun -np 2 ./heat_mpi bottle.dat 1000
      
   ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/83eb4fb1-a8a5-42a8-baae-2b6fe7555f0a)
      
      
          En este caso el tiempo fue de: 75.787  sg
  
9.  También hacemos la ejecución dando las dimensiones y pasos de tiempo del patrón predeterminado:

          mpirun -np 2 ./heat_mpi 800 800 1000
          
   ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/098b58bc-a20e-4b25-baa3-806b0f5a8056)
      
          En este caso el tiempo fue de: 76.758 sg
    
10. Cada una de las anteriores ejecuciones produce una serie de imagenes en formato PNG, a continuación se muestran algunas de ellas correspondientes a las ejecuciones con mejor y peor desempeño respectivamente.

          Mejor desemepeño (pt 6):
          
    ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/d706faa8-99b1-4ef9-8035-b520bcaa863e)
    ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/690b86ff-2b65-4e50-8e5d-4e93ccf9247a)
    ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/bfaf56e6-8d9b-42b8-9193-cf097db63583)
      
      
          Peor desempeño (pt 9):
      
    ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/efacadfe-20a6-4589-8672-46ccb2a2f0f8)
    ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/6e91114d-3ad2-4e9e-8ba1-693bb1933a0f)
    ![image](https://github.com/Avillamizarv/IntroPP2190033/assets/108444542/f636bdad-618f-4738-8444-83bfbb9107b7)
          

    MODIFICACIONES
    
11. Si cambiamos el número de procesos a la hora de ejecutar el programa, vemos una diferencia en los tiempos de ejecución, los resultados quedan de la siguiente manera:

            X(# prcs)-------->T(sg)
      
            2-----------------36.964
          
            4-----------------5.202
          
            8-----------------63.902
    

          El mejor desempeño se obtiene cuando se utilizan 4 procesos.
    
13. Si cambiamos la opción de optimización a la hora de compilar (abriendo el archivo Makefile y cambiando -O3 por cada una de las distintas opciones), tenemos los siguientes resultados:

          Opción de compilación ----------> T(sg)
      
          ninguna--------------------------21.554
          
          -O1------------------------------39.441
          
          -O2------------------------------9.523
          
          -O3------------------------------5.202
          
      
          La mejor opción de optimización en la compilación es la -O3, es decir, la que ya viene en el programa original
          
15. 



