#ifndef NN_H
#define NN_H

#include "../../GENERAL/include/matrix_math.h"

// struct used to store and use NN
typedef struct NN{
    struct MyStruct **AW; // all layers vweights connecting them (matrix of matrixes)
    struct MyStruct **BW; // all values of biases of each level

    int *neurons_size;  // matrix of number of neurons per layer incl. input and output
    int  layer_number;  // number representing the number of layers incl. input and output
    // using layer_number we can get all values of neurons_size, from which we can get respective matrixes sizes

    int  count_of_values; // number of values needed to fill all matrixes, is used to generate population

    float **normalization_matrix;   // matrix of all normalization values max and min. Max is on 0 row, min on 1
    float **denormalization_matrix; // matrix of all denormalization values max and mins 
    // number of normalization max/min pairs should be same as the number of inpputs. Same for denormalization and outputs
}NN;

// struct used to deffine needed values for NN to be created
typedef struct NNInput{
    int *neurons_size; // matrix of number of neurons per layer incl. input and output
    int  layer_number; // number representing the number of layers incl. input and output

    float **normalization_matrix;  // matrix of all normalization values max and min. Max is on 0 row, min on 1
    float **denormalization_matrix; // matrix of all denormalization values max and mins 
}NNInput;

// function to create new neural network out of input structure and deletion of the input structure at the end
void create_neural_network(struct NNInput *input, struct NN *neural_network);

// function to delete neural network 
void clear_neural_network(struct NN *neural_network);

#endif