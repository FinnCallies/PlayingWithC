#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vec.h"
#include "matrix.h"


void parse_csv(char *filename)
{
    FILE *CSV;
    char *str = calloc(500, sizeof(char)); // free(str)
    char *token;
    char *delimiter = ",";


    CSV = fopen("test.csv", "r"); // fclose(CSV)
    if (CSV == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // 
    int line_count = 13581;
    // count_xs = number of training examples
    int count_xs = 0;
    // features = number of features (wohnfläche)
    int features = 1;
    // iterations = number of iterations
    int iterations = 1000000;

    // init Matrices and Matrix-Array
    Matrix *theta = matrix_new(features + 1, 1);    // matrix_free(theta)
    Matrix *y = matrix_new(line_count, 1);          // matrix_free(y)
    Matrix **x = (Matrix **) calloc(line_count, sizeof(Matrix *)); // matrix_free(x[i]); free(x)
    if (x == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }
    
    
    
    // Setting the learning rate alpha
    // double alpha = 0.00012306;   // 4,037 - 4,038 mio (Standartwerte)
    double alpha = 0.000002;          // 4,1 mio (vier Punkte)
    
    // Setting initial Theta
    matrix_set(theta, 0, 0, 500000.0);
    matrix_set(theta, 1, 0, 4000.0);


    int lines = 0;
    while(fgets(str,500,CSV)) {
        int tok = 0;
        double price = 0.0;
        double buildingArea = 0.0;

        lines++;

        token = strtok(str, delimiter);

        while (token != NULL) {
            if (tok == 4) {
                price = atof(token);
            } else if (tok == 14) {
                buildingArea = atof(token);
            }
            
            token = strtok(NULL,delimiter);
            tok++;
        }


        if (buildingArea > 0.0 && price > 0.0) {
            x[count_xs] = matrix_new(features + 1, 1);
            matrix_set(x[count_xs], 0, 0, 1.0);
            matrix_set(x[count_xs], 1, 0, buildingArea);
            matrix_set(y, count_xs, 0, price);
            count_xs++;
        }
    }
}


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
    int count_xs = 2;
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
    if (x == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }

    
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


void melb_data_gradient_descent_linear_regression()
{
    FILE *CSV;
    char *str = calloc(500, sizeof(char)); // free(str)
    char *token;
    char *delimiter = ",";


    CSV = fopen("melb_data.csv", "r"); // fclose(CSV)
    if (CSV == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    // 
    int line_count = 13581;
    // count_xs = number of training examples
    int count_xs = 0;
    // features = number of features (wohnfläche)
    int features = 1;
    // iterations = number of iterations
    int iterations = 1000000;

    // init Matrices and Matrix-Array
    Matrix *theta = matrix_new(features + 1, 1);    // matrix_free(theta)
    Matrix *y = matrix_new(line_count, 1);          // matrix_free(y)
    Matrix **x = (Matrix **) calloc(line_count, sizeof(Matrix *)); // matrix_free(x[i]); free(x)
    if (x == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }
    
    
    
    // Setting the learning rate alpha
    // double alpha = 0.00012306;   // 4,037 - 4,038 mio (Standartwerte)
    double alpha = 0.000002;          // 4,1 mio (vier Punkte)
    
    // Setting initial Theta
    matrix_set(theta, 0, 0, 500000.0);
    matrix_set(theta, 1, 0, 4000.0);


    int lines = 0;
    while(fgets(str,500,CSV)/*  && lines < 200 */) {
        int tok = 0;
        double price = 0.0;
        double buildingArea = 0.0;

        lines++;

        token = strtok(str, delimiter);

        while (token != NULL)
        {
            if (tok == 4) {
                price = atof(token);
            } else if (tok == 14) {
                buildingArea = atof(token);
            }
            
            token = strtok(NULL,delimiter);
            tok++;
        }

        /* printf("price: %lf; ", price);
        printf("buildingArea: %lf\n", buildingArea); */


        if (buildingArea > 0.0 && price > 0.0)
        {
            x[count_xs] = matrix_new(features + 1, 1);
            matrix_set(x[count_xs], 0, 0, 1.0);
            matrix_set(x[count_xs], 1, 0, buildingArea);

            /* for (int i = 0; i < count_xs + 1; i++) {
                printf("%p, ", x[i]);
            }
            printf("\n"); */

            matrix_set(y, count_xs, 0, price);
            /* printf("x[%d]: ", count_xs);
            matrix_print(x[count_xs]);
            printf("\n"); */
            
            /* for (int i = 0; i < count_xs + 1; i++) {
                printf("%p, ", x[i]);
            }
            printf("\n"); */

            /* matrix_print(x[0]);
            printf("\n"); */
            count_xs++;
        }
    }


    printf("lines: %d; \n", lines);

    // matrix_print(x[count_xs - 1]);
    gradient_descent(count_xs, features, iterations, theta, x, y, alpha);



    if (fclose(CSV) != 0) {
        printf("Error closing file\n");
    }
    for (int i = 0; i < count_xs; i++) {
        matrix_free(x[i]);
    }
    matrix_free(y);
    matrix_free(theta);
    free(x);
    free(str);
}


int main(int argc, char const *argv[])
{
    // melb_data_gradient_descent_linear_regression();
    // lecture1_exercise_linear_regression();
    lecture1_exercise_gradient_descent();

    return 0;
}