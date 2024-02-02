#include "include/ploting_toolbox.h"

#include "include/signal_designer.h"

#include <stdio.h>
#include <stdlib.h>



void plotGraph() {

    const char *command = "python3 TOOLBOX/PYTHON/ploting_code.py";

    int status = system(command);
}


void plotGraphNN() {

    const char *command = "python3 TOOLBOX/PYTHON/ploting_code_NN.py";

    int status = system(command);
}