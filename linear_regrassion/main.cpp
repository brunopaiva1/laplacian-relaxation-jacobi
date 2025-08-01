/**
Compilar regressão linear: g++ -o linear_regression main.cpp linear.cpp
executar: ./linear_regression --samples 100000 --features 5 --functions 3 --iterations 15
**/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cstring>
#include <iomanip> 
#include "linear.h"

double** allocateMatrix(int rows, int cols) {
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        matrix[i] = new double[cols];
    }
    return matrix;
}

void freeMatrix(double** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void generateRandomMatrix(double** matrix, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = static_cast<double>(rand()) / RAND_MAX;
        }
    }
}

int main(int argc, char* argv[]) {
    int samples = 200000;
    int features = 10;
    int functions = 4;
    int interations = 20;
    int thread_count = 4; // Número de threads (por exemplo, 4)

    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--samples" && i + 1 < argc) samples = std::stoi(argv[++i]);
        else if (std::string(argv[i]) == "--features" && i + 1 < argc) features = std::stoi(argv[++i]);
        else if (std::string(argv[i]) == "--functions" && i + 1 < argc) functions = std::stoi(argv[++i]);
        else if (std::string(argv[i]) == "--interations" && i + 1 < argc) interations = std::stoi(argv[++i]);
        else if (std::string(argv[i]) == "--threads" && i + 1 < argc) thread_count = std::stoi(argv[++i]); // Aceitar valor de threads via argumento
    }

    double alphaN = 0.01 / samples;

    double** w = allocateMatrix(features, functions);
    double** points = allocateMatrix(samples, features);
    double** labels = allocateMatrix(samples, functions);

    std::srand(0);
    generateRandomMatrix(points, samples, features);
    generateRandomMatrix(labels, samples, functions);
    for (int i = 0; i < features; ++i) {
        std::memset(w[i], 0, functions * sizeof(double));
    }

    LinearRegression lr(interations, alphaN);

    auto start = std::chrono::high_resolution_clock::now();
    lr.fit(labels, points, w, samples, features, functions, thread_count);
    auto end = std::chrono::high_resolution_clock::now();

    double selftimed = std::chrono::duration<double>(end - start).count();
    std::cout << "SELFTIMED " << selftimed << " seconds\n";

    double checksum = 0.0;
    for (int i = 0; i < features; ++i) {
        for (int j = 0; j < functions; ++j) {
            checksum += w[i][j];
        }
    }
    std::cout << "Checksum: " << std::fixed << std::setprecision(16) << checksum << "\n";
    freeMatrix(w, features);
    freeMatrix(points, samples);
    freeMatrix(labels, samples);

    return 0;
}
