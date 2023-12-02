#include <iostream>
#include <fstream>
#include <vector>

// Estructura para almacenar los resultados del modelo  de la regresión lineal
struct LinearRegressionResult {
    double slope;     // Pendiente
    double intercept;  // Intersección
};

// Función para predecir el resultado usando los resultados de la regresión lineal
double predict(const double& feature, const LinearRegressionResult& result) {
    return result.slope * feature + result.intercept;
}

// Función para entrenar el modelo de regresión lineal
LinearRegressionResult trainModel(const std::vector<double>& X, const std::vector<double>& y, int epochs, double learningRate) {
    size_t numSamples = X.size();

    double slope = 0.0;
    double intercept = 0.0;

    // Iterar a través de los epochs
    for (int epoch = 0; epoch < epochs; ++epoch) {
        for (size_t i = 0; i < numSamples; ++i) {
            // Realizar una predicción
            double y_pred = predict(X[i], {slope, intercept});
            
            // Calcular el error
            double error = y_pred - y[i];

            // Actualizar los parámetros (pendiente e intersección) utilizando el descenso de gradiente
            slope -= learningRate * error * X[i];
            intercept -= learningRate * error;
        }
    }

    return {slope, intercept};
}

int main() {
    
    // Abrir el archivo de entrada
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de entrada." << std::endl;
        return 1;
    }

    // Vectores para almacenar los datos de entrada (X) y salida (y)
    std::vector<double> X;
    std::vector<double> y;
    double value;

    
    // Leer los datos del archivo de entrada
    while (inputFile >> value) {
        X.push_back(value);
        inputFile >> value;
        y.push_back(value);
    }

    inputFile.close();

    
    // Configurar los parámetros del modelo
    int epochs = 1000;
    double learningRate = 0.01;
    // Entrenar el modelo de regresión lineal
    LinearRegressionResult result = trainModel(X, y, epochs, learningRate);

    // Escribir los resultados en el archivo de salida
    std::ofstream outputFile("output.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error al abrir el archivo de salida." << std::endl;
        return 1;
    }

    outputFile << "Pendiente (m): " << result.slope << std::endl;
    outputFile << "Intersección (b): " << result.intercept << std::endl;

    outputFile.close();

    std::cout << "El modelo se ha guardado en 'output.txt'" << std::endl;

    return 0;
}
