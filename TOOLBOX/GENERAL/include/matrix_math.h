#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H
#include "../../GENETIC/include/population.h"

typedef struct Matrix{
    float** matrix;
    int*    sizes;
}Matrix;

// function to create new matrix
void create_matrix(struct Matrix *matrix, int *sizes);

// function to multiply two matrixes in form A * B
void matrix_multiply(struct Matrix *A, struct Matrix *B, struct Matrix *output);

// function to sunbstruct two matrixes in form A - B
void matrix_subst(struct Matrix *A, struct Matrix *B, struct Matrix *output);

// function to pass all values trough function
void matrix_all_values_formula(struct Matrix *matrix, float (*func_ptr)(float));

// function to create matrix from values of pointer
void create_matrix_from_pointer(struct Matrix *output, float *input, int *size);

// function to delete matrix
void matrix_delete(struct Matrix *matrix);

#endif
 