#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

class LinearRegression {
private:
    int interations;
    double alphaN;

public:
     LinearRegression(int iterations, double alphaN);
    ~LinearRegression();

    void fit(double** Y, double** X, double** w, int N, int D, int p);
};

#endif //LINEAR_REGRESSION_H
