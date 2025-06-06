#include "general/matrix_math.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void matrixDeleteOnlyData(Matrix *matrix){
    if(matrix){
        for(int i=0; i<matrix->sizes[0]; i++){
            free(matrix->matrix[i]);
        }
        free(matrix->matrix);
        free(matrix->sizes);

        matrix->matrix = NULL;
        matrix->sizes  = NULL;
    }
}

void matrixDelete(Matrix *matrix){
    matrixDeleteOnlyData(matrix);
    free(matrix);
}

void createMatrix(Matrix *matrix, int *sizes){
    // sizes are in format [row, col]

    matrix->matrix = malloc(sizes[0] * sizeof(float*));
    for(int i=0; i<sizes[0]; i++){
        matrix->matrix[i] = malloc(sizes[1] * sizeof(float));
    }

    matrix->sizes = malloc(2 * sizeof(int));
    matrix->sizes[0] = sizes[0];
    matrix->sizes[1] = sizes[1];

    free(sizes);
}

void createMatrixFromPointer(Matrix *output, const float *input, int *size){
    // sizes are in format [row, col]
    createMatrix(output, size);

    int globalIndex = 0;
    for(int i=0; i<output->sizes[0]; i++){
        for(int y=0; y<output->sizes[1]; y++){
            output->matrix[i][y] = input[globalIndex];
            globalIndex++;
        }
    }
}

void matrixMultiply(const Matrix *leftMatrix, const Matrix *rightMatrix, Matrix *output){
    if(leftMatrix->sizes[1] != rightMatrix->sizes[0]){
        fprintf(stderr, "Error: Sizes of matrix's are incorrect\n");
        exit(EXIT_FAILURE);
    }
    CREATE_MATRIX_WITH_SIZE(output, leftMatrix, leftMatrix);

    for(int i=0; i < rightMatrix->sizes[1]; i++){
        // start of a column of matrix
        for(int y=0; y < leftMatrix->sizes[0]; y++){
            // start of a row of matrix 
            output->matrix[y][i] = 0;

            for(int x=0; x < leftMatrix->sizes[1]; x++){
                output->matrix[y][i] += leftMatrix->matrix[y][x] * rightMatrix->matrix[x][i];
            }
        }
    }
}

void fullyCopyMatrix(const Matrix *input, Matrix *output){
    CREATE_MATRIX_WITH_SIZE(output, input, input);

    for(int i=0; i < output->sizes[0]; i++){
        memcpy(output->matrix[i], input->matrix[i], output->sizes[1] * sizeof(float));
    }
}

void matrixSubstAdd(struct Matrix *A, struct Matrix *B, struct Matrix *output, int type){
    // please note that the sizes should be in the following format:
    // [ rows cols ]

    // type: 0 - subs, 1 - add
    CREATE_MATRIX_WITH_SIZE(output, A, B);

    for(int i=0; i<output->sizes[0]; i++){

        for(int y=0; y<output->sizes[1]; y++){
            if(type == 0){
                output->matrix[i][y] = A->matrix[i][y] - B->matrix[i][y];
            } else{
                output->matrix[i][y] = A->matrix[i][y] + B->matrix[i][y];
            }
        }
    }
}

void matrixAllValuesFormula(const Matrix *matrix, float (*func_ptr)(float)){
    for(int i=0; i<matrix->sizes[0]; i++){
        for(int y=0; y<matrix->sizes[1]; y++){
            matrix->matrix[i][y] = func_ptr(matrix->matrix[i][y]);
        }
    }
}