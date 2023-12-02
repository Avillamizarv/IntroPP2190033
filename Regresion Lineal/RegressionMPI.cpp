#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <mpi.h>

struct LinearRegressionResult {
    double slope;    
    double intercept;  
};

double predict(const double& feature, const LinearRegressionResult& result) {
    return result.slope * feature + result.intercept;
}

LinearRegressionResult trainModel(const std::vector<double>& X, const std::vector<double>& y, int epochs, double learningRate, int world_rank, int world_size) {
    size_t numSamples = X.size();

    double slope = 0.0;
    double intercept = 0.0;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = world_rank; i < numSamples; i += world_size) {
            double y_pred = predict(X[i], {slope, intercept});

            double error = y_pred - y[i];

            slope -= learningRate * error * X[i];
            intercept -= learningRate * error;
        }
    }

    return {slope, intercept};
}

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

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
    LinearRegressionResult result = trainModel(X, y, epochs, learningRate, world_rank, world_size);

    if (world_rank == 0) {
        std::ofstream outputFile("output.txt");
        if (!outputFile.is_open()) {
            std::cerr << "Error al abrir el archivo de salida." << std::endl;
            return 1;
        }

        outputFile << "Pendiente (m): " << result.slope << std::endl;
        outputFile << "IntersecciÃ³n (b): " << result.intercept << std::endl;

        outputFile.close();

        std::cout << "El modelo se ha guardado en 'output.txt'" << std::endl;

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        std::cout << "Tiempo de ejecución: " << elapsed.count() << "s" << std::endl;
    }

    MPI_Finalize();

    return 0;
}
