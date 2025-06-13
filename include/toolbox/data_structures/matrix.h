#ifndef MATRIX_H
#define MATRIX_H

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
Matrix* MatrixCreate(const int rows, const int cols);

/*
 * This function is used to create matrix from values of a pointer array "input"
 * Input:
 *    const float *input - the float array pointer which contains values for the matrix
 *    const int rows - the number of rows in new matrix
 *    const int cols - the number of columns in new matrix
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 */
Matrix* MatrixCreateFromPointer(const float *input, const int rows, const int cols);

/*
 * This function is used to multiply two matrices in form A * B
 * Input:
 *    const Matrix *leftMatrix - the left matrix of the action
 *    const Matrix *rightMatrix - the right matrix of the action
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 */
Matrix* MatrixMultiply(const Matrix *leftMatrix, const Matrix *rightMatrix);

/*
 * This function is used to add/substruct two matrices in format A-B or A+B
 * Input:
 *    const Matrix *leftMatrix - the left matrix of the action
 *    const Matrix *rightMatrix - the right matrix of the action
 *    const int type - the definer of the type of actions made. 0 - subs, 1 - add
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 */
Matrix* MatrixSubstAdd(const Matrix *leftMatrix, const Matrix *rightMatrix, const int type);

/*
 * This function is used to make a copy of the matrix provided
 * Input:
 *    const Matrix *matrix - the matrix which will be copied
 * Output;
 *    The function returns the pointer to the structure of type Matrix
 */
Matrix* MatrixMakeCopy(const Matrix *input);

/*
 * This function is used to pass all values trough function
 * Input:
 *    const Matrix *matrix - the pointer to struct matrix which is used for the action
 *    float (*func_ptr)(float) - the function pointer for the action
 * Output;
 *    The function returns nothing. But makes direct changes to the matrix pointer provided
 */
void MatrixApplyFormula(const Matrix *matrix, float (*func_ptr)(float));

/*
 * This function is used to fully delete matrix
 * Input:
 *    const Matrix *matrix - the pointer to struct matrix which is used for the action
 * Output;
 *    The function returns nothing.
 */
void MatrixDelete(Matrix *matrix);

/*
 * This function is used to delete the data of the matrix
 * Input:
 *    const Matrix *matrix - the pointer to struct matrix which is used for the action
 * Output;
 *    The function returns nothing. But makes direct changes to the matrix pointer provided
 */
void MatrixClear(Matrix *matrix);

/*
 * This function is used to reshape matrix size
 * Input:
 *    const Matrix *matrix - the pointer to struct matrix which is used for the action
 *    const int rows - new matrix number of the rows
 *    const int cols - new matrix number of the column
 * Output;
 *    The function returns nothing. But makes direct changes to the matrix pointer provided
 */

void MatrixReshape(Matrix *matrix, const int rows, const int cols);

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
 