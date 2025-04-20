#include "linear.h"
#include <iostream>
#include <omp.h>
#include <cstring>

LinearRegression::LinearRegression(int interations, double alphaN)
        : interations(interations), alphaN(alphaN) {}

LinearRegression::~LinearRegression() {}

void LinearRegression::fit(double** Y, double** X, double** w, int N, int D, int p, int thread_count) {
    double* gradient = new double[D * p];
    
    for (int it = 0; it < interations; ++it) {
        #pragma omp parallel for num_threads(thread_count)
        for (int i = 0; i < D * p; ++i) {
            gradient[i] = 0.0;
        }

        #pragma omp parallel for collapse(2) reduction(+:gradient[:D*p]) num_threads(thread_count)
        for (int i = 0; i < N; ++i) {
            for (int k = 0; k < p; ++k) {
                double prediction = 0.0;
                #pragma omp simd
                for (int d = 0; d < D; ++d) {
                    prediction += X[i][d] * w[d][k];
                }

                for (int j = 0; j < D; ++j) {
                    gradient[j * p + k] += X[i][j] * (prediction - Y[i][k]);
                }
            }
        }

        #pragma omp parallel for collapse(2) num_threads(thread_count)
        for (int j = 0; j < D; ++j) {
            for (int k = 0; k < p; ++k) {
                w[j][k] -= alphaN * gradient[j * p + k];
            }
        }
    }

    delete[] gradient;
}
