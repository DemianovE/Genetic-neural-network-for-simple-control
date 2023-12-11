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
    matrix->sizes[0] = sizes[0];
    matrix->sizes[1] = sizes[1];
    
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
    int *sizes = (int*)malloc(2 * sizeof(int));
    sizes[0] = A->sizes[0];
    sizes[1] = B->sizes[1];
    create_matrix(output, sizes);
    for(int i=0; i<B->sizes[1]; i++){
        // start of a collumn of matrix
        for(int y=0; y<A->sizes[0]; y++){
            // start of a row of matrix 
            output->matrix[y][i] = 0;

            for(int x=0; x<A->sizes[1]; x++){
                output->matrix[y][i] += A->matrix[y][x] * B->matrix[x][i];
            }
        }
    }
}

void fully_copy_matrix(struct Matrix *input, struct Matrix *output){
    create_matrix(output, input->sizes);

    for(int i=0; i<input->sizes[0]; i++){
        for(int x=0; x<input->sizes[1]; x++){
            output->matrix[i][x] = input->matrix[i][x];
        }
    }
}

void matrix_subst_add(struct Matrix *A, struct Matrix *B, struct Matrix *output, int type){
    // please not that the sizes should be in following format:
    // [ rows cols ]

    // type: 0 - subs, 1 - add

    int *sizes = (int *)malloc(2 * sizeof(int));
    sizes[0] = A->sizes[0];
    sizes[1] = B->sizes[1];

    create_matrix(output, sizes);

    for(int i=0; i<output->sizes[0]; i++){

        for(int y=0; y<output->sizes[1]; y++){
            printf("%f - %f\n", A->matrix[i][y], B->matrix[i][y]);
            if(type == 0){
                output->matrix[i][y] = A->matrix[i][y] - B->matrix[i][y];
            } else{
                output->matrix[i][y] = A->matrix[i][y] + B->matrix[i][y];
            }
        }
    }
}

void matrix_all_values_formula(struct Matrix *matrix, float (*func_ptr)(float)){
    for(int i=0; i<matrix->sizes[0]; i++){
        for(int y=0; y<matrix->sizes[1]; y++){
            matrix->matrix[i][y] = func_ptr(matrix->matrix[i][y]);
        }
    }
}