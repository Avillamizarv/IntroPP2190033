#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <cuda_runtime.h>
#include <device_launch_parameters.h>

// Estructura para almacenar los resultados de la regresión
struct LinearRegressionResult {
    double slope;      // Pendiente (m)
    double intercept;  // Intersección (b)
};

// Función para predecir el valor con un modelo de regresión lineal
_host_ _device_ double predict(const double& feature, const LinearRegressionResult& result) {
    return result.slope * feature + result.intercept;
}

// Kernel para el entrenamiento del modelo en paralelo con CUDA
_global_ void trainModelKernel(const double* X, const double* y, size_t numSamples,
                                 int epochs, double learningRate, LinearRegressionResult* result) {
    size_t idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < numSamples) {
        double slope = result->slope;
        double intercept = result->intercept;

        for (int epoch = 0; epoch < epochs; ++epoch) {
            // Predicción
            double y_pred = predict(X[idx], {slope, intercept});

            // Cálculo del error
            double error = y_pred - y[idx];

            // Actualización de pesos
            slope -= learningRate * error * X[idx];
            intercept -= learningRate * error;
        }

        // Almacenar resultados finales en el resultado compartido
        result->slope = slope;
        result->intercept = intercept;
    }
}

// Función para entrenar el modelo utilizando CUDA
LinearRegressionResult trainModelCUDA(const std::vector<double>& X, const std::vector<double>& y,
                                       int epochs, double learningRate) {
    size_t numSamples = X.size();

    // Copiar datos desde la CPU a la GPU
    double* d_X;
    double* d_y;
    cudaMalloc((void**)&d_X, numSamples * sizeof(double));
    cudaMalloc((void**)&d_y, numSamples * sizeof(double));
    cudaMemcpy(d_X, X.data(), numSamples * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(d_y, y.data(), numSamples * sizeof(double), cudaMemcpyHostToDevice);

    // Inicializar resultado en la GPU
    LinearRegressionResult result;
    result.slope = 0.0;
    result.intercept = 0.0;

    LinearRegressionResult* d_result;
    cudaMalloc((void**)&d_result, sizeof(LinearRegressionResult));
    cudaMemcpy(d_result, &result, sizeof(LinearRegressionResult), cudaMemcpyHostToDevice);

    // Configurar el tamaño del bloque y la cuadrícula
    size_t blockSize = 256;
    size_t gridSize = (numSamples + blockSize - 1) / blockSize;

    // Ejecutar el kernel en la GPU
    trainModelKernel<<<gridSize, blockSize>>>(d_X, d_y, numSamples, epochs, learningRate, d_result);

    // Copiar resultados de la GPU a la CPU
    cudaMemcpy(&result, d_result, sizeof(LinearRegressionResult), cudaMemcpyDeviceToHost);

    // Liberar memoria en la GPU
    cudaFree(d_X);
    cudaFree(d_y);
    cudaFree(d_result);

    return result;
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
        return 1;
    }

    std::vector<double> X;
    std::vector<double> y;
    double value;

    while (inputFile >> value) {
        X.push_back(value);
        inputFile >> value;
        y.push_back(value);
    }

    inputFile.close();

    int epochs = 1000;
    double learningRate = 0.01;
    LinearRegressionResult result = trainModelCUDA(X, y, epochs, learningRate);

    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return 1;
    }

    outputFile << "Pendiente (m): " << result.slope << std::endl;
    outputFile << "Intersección (b): " << result.intercept << std::endl;

    outputFile.close();

    std::cout << "El modelo se ha guardado en 'output.txt'" << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo de ejecución: " << elapsed.count() << "s" << std::endl;

    return 0;
}
