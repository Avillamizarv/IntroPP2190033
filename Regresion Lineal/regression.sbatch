//CUDA:
export PATH=/opt/ohpc/pub/devtools/cuda/12.1/bin:$PATH
nvcc -o Reg_Parall Reg_Parall.cu
./Reg_Parall

//OpenMP:
g++ -std=c++11 Reg_OMP.cpp -o Reg_OMP
./Reg_OMP

//MPI:
module load devtools/mpi/openmpi/3.1.4
mpic++ -std=c++11 Reg_MPI.cpp -o Reg_MPI
mpirun -np 4 --mca mpi_cuda_support 0 ./Reg_MPI
