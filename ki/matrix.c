#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matrix.h"


Matrix *matrix_new(int rows, int columns)
{
    Matrix *m = malloc(sizeof(Matrix));
    m->rows = rows;
    m->cols = columns;
    m->data = calloc(sizeof(double) * rows * columns, sizeof(double));
    return m;
}

void matrix_free(Matrix *m)
{
    free(m->data);
    free(m);
}

void matrix_set(Matrix *m, int row, int col, double value)
{
    m->data[row * m->cols + col] = value;
}

double matrix_get(Matrix *m, int row, int col)
{
    return m->data[row * m->cols + col];
}

void matrix_print(Matrix *m)
{
    printf("[");
    for (int i = 0; i < m->rows; i++)
    {
        printf("[");
        for (int j = 0; j < m->cols; j++)
        {
            printf("%f", m->data[i * m->cols + j]);
            if (j < m->cols - 1)
            {
                printf(", ");
            }
        }
        printf("]");
        if (i < m->rows - 1)
        {
            printf(", \n ");
        }
    }
    printf("]");
}

bool matrix_multiply(Matrix *a, Matrix *b, Matrix **c)
{
    if (a->cols != b->rows)
    {
        printf("Error: Matrix dimensions do not match");
        return false;
    }
    *c = matrix_new(a->rows, b->cols);
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < b->cols; j++)
        {
            double sum = 0;
            for (int k = 0; k < a->cols; k++)
            {
                sum += matrix_get(a, i, k) * matrix_get(b, k, j);
            }
            matrix_set(*c, i, j, sum);
        }
    }
    return true;
}

void matrix_transpose(Matrix *m, Matrix **t)
{
    *t = matrix_new(m->cols, m->rows);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            matrix_set(*t, j, i, matrix_get(m, i, j));
        }
    }
}

void matrix_add(Matrix *a, Matrix *b)
{
    if (a->rows != b->rows || a->cols != b->cols)
    {
        printf("Error: Matrix dimensions do not match");
        return;
    }
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            matrix_set(a, i, j, matrix_get(a, i, j) + matrix_get(b, i, j));
        }
    }
}

void matrix_subtract(Matrix *a, Matrix *b)
{
    if (a->rows != b->rows || a->cols != b->cols)
    {
        printf("Error: Matrix dimensions do not match");
        return;
    }
    for (int i = 0; i < a->rows; i++)
    {
        for (int j = 0; j < a->cols; j++)
        {
            matrix_set(a, i, j, matrix_get(a, i, j) - matrix_get(b, i, j));
        }
    }
}

void matrix_skalar_multiply(Matrix *m, double skalar)
{
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            matrix_set(m, i, j, matrix_get(m, i, j) * skalar);
        }
    }
}

Matrix* matrix_skalar_multiply_ret(Matrix *m, double skalar)
{
    Matrix *ret = matrix_new(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++)
    {
        for (int j = 0; j < m->cols; j++)
        {
            matrix_set(ret, i, j, matrix_get(m, i, j) * skalar);
        }
    }
    return ret;
}

bool matrix_invert(Matrix *m, Matrix **inverted)
{
    if (m->rows == m->cols == 2)
    {
        printf("Error: Matrix is not square");
        return false;
    }
    *inverted = matrix_new(m->rows, m->cols);
    
    double skalar = 1 / (matrix_get(m, 0, 0) * matrix_get(m, 1, 1) - matrix_get(m, 0, 1) * matrix_get(m, 1, 0));

    matrix_set(*inverted, 0, 0, matrix_get(m, 1, 1));
    matrix_set(*inverted, 0, 1, -matrix_get(m, 0, 1));
    matrix_set(*inverted, 1, 0, -matrix_get(m, 1, 0));
    matrix_set(*inverted, 1, 1, matrix_get(m, 0, 0));

    matrix_skalar_multiply(*inverted, skalar);

    return true;
}

void print_theta_func(Matrix *theta)
{
    printf("f(x) = %lf + %lf * x", matrix_get(theta, 0, 0), matrix_get(theta, 1, 0));
}

void linear_regression(Matrix **xs, Matrix *y, Matrix *theta)
{
    Matrix *x = matrix_new(2, 2);
    Matrix *x_t;

    for (int i = 0; i < 2; i++) {
        matrix_set(x, i, 0, matrix_get(xs[i], 0, 0));
        matrix_set(x, i, 1, matrix_get(xs[i], 1, 0));
    }

    matrix_transpose(x, &x_t);

    Matrix *x_t_x;
    matrix_multiply(x_t, x, &x_t_x);
    Matrix *x_t_x_i;
    matrix_invert(x_t_x, &x_t_x_i);
    Matrix *x_t_x_i_x_t;
    matrix_multiply(x_t_x_i, x_t, &x_t_x_i_x_t);
    matrix_multiply(x_t_x_i_x_t, y, &theta);
    
    print_theta_func(theta);

    // free(xs);
    matrix_free(x);
    matrix_free(x_t);
}

void gradient_descent(int count_xs, int features, int iterations, Matrix *theta, Matrix **x, Matrix *y, double alpha)
{
    Matrix *theta_t;
    double *h_x = calloc(sizeof(double) * count_xs, sizeof(double));
    for (int j = 0; j < iterations; j++) {
        Matrix *sum = matrix_new(features + 1, 1);
        
        matrix_transpose(theta, &theta_t);

        // h(x) = theta^T * x
        for (int i = 0; i < count_xs; i++) {
            Matrix *temp;
            matrix_multiply(theta_t, x[i], &temp);
            h_x[i] = matrix_get(temp, 0, 0);
            matrix_free(temp);
        }

        // sum = sum + (h(x) - y) * x
        for (int i = 0; i < count_xs; i++) {
            Matrix *h_x_y_x = matrix_skalar_multiply_ret(x[i], h_x[i] - matrix_get(y, i, 0));
            matrix_add(sum, h_x_y_x);
            matrix_free(h_x_y_x);
        }
        
        // theta = theta - (alpha / m) * sum
        matrix_skalar_multiply(sum, alpha * (1.0 / count_xs));
        matrix_subtract(theta, sum);

        // print theta every few iterations to spare time and the console
        if ((j + 1) % 100000 == 0) {
            printf("%d/%d: ", j+1, iterations);
            print_theta_func(theta);
            printf("\n");
        }
        matrix_free(sum);
    }
    matrix_free(theta_t);
}