#include "matrix.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * This function is used to creat a matrix grid from params
 * Input:
 *    const Matrix *matrix - the pointer to struct matrix which is used for the action
 * Output;
 *    The function returns nothing. But makes direct changes to the matrix pointer provided
 */
static void MatrixCreateGrid(Matrix *matrix){
    matrix->matrix = malloc(matrix->rows * sizeof(float*));
    if (matrix->matrix == NULL) { perror("Failed to allocate Matrix rows"); free(matrix); exit(EXIT_FAILURE); }

    for(int i=0; i<matrix->rows; i++){
        matrix->matrix[i] = NULL;
        matrix->matrix[i] = malloc(matrix->cols * sizeof(float));
        if (matrix->matrix[i] == NULL) { perror("Failed to allocate Matrix column"); CLEAR_MATRIX_UNTIL(matrix->matrix, i); free(matrix); exit(EXIT_FAILURE); }
    }
}

Matrix* MatrixCreate(const int rows, const int cols){
    /* Matrix *matrix - the output matrix pointer */

    assert(rows > 0 && "array of sizes value x should be positive!");
    assert(cols > 0 && "array of sizes value y should be positive!");

    Matrix *matrix = NULL;
    matrix = malloc(sizeof(Matrix));
    if (matrix == NULL){ perror("Failed to allocate Matrix"); exit(EXIT_FAILURE); }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = NULL;

    MatrixCreateGrid(matrix);

    return matrix;
}

Matrix* MatrixCreateFromPointer(const float *input, const int rows, const int cols){
    /* Matrix *matrix - the output matrix pointer */

    assert(input != NULL && "input pointer should not be NULL!");

    // sizes are in format [row, col]
    Matrix *output = MatrixCreate(1, rows * cols);
    memcpy(output->matrix[0], input, sizeof(float) * output->cols * output->rows);

    MatrixReshape(output, rows, cols);
    return output;
}

Matrix* MatrixMultiply(const Matrix *leftMatrix, const Matrix *rightMatrix){
    /* Matrix *matrix - the output matrix pointer */

    assert(leftMatrix != NULL && "leftMatrix pointer should not be NULL!");
    assert(rightMatrix != NULL && "rightMatrix pointer should not be NULL!");

    if(leftMatrix->cols != rightMatrix->rows){
        fprintf(stderr, "Error: Sizes of matrix's are incorrect\n");
        exit(EXIT_FAILURE);
    }
    Matrix *output = MatrixCreate(leftMatrix->rows, rightMatrix->cols);

    for(int i=0; i < rightMatrix->cols; i++){
        // start of a column of matrix
        for(int y=0; y < leftMatrix->rows; y++){
            // start of a row of matrix 
            output->matrix[y][i] = 0;
            for(int x=0; x < leftMatrix->cols; x++) output->matrix[y][i] += leftMatrix->matrix[y][x] * rightMatrix->matrix[x][i];
        }
    }
    return output;
}

Matrix* MatrixMakeCopy(const Matrix *input){
    /* Matrix *matrix - the output matrix pointer */

    Matrix *output = MatrixCreate(input->rows, input->cols);

    for(int i=0; i < output->rows; i++) memcpy(output->matrix[i], input->matrix[i], output->cols * sizeof(float));
    return output;
}

Matrix* MatrixSubstAdd(const Matrix *leftMatrix, const Matrix *rightMatrix, const int type){
    /* Matrix *matrix - the output matrix pointer */

    Matrix *output = MatrixCreate(leftMatrix->rows, rightMatrix->cols);

    for(int i=0; i<output->rows; i++){
        for(int y=0; y<output->cols; y++) output->matrix[i][y] = (type == 0) ? leftMatrix->matrix[i][y] - rightMatrix->matrix[i][y] : leftMatrix->matrix[i][y] + rightMatrix->matrix[i][y];
    }
    return output;
}

void MatrixReshape(Matrix *matrix, const int rows, const int cols){
    /*  Matrix *copy - the matrix pointer used to story a copy of matrix shaped */
    Matrix *copy = MatrixMakeCopy(matrix);

    MatrixClear(matrix);
    matrix->rows = rows;
    matrix->cols = cols;

    MatrixCreateGrid(matrix);

    int copyX = 0, copyY = 0;
    int mainX = 0, mainY = 0;

    for (size_t j=0; j<matrix->cols * matrix->rows; j++){
        matrix->matrix[mainX][mainY] = copy->matrix[copyX][copyY];

        mainY++; copyY++;
        if (mainY == matrix->cols) {mainY = 0; mainX++;};
        if (copyY == copy->cols) {copyY = 0; copyX++;};
    }

    MatrixDelete(copy);
}

void MatrixClear(Matrix *matrix){
    if(matrix){
        for(int i=0; i<matrix->rows; i++) free(matrix->matrix[i]);
        free(matrix->matrix);
        matrix->matrix = NULL;
    }
}

void MatrixDelete(Matrix *matrix){
    MatrixClear(matrix);
    free(matrix);
}

void MatrixApplyFormula(const Matrix *matrix, float (*func_ptr)(float)){
    for(int i=0; i<matrix->rows; i++){
        for(int y=0; y<matrix->cols; y++) matrix->matrix[i][y] = func_ptr(matrix->matrix[i][y]);
    }
}