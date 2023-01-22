#ifndef MATRIX_H
#define MATRIX_H


#include <stdbool.h>


typedef struct {
    double *data;
    int rows;
    int cols;
} Matrix;


Matrix *matrix_new(int rows, int cols);
void matrix_free(Matrix *m);
void matrix_set(Matrix *m, int row, int col, double value);
double matrix_get(Matrix *m, int row, int col);
void matrix_print(Matrix *m);
bool matrix_multiply(Matrix *a, Matrix *b, Matrix **c);
void matrix_transpose(Matrix *m, Matrix **t);
void matrix_add(Matrix *a, Matrix *b);
void matrix_subtract(Matrix *a, Matrix *b);
void matrix_skalar_multiply(Matrix *m, double skalar);
Matrix* matrix_skalar_multiply_ret(Matrix *m, double skalar);
bool matrix_invert(Matrix *m, Matrix **i);
void print_theta_func(Matrix *theta);
void linear_regression();
void gradient_descent(int count_xs, int features, int iterations, Matrix *theta, Matrix **x, Matrix *y, double alpha);


#endif