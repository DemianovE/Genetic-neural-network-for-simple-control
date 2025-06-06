#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "general/signal_designer.h"

#include <stdio.h>

// the structure which will hold all information needed for PID work
typedef struct PID {
  // constants aren't changed in calculations
  float Kp; // constant of P
  float Ki; // constant of I
  float Kd; // constant of D
  float tauI; // time constant can be used in the PID to make up for response time in Integral part
  float tauD; // same as tauI but for the Derivative part 

  // values used in the process of the calculations
  float prevError;      // the previous error used in D 

  float proportiError;  // the values of the P argument of the PID controller
  float integralError;  // the values of the I argument of the PID controller
  float differenError;  // the values of the D argument of the PID controller

  // input values
  Signal *signal;    // structure which contains the signal used in the system
  float (*func_system)(float*); // function pointer to the system simulated

  // memory of output
  Signal *output;    // the array of output values

  float *dataSystem;  // memory used by the system
  int sizeDataSystem; // size of data_system saving point

  // the limits for integral part
  float limMaxInt;
  float limMinInt;

  float limMax;
  float limMin;

  // the fit value of pid run
  float fit;

  // the check for steady rise pid to prevent the best PID fi value being the steady rise line
  int steadyRiseCheck;

  // the maxCounter is used to determine signals that are too oscillating and as such have too much over the limit value (>1%)
  int maxCounter;
}PID;

void createNewPidController(PID *pid);

void deletePid(PID *pid);

void makeSimulationOfSignal(PID *pid, FILE *csvFile, int csv);

// make macro for the file input
#define WRITE_TO_FILE(csv, csvFile, pid, i) do {                                                                                                      \
  if (csv == 0) {                                                                                                                                     \
    fprintf(csvFile, "%f,%f,%f,%f,%f\n", pid->proportiError, pid->integralError, pid->differenError, pid->output->signal[i], pid->signal->signal[i]); \
  }                                                                                                                                                   \
} while (0)

#endif