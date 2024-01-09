#ifndef NN_H
#define NN_H

#include "../../GENERAL/include/matrix_math.h"

// struct used to store and use NN
typedef struct NN{
    struct Matrix **AW; // all layers vweights connecting them (matrix of matrixes)
    struct Matrix **BW; // all values of biases of each level

    int *neurons_size;  // matrix of number of neurons per layer incl. input and output
    int  layer_number;  // number representing the number of layers incl. input and output
    // using layer_number we can get all values of neurons_size, from which we can get respective matrixes sizes

    int  count_of_values; // number of values needed to fill all matrixes, is used to generate population

    float **normalization_matrix;   // matrix of all normalization values max and min. Max is on 0 row, min on 1
    float **denormalization_matrix; // matrix of all denormalization values max and mins 
    // number of normalization max/min pairs should be same as the number of inpputs. Same for denormalization and outputs

    float (*func_ptr)(float); // activation function pointer

    int    *layer_type; // array showing the type of each HL 0 - FF, 1 - SD

    int   **sd_neurons_types;  // matrix containing type for each neuron in the SD layer 0 - straight, 1 - S, 2 - D
    struct Matrix **SD_memory; // array of Matrixes for each SD layer
}NN;

// struct used to deffine needed values for NN to be created
typedef struct NNInput{
    int *neurons_size; // matrix of number of neurons per layer incl. input and output
    int  layer_number; // number representing the number of layers incl. input and output

    float **normalization_matrix;  // matrix of all normalization values max and min. Max is on 0 row, min on 1
    float **denormalization_matrix; // matrix of all denormalization values max and mins 

    int    *layer_type; // array showing the type of each HL 0 - FF, 1 - SD

    int  sd_number;           // the number of sd layers
}NNInput;

// function to create new neural network out of input structure and deletion of the input structure at the end
void create_neural_network(struct NNInput *input, struct NN *neural_network);

// function to delete neural network 
void clear_neural_network(struct NN *neural_network);

// function to calculate the output of network based on the input
void one_calculation(struct NN *neural_network, struct Matrix *input, struct Matrix *output);

// function to set all matrixes based on one row of population
void fill_matrixes_nn(struct NN *neural_network, float *population);

#endif