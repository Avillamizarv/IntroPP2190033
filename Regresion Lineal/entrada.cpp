#include <iostream>
#include <fstream>
#include <vector>
#include <random>

int main() {
    // Tamaño de los datos a generar
    size_t dataSize = 50;

    // Inicializar un generador de números aleatorios
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 10.0); // Rango de valores para X y y

    // Vectores para almacenar los datos generados
    std::vector<double> X(dataSize);
    std::vector<double> y(dataSize);

    // Generar datos aleatorios para X y calcular y basándose en una relación lineal
    for (size_t i = 0; i < dataSize; ++i) {
        X[i] = dis(gen);
        y[i] = 2.0 * X[i] + dis(gen);
    }

    // Abrir un archivo de salida para guardar los datos generados
    std::ofstream outputFile("input.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return 1;
    }

    // Escribir los datos generados en el archivo de salida
    for (size_t i = 0; i < dataSize; ++i) {
        outputFile << X[i] << " " << y[i] << std::endl;
    }

    // Cerrar el archivo de salida
    outputFile.close();

    std::cout << "Se han generado datos aleatorios y se han guardado en 'input.txt'" << std::endl;

    return 0;
}
