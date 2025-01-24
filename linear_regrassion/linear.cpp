#include "linear.h"
#include <iostream>
#include <cstring>
#include <omp.h>

LinearRegression::LinearRegression(int interations, double alphaN)
        : interations(interations), alphaN(alphaN) {}

LinearRegression::~LinearRegression() {}

void LinearRegression::fit(double** Y, double** X, double** w, int N, int D, int p, int thread_count){
    double** gradient = new double*[D];
# pragma omp parallel for num_threads(thread_count)
    for (int i = 0; i < D; ++i) {
        gradient[i] = new double[p];
        std::memset(gradient[i], 0, p * sizeof(double));
    }
# pragma omp parallel for
    for (int it = 0; it < interations; ++it) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < D; ++j) {
                for (int k = 0; k < p; ++k) {
                    double prediction = 0.0;
                    for (int d = 0; d < D; ++d) {
                        prediction += X[i][d] * w[d][k];
                    }
                    gradient[j][k] += X[i][j] * (prediction - Y[i][k]);
                }
            }
        }
        for (int j = 0; j < D; ++j) {
            for (int k = 0; k < p; ++k) {
                w[j][k] -= alphaN * gradient[j][k];
            }
        }
        for (int i = 0; i < D; ++i) {
            std::memset(gradient[i], 0, p * sizeof(double));
        }
    }
    for (int i = 0; i < D; ++i) {
        delete[] gradient[i];
    }
    delete[] gradient;
}