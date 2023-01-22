#ifndef VEC_H
#define VEC_H


typedef struct {
    double *data;
    int dimensions;
} Vec;


Vec *vec_new(int dimensions);
void vec_free(Vec *v);
void vec_set(Vec *v, int index, double value);
double vec_get(Vec *v, int index);
void vec_print(Vec *v);


#endif