#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <omp.h>

struct LinearRegressionResult {
    double slope;    
    double intercept;  
};

double predict(const double& feature, const LinearRegressionResult& result) {
    return result.slope * feature + result.intercept;
}

LinearRegressionResult trainModel(const std::vector<double>& X, const std::vector<double>& y, int epochs, double learningRate) {
    size_t numSamples = X.size();

    double slope = 0.0;
    double intercept = 0.0;

    for (int epoch = 0; epoch < epochs; ++epoch) {

        //Se agrega la notación de paralelización con omp
        #pragma omp parallel for
        for (size_t i = 0; i < numSamples; ++i) {
            double y_pred = predict(X[i], {slope, intercept});

            double error = y_pred - y[i];

            #pragma omp atomic
            slope -= learningRate * error * X[i];

            #pragma omp atomic
            intercept -= learningRate * error;
        }
    }

    return {slope, intercept};
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
    LinearRegressionResult result = trainModel(X, y, epochs, learningRate);

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

    return 0;
}
