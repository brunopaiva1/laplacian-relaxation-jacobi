#include "laplacian.h"
#include <iostream>
#include <cmath>

JacobiRelaxation::JacobiRelaxation(int rows, int cols, double tol, int max_interation)
    : rows(rows), cols(cols), tol(tol), max_interation(max_interation) {
        A = allocate_matrix(rows, cols);
        A_new = allocate_matrix(rows, cols);
}

JacobiRelaxation::~JacobiRelaxation(){
    deallocate_matrix(A, rows);
    deallocate_matrix(A_new, rows);
}

double** JacobiRelaxation::allocate_matrix(int rown, int cols){
    double** matrix = new double*[rows];
    for (int i = 0; i < rows; ++i){
        matrix[i] = new double[cols]();
    }
    return matrix;
}

void JacobiRelaxation::deallocate_matrix(double** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

void JacobiRelaxation::initialize() {
    double error = 1.0;
    int cont = 0;

    std::cout << "Jacobi relaxation Calculation: "
              << rows << " x " << cols << "mesh" << std::endl;

    while (error > tol && cont < max_interation) {
        error = 0.0;

        for(int j = 1; j < rows - 1; ++j){
            for (int i = 1; i < cols -1; ++i){
                A_new[j][i] = 0.25 * (A[j][i + 1] + A[j][i - 1] +
                                      A[j - 1][i] + A[j + 1][i]);
                error = std::max(error, std::fabs(A_new[j][i] - A[j][i]));
            }
        }

        double** temp = A;
        A = A_new;
        A_new = temp;

    }
}