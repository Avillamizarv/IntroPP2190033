#!/bin/bash
#SBATCH --job-name=MPI
#SBATCH --nodes=2
#SBATCH --cpus-per-task=4

#SBATCH --output=output_heatEquation.txt%j.out
#SBATCH --error=error_heatEquation.err%j.err


##Cargar el módulo de MPI

module load devtools/mpi/openmpi/3.1.4


##Compilación con optimización -03, y flags para advertencias y debug

CC=mpicc
CCFLAGS=-O3 -Wall
LDFLAGS=
LIBS=-lpng -lm

EXE=heat_mpi
OBJS=core.o setup.o utilities.o io.o main.o
OBJS_PNG=pngwriter.o

$CC $CCFLAGS -c core.c -o core.o
$CC $CCFLAGS -c setup.c -o setup.o
$CC $CCFLAGS -c utilities.c -o utilities.o
$CC $CCFLAGS -c io.c -o io.o
$CC $CCFLAGS -c main.c -o main.o
$CC $CCFLAGS -c pngwriter.c -o pngwriter.o

$CC $CCFLAGS $OBJS $OBJS_PNG -o $EXE $LDFLAGS $LIBS

##Ejecución

mpirun -np 4 ./heat_mpi
