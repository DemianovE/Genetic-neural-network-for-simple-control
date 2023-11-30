#include "include/matrix_math.h"
#include "../GENETIC/include/population.h"

#include <stdlib.h>
#include <stdio.h>

void matrix_delete(struct Matrix *matrix){

    for(int i=0; i<matrix->sizes[0]; i++){
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix->sizes);
    free(matrix);
}

void create_matrix(struct Matrix *matrix, int *sizes){
    // sizes are in format [row, col]

    matrix->matrix = (float**)malloc(sizes[0] * sizeof(float*));
    for(int i=0; i<sizes[0]; i++){
        matrix->matrix[i] = (float*)malloc(sizes[1] * sizeof(float));
    }
    matrix->sizes = (int*)malloc(2 * sizeof(int));
    matrix->sizes = sizes;
    free(sizes);
}

void create_matrix_from_pointer(struct Matrix *output, float *input, int *size){
    // sizes are in format [row, col]
    create_matrix(output, size);

    int global_index = 0;
    for(int i=0; i<size[0]; i++){
        for(int y=0; y<size[1]; y++){
            output->matrix[i][y] = input[global_index];
            global_index++;
        }
    }
    free(size);
}

void matrix_multiply(struct Matrix *A, struct Matrix *B, struct Matrix *output){

    if(A->sizes[1] != B->sizes[0]){
        fprintf(stderr, "Error: Sizes of matrixes are incorect\n");
        exit(EXIT_FAILURE);
    } 

    int sizes[] = {A->sizes[0], B->sizes[1]};
    create_matrix(output, sizes);

    int sum;
    for(int i=0; i<B->sizes[1]; i++){
        // start of a collumn of matrix
        for(int y=0; y<A->sizes[0]; y++){
            // start of a row of matrix 
            sum = 0;

            for(int x=0; x<A->sizes[1]; x++){
                sum += A->matrix[y][x] * B->matrix[x][i];
            }
            output->matrix[y][i] = sum;
        }
    }
    
    // delete input matrixes
    matrix_delete(A);
    matrix_delete(B);
}

void matrix_subst(struct Matrix *A, struct Matrix *B, struct Matrix *output){
    // please not that the sizes should be in following format:
    // [ rows cols ]

    int sizes[] = {A->sizes[0], B->sizes[1]};
    create_matrix(output, sizes);

    for(int i=0; i<sizes[0]; i++){

        for(int y=0; y<sizes[1]; y++){
            output->matrix[i][y] = A->matrix[i][y] - B->matrix[i][y];
        }
    }
    matrix_delete(A);
    matrix_delete(B);
}

void matrix_all_values_formula(struct Matrix *matrix, float (*func_ptr)(float)){
    for(int i=0; i<matrix->sizes[0]; i++){
        for(int y=0; y<matrix->sizes[1]; y++){
            matrix->matrix[i][y] = func_ptr(matrix->matrix[i][y]);
        }
    }
}