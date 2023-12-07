#include  "include/neural_network.h"
#include "../GENETIC/include/population.h"
#include "../GENERAL/include/sort.h"
#include "../GENERAL/include/matrix_math.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_neural_network(struct NNInput *input, struct NN *neural_network) {
    // create list of neurons sizes
    neural_network->layer_number = input->layer_number;
    neural_network->neurons_size = (int*)malloc(input->layer_number * sizeof(int));
    neural_network->neurons_size = input->neurons_size;

    neural_network->AW = (struct Matrix **)malloc((input->layer_number - 1) * sizeof(struct Matrix *));
    neural_network->BW = (struct Matrix **)malloc((input->layer_number - 2) * sizeof(struct Matrix *));

    // create size for all matrixes
    int layer_index = 0;
    for(int i=0; i<input->layer_number - 1; i++){
        neural_network->AW[i] = (struct Matrix*)malloc(sizeof(struct Matrix));
        neural_network->BW[i] = (struct Matrix*)malloc(sizeof(struct Matrix));

        int sizes_AW[] = {input->neurons_size[layer_index + 1], input->neurons_size[layer_index]};
        int sizes_BW[] = {input->neurons_size[layer_index + 1], 1};

        create_matrix(neural_network->AW[i], sizes_AW);
        create_matrix(neural_network->BW[i], sizes_BW);

        layer_index += 2;
    }

    // create de/normalization matrixes of the system
    neural_network->normalization_matrix   = (float**)malloc(2 * sizeof(float*));
    neural_network->denormalization_matrix = (float**)malloc(2 * sizeof(float*));

    for(int i = 0; i < 2; i++){
        neural_network->normalization_matrix[i]   = (float*)malloc(input->layer_number * sizeof(float));
        neural_network->denormalization_matrix[i] = (float*)malloc(input->layer_number * sizeof(float));

        neural_network->normalization_matrix[i]   = input->normalization_matrix[i];
        neural_network->denormalization_matrix[i] = input->denormalization_matrix[i];
    }

    neural_network->func_ptr = malloc(sizeof(input->func_ptr));
    neural_network->func_ptr = input->func_ptr;

    // delete input structure
    clear_neural_network_input(input);
}

void clear_neural_network(struct NN *neural_network) {
    // free matrixes
     for(int i=0; i<neural_network->layer_number - 1; i++){
        matrix_delete(neural_network->AW[i]);
        matrix_delete(neural_network->BW[i]);
     }
     free(neural_network->AW);
     free(neural_network->BW);

    // free de_normalization matrixes
    for(int i = 0; i < 2; i++){
        free(neural_network->normalization_matrix[i]);
        free(neural_network->denormalization_matrix[i]);
    }
    free(neural_network->normalization_matrix);
    free(neural_network->denormalization_matrix);

    // free last pointer
    free(neural_network->neurons_size);

    // free activation function 
    free(neural_network->func_ptr);

    // delete full structure
    free(neural_network);
}

void clear_neural_network_input(struct NNInput *input){
    free(input->neurons_size);

    // free de_normalization matrixes
    for(int i = 0; i < 2; i++){
        free(input->normalization_matrix[i]);
        free(input->denormalization_matrix[i]);
    }
    free(input->normalization_matrix);
    free(input->denormalization_matrix);

    // free activation function
    free(input->func_ptr);

    // delete full strcture
    free(input);
}

void de_normalization_process(struct NN *neural_network, struct Matrix *input, int way){
    float r_min, r_max, t_min, t_max;
    for(int i=0; i<neural_network->neurons_size[0]; i++){
        if(way == 0){
            r_min = neural_network->normalization_matrix[1][i];
            r_max = neural_network->normalization_matrix[0][i];
            t_min = -1;
            t_max = 1;
        } else if(way == 1){
            r_min = -1;
            r_max = 1;
            t_min = neural_network->denormalization_matrix[1][i];
            t_max = neural_network->denormalization_matrix[0][i];
        }
        
        input->matrix[i][0] = ((input->matrix[i][0] - r_min)/(r_max - r_min)) * (t_max - t_min) + t_min;
    }
}

void one_calculation(struct NN *neural_network, struct Matrix *input_init, float output_value){

    struct Matrix *output = (struct Matrix*)malloc(sizeof(struct Matrix));
    struct Matrix *input = (struct Matrix*)malloc(sizeof(struct Matrix));
    // go though each layer intersaction and calculate
    for(int i=0; i<neural_network->layer_number - 1; i++){
        // calculate first multiplication W*x
        if(i == 0){
            matrix_multiply(input_init, neural_network->AW[i], output);
            matrix_delete(input_init);
            struct Matrix *input = (struct Matrix*)malloc(sizeof(struct Matrix));
        } else{
            matrix_multiply(input, neural_network->AW[i], output);
            matrix_delete(input);
            struct Matrix *input = (struct Matrix*)malloc(sizeof(struct Matrix));
        }

        // calculate sbstruction of W*x - omega
        if(i != neural_network->layer_number - 2){
            matrix_subst(output, neural_network->BW[i], input);
            matrix_delete(output);

            matrix_all_values_formula(input, neural_network->func_ptr);
            struct Matrix *output = (struct Matrix*)malloc(sizeof(struct Matrix));
        } else {
            matrix_all_values_formula(output, neural_network->func_ptr);
        }
    }   

    output_value = output->matrix[0][0];
    matrix_delete(output);
    matrix_delete(input);
}