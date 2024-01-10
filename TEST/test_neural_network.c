#include "include/test_neural_network.h"

#include "../TOOLBOX/NEURAL/include/neural_network.h"
#include "../TOOLBOX/GENETIC/include/population.h"
#include "../TOOLBOX/GENERAL/include/matrix_math.h"

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

int arrays_equal_nn(int *arr1, int *arr2, int size) {
    for (int i = 0; i < size; ++i) {
        if (arr1[i] != arr2[i]) {
            return 0; 
        }
    }
    return 1; 
}

int check_matrixes_nn(struct NN *neural_network, float *population){
  int global_index = 0;
  int flag = 1;
  
  for(int i=0; i<neural_network->layer_number - 1; i++){
    // first the AW matrix is set
    for(int x=0; x<neural_network->AW[i]->sizes[0]; x++){
      for(int y=0; y<neural_network->AW[i]->sizes[1]; y++){
        if(neural_network->AW[i]->matrix[x][y] != population[global_index]){
          flag = 0;
        }
        global_index++;
      }
    }

    
    // second the BW is set
    if( i < neural_network->layer_number - 2){
      for(int x=0; x<neural_network->BW[i]->sizes[0]; x++){
        for(int y=0; y<neural_network->BW[i]->sizes[1]; y++){
          if(neural_network->BW[i]->matrix[x][y] != population[global_index]){
            flag = 0;
          }
          global_index++;
        }
      }
    }
  }
  return flag;
}

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
  input->denormalization_matrix[1][0] = 0.0;

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

  int neurons_size[] = {1, 5, 5, 1};
  int layer_type[]   = {0, 1, 0, 0};

  float normalization_max[] = {100};
  float normalization_min[] = {0.0};

  float de_normalization_max[] = {100};
  float de_normalization_min[] = {0.0};

  int sd_types_1[] = {0, 0, 1, 2, 2};
  
  int row_sd[] = {5, 1};

  int flag1 = arrays_equal_nn(neurons_size, neural_network->neurons_size, neural_network->layer_number);
  int flag2 = arrays_equal_nn(layer_type,   neural_network->layer_type,   neural_network->layer_number);
  int flag3 = arrays_equal_nn(layer_type,   neural_network->layer_type,   neural_network->layer_number);

  int flag4 = arrays_equal_nn(normalization_max,   neural_network->normalization_matrix[0],   1);
  int flag5 = arrays_equal_nn(normalization_min,   neural_network->normalization_matrix[1],   1);

  int flag6 = arrays_equal_nn(de_normalization_max,   neural_network->denormalization_matrix[0],   1);
  int flag7 = arrays_equal_nn(de_normalization_min,   neural_network->denormalization_matrix[1],   1);

  int flag8 = arrays_equal_nn(sd_types_1,   neural_network->sd_neurons_types[0],   5);

  int flag9 = arrays_equal_nn(row_sd,   neural_network->SD_memory[0]->sizes,   2);

  clear_neural_network(neural_network);
  
  if(flag1 == 0 || flag2 == 0 || flag3 == 0 || flag4 == 0 || flag5 == 0 || flag6 == 0 || flag7 == 0 || flag8 == 0 || flag9 == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST NEURAL NETWORK CREATE FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST NEURAL NETWORK CREATE SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}

int test_fill_matrixes_nn(){
  printf(ANSI_BOLD "=======TEST FILL MATRIXES NN STARTED=======" ANSI_COLOR_RESET "\n");

  struct NN *neural_network = (struct NN*)malloc(sizeof(struct NN));

  create_simple_neural_network(neural_network);

  struct InputPop *input = (struct InputPop*)malloc(sizeof(struct InputPop));
  struct Pop *pop = (struct Pop*)malloc(sizeof(struct Pop));
  int size[] = {1, neural_network->count_of_values};
  float *max = (float*)malloc(neural_network->count_of_values * sizeof(float));
  float *min = (float*)malloc(neural_network->count_of_values * sizeof(float));
  for(int i=0; i<neural_network->count_of_values; i++){
    max[i] = 10.0;
    min[i] =  0.0;
  }

  create_input_pop(input, max, min, size);
  create_structure(input, pop);

  fill_matrixes_nn(neural_network, pop->pop[0]);

  
  int flag = check_matrixes_nn(neural_network, pop->pop[0]);

  clear_neural_network(neural_network);
  clear_population(pop);
  free(min);
  free(max);

  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST FILL MATRIXES NN FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST FILL MATRIXES NN SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}

int test_de_normalization_process(){
  printf(ANSI_BOLD "=======TEST DE_NORMALIZATION PROCESS STARTED=======" ANSI_COLOR_RESET "\n");

  struct NN *neural_network = (struct NN*)malloc(sizeof(struct NN));
  struct Matrix *A  = (struct Matrix*)malloc(sizeof(struct Matrix));

  int *sizes1 = (int *)malloc(2 * sizeof(int));
  sizes1[0] = 1;
  sizes1[1] = 1;
  int way = 0;
  int flag = 1;

  create_simple_neural_network(neural_network);
  create_matrix(A, sizes1);

  A->matrix[0][0] = 50;
  de_normalization_process(neural_network, A, way);
  if(A->matrix[0][0] != 0.0){
    flag = 0;
  }

  A->matrix[0][0] = 0.40;
  way = 1;
  de_normalization_process(neural_network, A, way);

  if(A->matrix[0][0] != 70.0){
    flag = 0;
  }


  matrix_delete(A);
  clear_neural_network(neural_network);

  
  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST DE_NORMALIZATION PROCESS FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST DE_NORMALIZATION PROCESS SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}

int test_one_calculation(){
  printf(ANSI_BOLD "=======TEST ONE CALCULATION STARTED=======" ANSI_COLOR_RESET "\n");

  struct NN *neural_network = (struct NN*)malloc(sizeof(struct NN));
  create_simple_neural_network(neural_network);
  
  struct Matrix *input = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *output = (struct Matrix*)malloc(sizeof(struct Matrix));

  int *size = (int *)malloc(2 * sizeof(int));
  size[0] = 1;
  size[1] = 1;

  create_matrix(input, size);
  input->matrix[0][0] = 80;


  struct Pop *pop = (struct Pop*)malloc(sizeof(struct Pop));
  struct InputPop *inputPop = (struct InputPop*)malloc(sizeof(struct InputPop));
  int sizePop[] = {1, neural_network->count_of_values};
  float *max = (float*)malloc(neural_network->count_of_values * sizeof(float));
  float *min = (float*)malloc(neural_network->count_of_values * sizeof(float));
  for(int i=0; i<neural_network->count_of_values; i++){
    max[i] =  1.0;
    min[i] = -1.0;
  }


  create_input_pop(inputPop, max, min, sizePop);
  create_structure(inputPop, pop);
  

  fill_matrixes_nn(neural_network, pop->pop[0]);
  one_calculation(neural_network, input, output);

  printf("Result output:\n");
  for(int i=0; i<output->sizes[0];i++){
    for(int j=0;j<output->sizes[1];j++){
      printf("%f ", output->matrix[i][j]);
    }
    printf("\n");
  }
  printf("Result SD memory:\n");
  for(int i=0; i<neural_network->SD_memory[0]->sizes[0];i++){
    for(int j=0;j<neural_network->SD_memory[0]->sizes[1];j++){
      printf("%f ", neural_network->SD_memory[0]->matrix[i][j]);
    }
    printf("\n");
  }

  clear_neural_network(neural_network);
  clear_population(pop);
  matrix_delete(output);
  free(max);
  free(min);

  int flag = 1;
  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST ONE CALCULATION FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST DONE CALCULATION SUCCESSFU L=======" ANSI_COLOR_RESET "\n");
  return 1;
}