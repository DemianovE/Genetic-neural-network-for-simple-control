#ifndef MODEL_SYSTEM_H
#define MODEL_SYSTEM_H

#include "neural_network.h"
#include "../../GENERAL/include/matrix_math.h"
#include "../../GENERAL/include/signal_designer.h"
#include "../../GENERAL/include/systems_builder.h"

// this struct has all information needed for the NN run of the system
typedef struct SystemNN {

  struct NN *neuralNetwork; // NN used in the system

  // input values
  struct Signal *signal;    // structure which contains the siggnal used in the system 
  float (*func_system)(float*); // function pointer to the system simulated

  // memory of output
  struct Signal *output; // the array of output values
  float *dataSystem;     // memory used by the system
  int sizeDataSystem;    // size of data_system saving point

  float (*input_sys)(float*); // function pointer to the system simulated
  float  *inputData;     // memory for the input system
  int    *inputDataSize; // the vector containing all nececary information about data [start, end, full]

  float fit; // fit value of the run

  // checks
  int steadyRiseCheck; // same as in pid
  int maxCounter; // same as in pid
}SystemNN;

#endif