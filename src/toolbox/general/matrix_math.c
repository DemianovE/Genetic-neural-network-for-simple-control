#include "matrix_math.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void matrixDeleteOnlyData(Matrix *matrix){
    if(matrix){
        for(int i=0; i<matrix->rows; i++){
            free(matrix->matrix[i]);
        }
        free(matrix->matrix);

        matrix->matrix = NULL;
    }
}

void matrixDelete(Matrix *matrix){
    matrixDeleteOnlyData(matrix);
    free(matrix);
}

Matrix* createMatrix(const int rows, const int cols){
    assert(rows > 0 && "array of sizes value x should be positive!");
    assert(cols > 0 && "array of sizes value y should be positive!");

    Matrix *matrix = NULL;
    matrix = malloc(sizeof(Matrix));
    if (matrix == NULL){ perror("Failed to allocate Matrix"); exit(EXIT_FAILURE); }

    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = NULL;

    matrix->matrix = malloc(matrix->rows * sizeof(float*));
    if (matrix->matrix == NULL) { perror("Failed to allocate Matrix rows"); free(matrix); exit(EXIT_FAILURE); }

    for(int i=0; i<matrix->rows; i++){
        matrix->matrix[i] = NULL;
        matrix->matrix[i] = malloc(matrix->cols * sizeof(float));
        if (matrix->matrix[i] == NULL) { perror("Failed to allocate Matrix column"); free(matrix); CLEAR_MATRIX_UNTIL(matrix->matrix, i); exit(EXIT_FAILURE); }
    }

    return matrix;
}

Matrix* createMatrixFromPointer(const float *input, const int rows, const int cols){
    assert(input != NULL && "input pointer should not be NULL!");

    // sizes are in format [row, col]
    Matrix *output = createMatrix(rows, cols);

    int globalIndex = 0;
    for(int i=0; i<output->rows; i++){
        for(int y=0; y<output->cols; y++){
            output->matrix[i][y] = input[globalIndex];
            globalIndex++;
        }
    }

    return output;
}

Matrix* matrixMultiply(const Matrix *leftMatrix, const Matrix *rightMatrix){
    assert(leftMatrix != NULL && "leftMatrix pointer should not be NULL!");
    assert(rightMatrix != NULL && "rightMatrix pointer should not be NULL!");

    if(leftMatrix->cols != rightMatrix->rows){
        fprintf(stderr, "Error: Sizes of matrix's are incorrect\n");
        exit(EXIT_FAILURE);
    }
    Matrix *output = createMatrix(leftMatrix->rows, rightMatrix->cols);

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

Matrix* matrixFullyCopy(const Matrix *input){
    Matrix *output = createMatrix(input->rows, input->cols);

    for(int i=0; i < output->rows; i++) memcpy(output->matrix[i], input->matrix[i], output->cols * sizeof(float));
    return output;
}

Matrix* matrixSubstAdd(const Matrix *leftMatrix, const Matrix *rightMatrix, const int type){
    // type:
    Matrix *output = createMatrix(leftMatrix->rows, rightMatrix->cols);

    for(int i=0; i<output->rows; i++){
        for(int y=0; y<output->cols; y++) output->matrix[i][y] = (type == 0) ? leftMatrix->matrix[i][y] - rightMatrix->matrix[i][y] : leftMatrix->matrix[i][y] + rightMatrix->matrix[i][y];
    }
    return output;
}

void matrixAllValuesFormula(const Matrix *matrix, float (*func_ptr)(float)){
    for(int i=0; i<matrix->rows; i++){
        for(int y=0; y<matrix->cols; y++) matrix->matrix[i][y] = func_ptr(matrix->matrix[i][y]);
    }
}