#ifndef FIT_FUNCTIONS_H
#define FIT_FUNCTIONS_H

#include "population.h"
#include "../../GENERAL/include/pid_controller.h"
#include "../../GENERAL/include/signal_designer.h"

#include <stdio.h>

// function to get fit value of the pid designed controller
void pidFitFunction(struct Pop *population, float *fit, struct PID *pid);

#endif