#ifndef JACOBIRELAXATION_H
#define JACOBIRELAXATION_H

#include <string>

class JacobiRelaxantion {
private:
    int rows, cols; // linhas e colunas para dimensão da malha
    double tol;
    int max_interation;
    double** A;
    double** A_new;
};

#endif // JACOBIRELAXATION_H