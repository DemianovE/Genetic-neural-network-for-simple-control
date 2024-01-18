#include "include/fit_functions.h"

#include "include/population.h"
#include "../GENERAL/include/pid_controller.h"
#include "../GENERAL/include/signal_designer.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void pidFitFunction(struct Pop *population, float *fit, struct PID *pid, FILE *csvFile){
  float fitValue;

  for(int i=0; i<population->rows; i++){
    // clear system memory before running
    for(int j=0; j<pid->sizeDataSystem; j++){
      pid->dataSystem[j] = 0.0;
    }
    pid->dataSystem[1] = pid->signal->dt;

    // first set the coeficients
    pid->Kp = population->pop[i][0];
    pid->Ki = population->pop[i][1];
    pid->Kd = population->pop[i][2];

    int csv = 0;
    makeSimulationOfSignal(pid, csvFile, csv);

    // now calculate the fit value
    fitValue = 0;
    for(int j=0; j<pid->output->length; j++){
      fitValue += fabs(pid->signal->signal[j] - pid->output->signal[j]);
    }
    fit[i] = fitValue;
    
  }
}
