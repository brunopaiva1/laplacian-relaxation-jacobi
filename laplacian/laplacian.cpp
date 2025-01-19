#include "laplacian.h"
#include <iostream>
#include <cmath>

JacobiRelaxantion::JacobiRelaxantion(int rows, int cols, double tol, int max_interation)
    : rows(rows), cols(cols), tol(tol), max_interation(max_interation) {
        A = allocate_matrix(rows, cols);
        A_new = allocate_matrix(rows, cols);
    }

JacobiRelaxantion::~JacobiRelaxantion(){
    deallocate_matrix(A, rows);
    deallocate_matrix(A_new, rows);
}