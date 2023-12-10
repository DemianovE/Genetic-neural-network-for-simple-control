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

    // deffine the type of the NN
    neural_network->type = input->type;

    // delete input structure
    clear_neural_network_input(input);

    neural_network->AW = (struct Matrix **)malloc((neural_network->layer_number - 1) * sizeof(struct Matrix *));
    neural_network->BW = (struct Matrix **)malloc((neural_network->layer_number - 2) * sizeof(struct Matrix *));

    // create size for all matrixes
    int layer_index = 0;
    for(int i=0; i<neural_network->layer_number - 1; i++){
        neural_network->AW[i] = (struct Matrix*)malloc(sizeof(struct Matrix));
        neural_network->BW[i] = (struct Matrix*)malloc(sizeof(struct Matrix));

        int sizes_AW[] = {neural_network->neurons_size[layer_index + 1], neural_network->neurons_size[layer_index]};
        int sizes_BW[] = {neural_network->neurons_size[layer_index + 1], 1};

        create_matrix(neural_network->AW[i], sizes_AW);
        create_matrix(neural_network->BW[i], sizes_BW);

        layer_index += 2;
    }

    // create de/normalization matrixes of the system
    neural_network->normalization_matrix   = (float**)malloc(2 * sizeof(float*));
    neural_network->denormalization_matrix = (float**)malloc(2 * sizeof(float*));

    for(int i = 0; i < 2; i++){
        neural_network->normalization_matrix[i]   = (float*)malloc(neural_network->layer_number * sizeof(float));
        neural_network->denormalization_matrix[i] = (float*)malloc(neural_network->layer_number * sizeof(float));

        neural_network->normalization_matrix[i]   = neural_network->normalization_matrix[i];
        neural_network->denormalization_matrix[i] = neural_network->denormalization_matrix[i];
    }

    neural_network->func_ptr = malloc(sizeof(neural_network->func_ptr));
    neural_network->func_ptr = neural_network->func_ptr;

    // alocate AM if type != 0
    if(neural_network->type == 1){ // SD
        neural_network->AM = (struct Matrix**)malloc(2 * sizeof(Matrix*));
         
        int sizes_AM_start[] = {neural_network->neurons_size[1], 1};   // size of the strat SD matrix which is the size of the 1 HL
        int size_AM_end[]    = {neural_network->neurons_size[layer_index - 2], 1}; // size of the end SD layer which is the size of last HL
        
        create_matrix(neural_network->AM[0], sizes_AM_start);
        create_matrix(neural_network->AM[1], size_AM_end);

        // create type_AM array and fill with types for S and D of SD NN
        neural_network->type_AM = (int**)malloc(2* sizeof(int*));
        neural_network->type_AM[0] = (int*)malloc(neural_network->neurons_size[1] * sizeof(int));
        neural_network->type_AM[1] = (int*)malloc(neural_network->neurons_size[layer_index - 2] * sizeof(int));

        int till_D_start = neural_network->neurons_size[1] % 2 == 0 ? neural_network->neurons_size[1] / 2 : (neural_network->neurons_size[1] - 1) / 2;
        int till_D_end   = neural_network->neurons_size[layer_index - 2] % 2 == 0 ? neural_network->neurons_size[layer_index - 2] / 2 : (neural_network->neurons_size[layer_index - 2] - 1) / 2;

        for(int i=0; i< neural_network->neurons_size[layer_index - 2]; i++){
            if(i<till_D_end){
                neural_network->type_AM[1][i] = 0; // s type SD neuron
            } else{
                neural_network->type_AM[1][i] = 1; // D type SD neuron
            }
        }

        for(int i=0; i< neural_network->neurons_size[1]; i++){
            if(i<till_D_start){
                neural_network->type_AM[0][i] = 0; // S type SD neuron
            } else{
                neural_network->type_AM[0][i] = 1; // D type SD neuron
            }
        }
    }
}

void clear_neural_network(struct NN *neural_network) {
    // free matrixes
    for(int i=0; i<neural_network->layer_number - 1; i++){
       matrix_delete(neural_network->AW[i]);
       matrix_delete(neural_network->BW[i]);
    }
    free(neural_network->AW);
    free(neural_network->BW);

    // free AM
    if(neural_network->type == 1){
        matrix_delete(neural_network->AM[0]);
        matrix_delete(neural_network->AM[1]);
        free(neural_network->AM);
        
        // free type_AM array
        free(neural_network->type_AM[0]);
        free(neural_network->type_AM[1]);
        free(neural_network->type_AM);
    }

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

void set_SD_neurons(struct NN *neural_network, struct Matrix *data, int type, int where){
    // where: 0 - start, 1 - end;

    int limit     = where == 0 ? neural_network->neurons_size[1] : neural_network->neurons_size[neural_network->layer_number - 2];
    int index_col = where == 0 ? 0 : 1;
    for(int i=0; i<limit; i++){
        if(type == neural_network->type_AM[i][index_col]){
            // if type is D then value should be negative to reflect operation of substraction
            if (type == 1){
                neural_network->AM[index_col]->matrix[i][0] = data->matrix[i][0] * -1;
            }  else{
                neural_network->AM[index_col]->matrix[i][0] = data->matrix[i][0];
            }
        }
    }
}

void one_calculation(struct NN *neural_network, struct Matrix *input, struct Matrix *output){
    for(int i=0; i<neural_network->layer_number - 1; i++){
        // perform W*input
        matrix_multiply(neural_network->AW[i], input, output);

        // delete the matrix to create new pointer for future loop 
        matrix_delete(input);
        struct Matrix *input = (struct Matrix*)malloc(sizeof(struct Matrix));

        if( i != neural_network->layer_number - 2){
            // perform  - Bias
            int type = 0; // for sub action
            matrix_subst_add(output, neural_network->BW[i], input, type);

            // clear the output
            matrix_delete(output);
            struct Matrix *output = (struct Matrix*)malloc(sizeof(struct Matrix));
            
            // perform activation function, created input for next action
            matrix_all_values_formula(input, neural_network->func_ptr);
        } else {
            // perform activation avoiding Bias for last calculation
            matrix_all_values_formula(output, neural_network->func_ptr);
        }

        // if the type is SD 
        if(neural_network->type == 1){
            struct Matrix *input_sd = (struct Matrix*)malloc(sizeof(struct Matrix));

            int type;
            int where;
            // perform first layer of the 
            if(i == 1){
                // make sd action
                where = 0;
                type = 1;
                matrix_subst_add(input, neural_network->AM[0], input_sd, type);
            } else if(i == neural_network->layer_number - 3){
                where = 1;
                type = 1;
                matrix_subst_add(input, neural_network->AM[1], input_sd, type);
            }

            // save new values to SD
            type = 1; // D neuron
            set_SD_neurons(neural_network, input, type, where);
            type = 0; // S neurons
            set_SD_neurons(neural_network, input_sd, type, where);

            // re-create input matrix to continue
            matrix_delete(input);
            struct Matrix *input = (struct Matrix*)malloc(sizeof(struct Matrix));

            // copy input_sd to input
            fully_copy_matrix(input_sd, input);
            matrix_delete(input_sd);
        }
    }
}