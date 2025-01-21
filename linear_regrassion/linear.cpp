#include "linear.h"
#include <iostream>
#include <cstring>

LinearRegression::LinearRegression(int interations, double alphaN)
        : interations(interations), alphaN(alphaN) {}

LinearRegression::~LinearRegression() {}

void LinearRegression::fit(double** Y, double** X, double** w, int N, int D, int p){
    double** gradient = new double*[D];
    for (int i = 0; i < D; ++i) {
        gradient[i] = new double[p];
        std::memset(gradient[i], 0, p * sizeof(double));
    }
}