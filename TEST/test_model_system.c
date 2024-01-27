#include "include/test_model_system.h"

#include "../TOOLBOX/NEURAL/include/neural_network.h"
#include "../TOOLBOX/NEURAL/include/model_system.h"

#include <stdlib.h>
#include <stdio.h>

// used to print testing outputs
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void createSystemNeuralNetworkInput(struct NNInput *input, int check){

  input->neuronsSize = (int*)malloc(4 * sizeof(int));
  input->neuronsSize[0] = 1;
  if(check == 1){
    input->neuronsSize[1] = 3;
    input->neuronsSize[2] = 2;
  } else{
    input->neuronsSize[1] = 5;
    input->neuronsSize[2] = 5;
  }
  input->neuronsSize[3] = 1;

  input->layerNumber = 4;

  input->normalizationMatrix   = (float**)malloc(2 * sizeof(float*));
  input->denormalizationMatrix = (float**)malloc(2 * sizeof(float*));

  input->normalizationMatrix[0]   = (float*)malloc(sizeof(float));
  input->normalizationMatrix[1]   = (float*)malloc(sizeof(float));

  input->denormalizationMatrix[0] = (float*)malloc(sizeof(float));
  input->denormalizationMatrix[1] = (float*)malloc(sizeof(float));

  input->normalizationMatrix[0][0]   = 100;
  input->normalizationMatrix[1][0]   = .0;

  input->denormalizationMatrix[0][0] = 100;
  input->denormalizationMatrix[1][0] = 0.0;

  input->layerType = (int*)malloc(input->layerNumber * sizeof(int));
  input->layerType[0] = 0;
  input->layerType[1] = 1;
  input->layerType[2] = 0;
  input->layerType[3] = 0;

  input->sdNumber = 1;
}

int testSystemCreate(){
  printf(ANSI_BOLD "=======TEST SYSTEM NN CREATE STARTED=======" ANSI_COLOR_RESET "\n");

  struct NNInput *input = (struct NNInput*)malloc(sizeof(struct NNInput));
  struct SystemNN *systemNN = (struct SystemNN*)malloc(sizeof(struct SystemNN));

  createSystemNeuralNetworkInput(input, 1);

  createNNSystem(systemNN, input);

  clearNNSystem(systemNN);
 
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST SYSTEM NN CREATE SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}