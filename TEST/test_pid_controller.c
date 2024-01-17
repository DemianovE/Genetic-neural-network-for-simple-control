#include "include/test_pid_controller.h"

#include "../TOOLBOX/GENERAL/include/pid_controller.h"
#include "../TOOLBOX/GENERAL/include/ploting_toolbox.h"

#include <stdlib.h>
#include <stdio.h>

// used to print testing outputs
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int testPIDCreate(){
  printf(ANSI_BOLD "=======TEST PID CREATE STARTED=======" ANSI_COLOR_RESET "\n");

  struct PID *pid = (struct PID*)malloc(sizeof(struct PID));
  createNewPidController(pid);

  FILE *csvFile = fopen("TOOLBOX/PYTHON/input/data_pid_.csv", "w");
  fprintf(csvFile, "P,I,D,CV,RV\n");

  pid->Kp = 0.1;
  pid->Ki = 0.01;
  pid->Kd = 0.001;

  pid->iMax = 5.0;
  pid->iMin = -5.0;

  int csv = 1;

  makeSimulationOfSignal(pid, csvFile, csv);

  plotGraph();

  deletePid(pid);
  int flag = 1;

  fclose(csvFile);

  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST PID CREATE FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST PID CREATE SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}