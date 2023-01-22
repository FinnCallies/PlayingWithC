#include <stdio.h>
#include <stdlib.h>
#include "vec.h"
#include "matrix.h"


void lecture1_exercise_linear_regression()
{
    Matrix *theta = matrix_new(2, 1);
    Matrix *x1 = matrix_new(2, 1);
    Matrix *x2 = matrix_new(2, 1);
    Matrix *y = matrix_new(2, 1);
    Matrix **x = calloc(2, sizeof(Matrix *));
    
    matrix_set(x1, 0, 0, 1);
    matrix_set(x1, 1, 0, 100);
    x[0] = x1;

    matrix_set(x2, 0, 0, 1);
    matrix_set(x2, 1, 0, 150);
    x[1] = x2;
    
    matrix_set(y, 0, 0, 400);
    matrix_set(y, 1, 0, 500);


    linear_regression(x, y, theta);


    matrix_free(x1);
    matrix_free(x2);
    matrix_free(y);
    matrix_free(theta);
    free(x);
}


void lecture1_exercise_gradient_descent()
{
    // count_xs = number of training examples
    int count_xs = 4;
    // features = number of features (wohnfläche)
    int features = 1;
    // iterations = number of iterations
    int iterations = 5000000;

    // init Matrices and Matrix-Array
    Matrix *theta = matrix_new(features + 1, 1);
    Matrix *x1 = matrix_new(features + 1, 1);
    Matrix *x2 = matrix_new(features + 1, 1);
    Matrix *x3 = matrix_new(features + 1, 1);
    Matrix *x4 = matrix_new(features + 1, 1);
    Matrix *y = matrix_new(count_xs, 1);
    Matrix **x = calloc(count_xs, sizeof(Matrix *));
    
    // Setting the learning rate alpha
    // double alpha = 0.00012306;   // 4,037 - 4,038 mio (Standartwerte)
    double alpha = 0.0001055;          // 4,1 mio (vier Punkte)
    
    // Setting initial Theta
    matrix_set(theta, 0, 0, 100);
    matrix_set(theta, 1, 0, 3);
    
    // Setting the x and y values for the training examples
    matrix_set(x1, 0, 0, 1);
    matrix_set(x1, 1, 0, 100);
    matrix_set(y, 0, 0, 400);
    x[0] = x1;

    matrix_set(x2, 0, 0, 1);
    matrix_set(x2, 1, 0, 150);
    matrix_set(y, 1, 0, 500);
    x[1] = x2;
    
    matrix_set(x3, 0, 0, 1);
    matrix_set(x3, 1, 0, 120);
    matrix_set(y, 2, 0, 600);
    x[2] = x3;

    matrix_set(x4, 0, 0, 1);
    matrix_set(x4, 1, 0, 170);
    matrix_set(y, 3, 0, 550);
    x[3] = x4;
    

    // The actual gradient descent algorithm
    gradient_descent(count_xs, features, iterations, theta, x, y, alpha);


    // free Matrices and Matrix-Array
    matrix_free(x1);
    matrix_free(x2);
    matrix_free(x3);
    matrix_free(x4);
    matrix_free(y);
    matrix_free(theta);
    free(x);
}


int main(int argc, char const *argv[])
{
    // lecture1_exercise_linear_regression();
    lecture1_exercise_gradient_descent();

    return 0;
}