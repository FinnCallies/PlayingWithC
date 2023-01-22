#include <stdio.h>
#include <stdlib.h>
#include "vec.h"


Vec *vec_new(int dimensions)
{
    Vec *v = malloc(sizeof(Vec));
    v->dimensions = dimensions;
    v->data = malloc(sizeof(double) * dimensions);
    return v;
}

void vec_free(Vec *v)
{
    free(v->data);
    free(v);
}

void vec_set(Vec *v, int index, double value)
{
    v->data[index] = value;
}

double vec_get(Vec *v, int index)
{
    return v->data[index];
}

void vec_print(Vec *v)
{
    printf("[");
    for (int i = 0; i < v->dimensions; i++)
    {
        printf("%f", v->data[i]);
        if (i < v->dimensions - 1)
        {
            printf(", ");
        }
    }
    printf("]");
}