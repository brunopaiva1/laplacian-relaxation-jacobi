#ifndef JACOBIRELAXATION_H
#define JACOBIRELAXATION_H

#include <string>

class JacobiRelaxation {
private:
    int rows, cols; // linhas e colunas para dimensão da malha
    double tol;
    int max_interation;
    double** A;
    double** A_new;

    double** allocate_matrix(int rows, int cols);
    void deallocate_matrix(double** matrix, int rows);

public:
    JacobiRelaxation(int rowns, int cols, double tol, int max_interation);
    ~JacobiRelaxation();

    void initialize();
    void solve();
    void print_results() const;
};

#endif // JACOBIRELAXATION_H