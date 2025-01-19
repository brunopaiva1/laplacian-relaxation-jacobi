#include "laplacian.h"
#include <iostream>

int main() {
    int rows = 512;
    int cols = 512;
    double tol = 1.0e-6;
    int max_interation = 1000;

    JacobiRelaxation jacobi(rows, cols, tol, max_interation);

    jacobi.initialize();
    jacobi.solve();
    // jacobi.print_results();

    return 0;
}