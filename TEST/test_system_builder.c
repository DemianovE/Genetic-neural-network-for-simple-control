#include "include/test_system_builder.h"
#include "../TOOLBOX/GENERAL/include/systems_builder.h"

#include "../TOOLBOX/GENERAL/include/pid_controller.h"

#include <stdlib.h>
#include <stdio.h>

// used to print testing outputs
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int testSelectSystem(){
  printf(ANSI_BOLD "=======TEST SELECT SYSTEM STARTED=======" ANSI_COLOR_RESET "\n");

  
  float (*func_ptr)(float);
  struct PID *pid = (struct PID*)malloc(sizeof(struct PID));
  selectSystem(&func_ptr);

  deletePid(pid);

  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST SELECT SYSTEM SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}