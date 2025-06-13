#ifndef MATRIX_MATH_H
#define MATRIX_MATH_H
#include "genetic/population.h"

typedef struct Matrix{
    float** matrix;

    int rows;
    int cols;
} Matrix;

/*
 * This function is used to create new matrix
 * Input:
 *    const int rows - the number of rows in new matrix
 *    const int cols - the number of columns in new matrix
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 */
Matrix* createMatrix(const int rows, const int cols);

/*
 * This function is used to multiply two matrices in form A * B
 * Input:
 *    const Matrix *leftMatrix - the left matrix of the action
 *    const Matrix *rightMatrix - the right matrix of the action
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 */
Matrix* matrixMultiply(const Matrix *leftMatrix, const Matrix *rightMatrix);

/*
 * This function is used to add/substruct two matrices in format A-B or A+B
 * Input:
 *    const Matrix *leftMatrix - the left matrix of the action
 *    const Matrix *rightMatrix - the right matrix of the action
 *    const int type - the definer of the type of actions made. 0 - subs, 1 - add
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 */
Matrix* matrixSubstAdd(const Matrix *leftMatrix, const Matrix *rightMatrix, const int type);

/*
 * This function is used to create matrix from values of a pointer array "input"
 * Input:
 *    const float *input - the float array pointer which contains values for the matrix
 *    const int rows - the number of rows in new matrix
 *    const int cols - the number of columns in new matrix
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 *
 * !!!! the way of doing this should be changed from the pointer to matrix to making a matrix with one row and then resizing it
 */
Matrix* createMatrixFromPointer(const float *input, const int rows, const int cols);

/*
 * This function is used to make a copy of the matrix provided
 * Input:
 *    const Matrix *matrix - the matrix which will be copied
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 */
Matrix* matrixFullyCopy(const Matrix *input);

/*
 * This function is used to pass all values trough function
 * Input:
 *    const Matrix *matrix - the pointer to struct matrix which is used for the action
 *    float (*func_ptr)(float) - the function pointer for the action
 * Output;
 *    The function returns nothing. But makes direct changes to the matrix pointer provided
 */
void matrixAllValuesFormula(const Matrix *matrix, float (*func_ptr)(float));

/*
 * This function is used to fully delete matrix
 * Input:
 *    const Matrix *matrix - the pointer to struct matrix which is used for the action
 * Output;
 *    The function returns nothing.
 */
void matrixDelete(Matrix *matrix);

/*
 * This function is used to delete the data of the matrix
 * Input:
 *    const Matrix *matrix - the pointer to struct matrix which is used for the action
 * Output;
 *    The function returns nothing. But makes direct changes to the matrix pointer provided
 */
void matrixDeleteOnlyData(Matrix *matrix);

#define CLEAR_MATRIX_UNTIL(matrix, count_to_free) do { \
    if (matrix != NULL) {                              \
        for (int i = 0; i < (count_to_free); i++) {    \
            if (matrix[i] != NULL) {                   \
                free(matrix[i]);                       \
                matrix[i] = NULL;                      \
            }                                          \
        }                                              \
    }                                                  \
} while (0)

#endif
 