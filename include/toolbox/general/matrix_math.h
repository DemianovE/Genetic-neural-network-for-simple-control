#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H
#include "genetic/population.h"

typedef struct Matrix{
    float** matrix;
    int*    sizes;
}Matrix;

// function to create new matrix
void createMatrix(Matrix *matrix, int *sizes);

// function to multiply two matrix's in form A * B
void matrixMultiply(const Matrix *A, const Matrix *B, struct Matrix *output);

// function to add/substruct two matrixes in format A-B or A+B
void matrixSubstAdd(Matrix *A, Matrix *B, Matrix *output, int type);

// function to pass all values trough function
void matrixAllValuesFormula(const Matrix *matrix, float (*func_ptr)(float));

// function to create matrix from values of a pointer
void createMatrixFromPointer(Matrix *output, const float *input, int *size);

// function to delete matrix
void matrixDelete(Matrix *matrix);

// function to delete the data of the matrix
void matrixDeleteOnlyData(Matrix *matrix);

// create full coppy of the matrix
void fullyCopyMatrix(const Matrix *input, Matrix *output);

// macro to copy size and make matrix
#define CREATE_MATRIX_WITH_SIZE(matrix, smaller, bigger) do { \
    int size[] = {smaller->sizes[0], bigger->sizes[1]}; \
    createMatrix(matrix, size); \
} while (0)

#endif
 