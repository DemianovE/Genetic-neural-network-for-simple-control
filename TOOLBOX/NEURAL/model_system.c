#include "include/model_system.h"

#include "include/neural_network.h"
#include "../GENERAL/include/signal_designer.h"
#include "../GENERAL/include/matrix_math.h"


#include <float.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void createNNSystem(struct SystemNN *systemNN, struct NNInput *input){

  // input system 
  selectInputNNFunction(&systemNN->input_sys, systemNN);

  // make input size be the same as the input system needs
  input->neuronsSize[0] = systemNN->inputDataSize[2] - 1;

  // now empty de_norm are created
  input->normalizationMatrix   = (float**)malloc(2 * sizeof(float*));
  input->denormalizationMatrix = (float**)malloc(2 * sizeof(float*));

  input->normalizationMatrix[0]   = (float*)malloc(input->neuronsSize[0] * sizeof(float));
  input->normalizationMatrix[1]   = (float*)malloc(input->neuronsSize[0] * sizeof(float));

  input->denormalizationMatrix[0] = (float*)malloc(sizeof(float));
  input->denormalizationMatrix[1] = (float*)malloc(sizeof(float));

  // first NN is created
  systemNN->neuralNetwork = (struct NN*)malloc(sizeof(struct NN));
  createNeuralNetwork(input, systemNN->neuralNetwork);

  // select signal and system
  systemNN->signal = (struct Signal *)malloc(sizeof(struct Signal));
  
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

static void cleanNNSystem(struct SystemNN *systemNN){
  // clear output and system data
  for(int i=0; i < systemNN->signal->length; i++){
      systemNN->output->signal[i] = 0.0;
  }
  for(int i=0; i<systemNN->sizeDataSystem; i++){
      systemNN->dataSystem[i] = 0.0;
  }
  systemNN->dataSystem[1] = systemNN->signal->dt;

  // clear input data
  for(int i=0; i<systemNN->inputDataSize[0]; i++){
      systemNN->inputData[i] = 0.0;
  }
  systemNN->inputData[0] = systemNN->signal->dt;

  systemNN->steadyRiseCheck = 1;
  systemNN->maxCounter = 0;

  systemNN->fit = 0.0;
}

static void getMaxMinSignalValues(struct Signal *signal, float *max, float *min){
  *max = 0.0; // max
  *min = 0.0; // min of system

  for(int i=0; i<signal->length; i++){
    if(signal->signal[i] > *max){
      *max = signal->signal[i];
    } else if (signal->signal[i] < *min){
      *min = signal->signal[i];
    }
  }
}

static float findUOneRound(struct SystemNN *systemNN, float *forValues, float *maxSig){
  float analyzedValue; 
  float finValue, sysOutput;
  float maxCreate = *maxSig * 5;

  float min = FLT_MAX;
  finValue = 0;
  for(float curValue = forValues[0]; curValue < forValues[1]; curValue += forValues[2]){
    analyzedValue = 0;

    // first the data of the system is reseted
    for(int j=0; j<systemNN->sizeDataSystem; j++){
        systemNN->dataSystem[j] = 0.0;
    }
    systemNN->dataSystem[1] = systemNN->signal->dt;

    // now the idea is to simulate 0.5s with the u set to curValue, finnal value is then analyzed
    for(float j=0; j< systemNN->signal->dt * 10; j += systemNN->signal->dt){
      systemNN->dataSystem[0] = curValue;
      sysOutput = systemNN->func_system(systemNN->dataSystem);
    }

    analyzedValue = maxCreate - sysOutput;
    if(analyzedValue < 0){
      analyzedValue *= (-1);
    }

    if(analyzedValue < min){
      min = analyzedValue;
      finValue = curValue;
    }
  }
  return finValue;
}

static float findUForSystemAndSignal(struct SystemNN *systemNN, float *maxSig){

  float forValueOne[] = {-100000000.0, 100000000.0, 1000.0};
  float roundOne = findUOneRound(systemNN, &forValueOne, maxSig);

  float forValueTwo[] = {roundOne - 1000.0, roundOne + 1000.0, 100.0};
  float roundTwo = findUOneRound(systemNN, &forValueTwo, maxSig);

  float forValueThree[] = {roundTwo - 100.0, roundTwo + 100.0, 10.0};
  float finValue = findUOneRound(systemNN, &forValueThree, maxSig);

  return finValue;
}

static float makeDerivation(float *x, float *x_t, float *dt){
  return (*x - *x_t) / *dt;
}

void createDeNormalization(struct SystemNN *systemNN){
  // first all generic normalizations are created into array and then the NN normalization is filled
  // the filling is controlled by the inputTypes

  float **normalization = (float**)malloc(2 * sizeof(float*));

  normalization[0] = (float*)malloc(12 * sizeof(float)); // create max
  normalization[1] = (float*)malloc(12 * sizeof(float)); // create min

  // get min and max of function

  float maxSig;
  float minSig;
  float maxChange;
  float maxChangeReverse;

  getMaxMinSignalValues(systemNN->signal, &maxSig, &minSig);

  // e 
  normalization[0][0]  = maxSig - systemNN->minSys;
  normalization[1][0]  = minSig - systemNN->maxSys;

  maxChange        = maxSig - minSig;
  maxChangeReverse = maxChange * -1;

  // u
  printf("%f -- %f\n", maxSig, minSig);
  normalization[0][1]  = findUForSystemAndSignal(systemNN, &maxChange);
  normalization[1][1]  = findUForSystemAndSignal(systemNN, &maxChangeReverse);

  // y
  normalization[0][2]  = systemNN->minSys;
  normalization[1][2]  = systemNN->maxSys;

  // de 
  normalization[0][3]  = makeDerivation(&normalization[0][0], &normalization[1][0], &systemNN->signal->dt); // bigest possible result
  normalization[1][3]  = makeDerivation(&normalization[1][0], &normalization[0][0], &systemNN->signal->dt); // smallest possible result

  // dde 
  normalization[0][4]  = makeDerivation(&normalization[0][3], &normalization[1][3], &systemNN->signal->dt); // bigest possible result
  normalization[1][4]  = makeDerivation(&normalization[1][3], &normalization[0][3], &systemNN->signal->dt); // smallest possible result

  // ie
  normalization[0][5]  = (normalization[0][0] * (float)systemNN->signal->length) / (float)systemNN->signal->dt;
  normalization[1][5]  = (normalization[1][0] * (float)systemNN->signal->length) / (float)systemNN->signal->dt;

  // du 
  normalization[0][6]  = makeDerivation(&normalization[0][1], &normalization[1][1], &systemNN->signal->dt); // bigest possible result
  normalization[1][6]  = makeDerivation(&normalization[1][1], &normalization[0][1], &systemNN->signal->dt); // smallest possible result

  // ddu 
  normalization[0][7]  = makeDerivation(&normalization[0][6], &normalization[1][6], &systemNN->signal->dt); // bigest possible result
  normalization[1][7]  = makeDerivation(&normalization[1][6], &normalization[0][6], &systemNN->signal->dt); // smallest possible result

  // iu
  normalization[0][8]  = (normalization[0][1] * (float)systemNN->signal->length) / (float)systemNN->signal->dt;
  normalization[1][8]  = (normalization[1][1] * (float)systemNN->signal->length) / (float)systemNN->signal->dt;

  // dy
  normalization[0][9]  = makeDerivation(&normalization[0][2], &normalization[1][2], &systemNN->signal->dt); // bigest possible result
  normalization[1][9]  = makeDerivation(&normalization[1][2], &normalization[0][2], &systemNN->signal->dt); // smallest possible result

  // ddy 
  normalization[0][10] = makeDerivation(&normalization[0][9], &normalization[1][9], &systemNN->signal->dt); // bigest possible result
  normalization[1][10] = makeDerivation(&normalization[1][9], &normalization[0][9], &systemNN->signal->dt); // smallest possible result

  // iy
  normalization[0][11] = (normalization[0][2] * (float)systemNN->signal->length) / (float)systemNN->signal->dt;
  normalization[1][11] = (normalization[1][2] * (float)systemNN->signal->length) / (float)systemNN->signal->dt;

  // now the normalization values are added to the de_normalization matrix of NN
  for(int i = 0; i < systemNN->inputDataSize[2] - 1; i++){
    systemNN->neuralNetwork->normalizationMatrix[0][i] = normalization[0][systemNN->inputTypes[i]];
    systemNN->neuralNetwork->normalizationMatrix[1][i] = normalization[1][systemNN->inputTypes[i]];
    printf("%d - MAX: %f MIN: %f\n", i, systemNN->neuralNetwork->normalizationMatrix[0][i], systemNN->neuralNetwork->normalizationMatrix[1][i]);
  }

  systemNN->neuralNetwork->denormalizationMatrix[0][0] = normalization[0][1];
  systemNN->neuralNetwork->denormalizationMatrix[1][0] = normalization[1][1];

  free(normalization[0]);
  free(normalization[1]);
  free(normalization);

  // the inputTypes will not be needed, so the array can be free
  free(systemNN->inputTypes);
}

void makeSimulationOfSignalNN(struct SystemNN *systemNN, FILE *csvFile, int csv){
  cleanNNSystem(systemNN);

  
  float error, diff;
  float neuralOutput = 0.0;
  float systemOutput = 0.0;

  int matrixIndex;

  float max = 0.0;

  for(int i=1; i<systemNN->signal->length; i++){

    error = systemNN->signal->signal[i] - systemNN->output->signal[i-1];

    // now the input for the NN is generated
    systemNN->inputData[1] = error;        // e
    systemNN->inputData[2] = neuralOutput; // u
    systemNN->inputData[3] = systemOutput; // y

    systemNN->input_sys(systemNN->inputData);

    // now the input matrix is created and filled
    struct Matrix *inputMatrix  = (struct Matrix*)malloc(sizeof(struct Matrix));
    struct Matrix *outputMatrix = (struct Matrix*)malloc(sizeof(struct Matrix));

    int *inputSize = (int *)malloc(2 * sizeof(int));
    inputSize[0] = systemNN->neuralNetwork->neuronsSize[0];
    inputSize[1] = 1;

    createMatrix(inputMatrix, inputSize);
    clearSDMemory(systemNN->neuralNetwork);

    matrixIndex = 0;
    for(int j=systemNN->inputDataSize[1]; j<systemNN->inputDataSize[2]; j++){
      inputMatrix->matrix[matrixIndex][0] = systemNN->inputData[j];
      matrixIndex++;
    }

    // now the matrix calculation can be made
    oneCalculation(systemNN->neuralNetwork, inputMatrix, outputMatrix);

    if(outputMatrix->matrix[0][0] > max){
      max = outputMatrix->matrix[0][0];
    }

    systemNN->dataSystem[0] = outputMatrix->matrix[0][0]; // the values of the calculation
    neuralOutput = systemNN->dataSystem[0]; // the next round u is set for input

    // set data and pass to system
    systemNN->output->signal[i] = systemNN->func_system(systemNN->dataSystem);
    float original = systemNN->output->signal[i];

    if(systemNN->output->signal[i] > systemNN->maxSys){
        systemNN->output->signal[i] = systemNN->maxSys;
        systemNN->maxCounter++;
    } else if(systemNN->output->signal[i] < systemNN->minSys){
        systemNN->output->signal[i] = systemNN->minSys;
        systemNN->maxCounter++;
    }
    systemOutput = systemNN->output->signal[i]; // y is set for next round input

    if(csv == 1){
      fprintf(csvFile, "%f,%f,%f,%f\n", systemNN->output->signal[i], systemNN->signal->signal[i], original, systemNN->output->signal[i]);
    } 

    diff = systemNN->signal->signal[i] - systemNN->output->signal[i];
    systemNN->fit += diff > 0 ? diff : diff * (-1);

    if(systemNN->output->signal[i-1] > systemNN->output->signal[i]){
        systemNN->steadyRiseCheck = 0;
    }

    matrixDelete(outputMatrix);
  }
  if(csv == 1){
    printf("%f\n", max);
  }
  

  if(systemNN->steadyRiseCheck == 1){
    systemNN->fit =  FLT_MAX; // make fit max value to not consider the steady rise solutions
  } else if(systemNN->maxCounter > systemNN->signal->length * 1 / 100){
    systemNN->fit += 10000;
  }

}