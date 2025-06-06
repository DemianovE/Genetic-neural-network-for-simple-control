#ifndef PLOTTING_TOOLBOX_H
#define PLOTTING_TOOLBOX_H

#include "general/signal_designer.h"
// general call for python plot graph code
void plotGraph();

// NN specific plot Pythinn function call
void plotGraphNN();

// macro to run the graph
#define RUN_GRAPH(command) do {                                     \
  char cmd[256];                                                    \
  snprintf(cmd, sizeof(cmd), "python3 data/python/%s.py", command); \
  system(cmd);                                                      \
} while(0);

#endif
