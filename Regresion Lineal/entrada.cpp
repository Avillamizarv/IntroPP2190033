#include <iostream>
#include <fstream>
#include <vector>
#include <random>

int main() {
    size_t dataSize = 50; 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 10.0); // Rango de valores para X y y

    std::vector<double> X(dataSize);
    std::vector<double> y(dataSize);

    for (size_t i = 0; i < dataSize; ++i) {
        X[i] = dis(gen);
        y[i] = 2.0 * X[i] + dis(gen); 
    }

    std::ofstream outputFile("input.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return 1;
    }

    for (size_t i = 0; i < dataSize; ++i) {
        outputFile << X[i] << " " << y[i] << std::endl;
    }

    outputFile.close();

    std::cout << "Se han generado datos aleatorios y se han guardado en 'input.txt'" << std::endl;

    return 0;
}
