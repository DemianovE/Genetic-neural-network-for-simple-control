#include "include/test_neural_network.h"

#include "../TOOLBOX/NEURAL/include/neural_network.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// used to print testing outputs
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void create_simple_neural_network(struct NN *neural_network){
  struct NNInput *input = (struct NNInput*)malloc(sizeof(struct NNInput));

  input->neurons_size = (int*)malloc(4 * sizeof(int));
  input->neurons_size[0] = 1;
  input->neurons_size[1] = 5;
  input->neurons_size[2] = 5;
  input->neurons_size[3] = 1;

  input->layer_number = 4;

  input->normalization_matrix   = (float**)malloc(2 * sizeof(float*));
  input->denormalization_matrix = (float**)malloc(2 * sizeof(float*));

  input->normalization_matrix[0]   = (float*)malloc(sizeof(float));
  input->normalization_matrix[1]   = (float*)malloc(sizeof(float));

  input->denormalization_matrix[0] = (float*)malloc(sizeof(float));
  input->denormalization_matrix[1] = (float*)malloc(sizeof(float));

  input->normalization_matrix[0][0]   = 100;
  input->normalization_matrix[1][0]   = .0;

  input->denormalization_matrix[0][0] = 100;
  input->denormalization_matrix[1][0] = .0;

  input->layer_type = (int*)malloc(input->layer_number * sizeof(int));
  input->layer_type[0] = 0;
  input->layer_type[1] = 1;
  input->layer_type[2] = 0;
  input->layer_type[3] = 0;

  input->sd_number = 1;

  create_neural_network(input, neural_network);
}

int test_neural_network_create(){
  printf(ANSI_BOLD "=======TEST NEURAL NETWORK CREATE STARTED=======" ANSI_COLOR_RESET "\n");

  struct NN *neural_network = (struct NN*)malloc(sizeof(struct NN));

  create_simple_neural_network(neural_network);

  clear_neural_network(neural_network);
  
  int flag = 0;
  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST NEURAL NETWORK CREATE FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST NEURAL NETWORK CREATE SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}