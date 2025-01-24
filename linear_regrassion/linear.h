#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include <omp.h>

class LinearRegression {
private:
    int interations;
    double alphaN;

public:
     LinearRegression(int iterations, double alphaN);
    ~LinearRegression();

    void fit(double** Y, double** X, double** w, int N, int D, int p, int thread_count);
};

#endif //LINEAR_REGRESSION_H
