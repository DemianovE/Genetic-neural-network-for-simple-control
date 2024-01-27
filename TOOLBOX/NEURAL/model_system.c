#include "include/model_system.h"

#include "include/neural_network.h"

void createNNSystem(struct SystemNN *systemNN, struct NNInput *input){

  // first NN is created
  systemNN->neuralNetwork = (struct NN*)malloc(sizeof(struct NN));
  createNeuralNetwork(input, systemNN->neuralNetwork);

  // select signal and system
  systemNN->signal = (struct Signal*)malloc(sizeof(struct Signal));
  cliSignalSelector(systemNN->signal);

  int size = selectSystem(&systemNN->func_system);
    
  systemNN->dataSystem = (float*)malloc(size * sizeof(float));
  for(int i=0; i<size; i++){
      systemNN->dataSystem[i] = 0.0;
  }
  systemNN->sizeDataSystem = size;

  // set the output signal
  systemNN->output = (struct Signal*)malloc(sizeof(struct Signal));
  systemNN->output->length = systemNN->signal->length;
  systemNN->output->dt = systemNN->signal->dt;
  systemNN->output->signal = (float*)malloc(systemNN->signal->length * sizeof(float));

  // input system 
  selectInputNNFunction(&systemNN->input_sys, systemNN);
}

void clearNNSystem(struct SystemNN *systemNN){
  clearNeuralNetwork(systemNN->neuralNetwork);

  deleteSignal(systemNN->signal);
  deleteSignal(systemNN->output);

  free(systemNN->dataSystem);
  free(systemNN->inputData);
  free(systemNN->inputDataSize);

  free(systemNN);
}

void cleanNNSystem(struct SystemNN *systemNN){
  // clear output and system data
  for(int i=0; i < systemNN->signal->length; i++){
      systemNN->output->signal[i] = 0.0;
  }
  for(int i=0; i<systemNN->sizeDataSystem; i++){
      systemNN->dataSystem[i] = 0.0;
  }
  systemNN->dataSystem[1] = systemNN->signal->dt;

  // clear input data
  for(int i=0; i<systemNN->inputDataSize; i++){
      systemNN->inputData[i] = 0.0;
  }
  systemNN->inputData[0] = systemNN->signal->dt;

  systemNN->steadyRiseCheck = 1;
  systemNN->maxCounter = 0;
}
