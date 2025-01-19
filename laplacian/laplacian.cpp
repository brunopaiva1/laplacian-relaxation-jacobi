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