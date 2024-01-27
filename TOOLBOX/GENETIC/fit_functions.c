#include "include/fit_functions.h"

#include "include/population.h"
#include "../GENERAL/include/pid_controller.h"
#include "../GENERAL/include/signal_designer.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void pidFitFunction(struct Pop *population, float *fit, struct PID *pid){
  int csv = 0;
  FILE *trash;

  for(int i=0; i<population->rows; i++){
    // clear system memory before running
    for(int j=0; j<pid->sizeDataSystem; j++){
      pid->dataSystem[j] = 0.0;
    }

    // first set the coeficients
    pid->Kp   = population->pop[i][0];
    pid->Ki   = population->pop[i][1];
    pid->Kd   = population->pop[i][2];
    pid->tauD = population->pop[i][3];

    makeSimulationOfSignal(pid, trash, csv);

    fit[i] = pid->fit;
    
  }
}
