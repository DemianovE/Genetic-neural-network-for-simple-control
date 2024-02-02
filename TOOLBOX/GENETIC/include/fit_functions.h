#ifndef FIT_FUNCTIONS_H
#define FIT_FUNCTIONS_H

#include "population.h"
#include "../../GENERAL/include/pid_controller.h"
#include "../../GENERAL/include/signal_designer.h"
#include "../../NEURAL/include/model_system.h"


#include <stdio.h>

// function to get fit value of the pid designed controller
void pidFitFunction(struct Pop *population, float *fit, struct PID *pid);

// function to get fir values of the nn system population
void nnFitFunction(struct Pop *population, float *fit, struct SystemNN *systemNN);

#endif