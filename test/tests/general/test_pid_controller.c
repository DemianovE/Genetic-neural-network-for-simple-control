#include "general/test_pid_controller.h"

#include "general/pid_controller.h"
#include "general/plotting_toolbox.h"

#include <stdlib.h>
#include <stdio.h>
#include "unity/unity.h"

void setUp() {}
void tearDown() {}

void testPIDCreate(){
  PID *pid = malloc(sizeof(struct PID));
  createNewPidController(pid);

  FILE *csvFile = fopen("data_pid_.csv", "w");
  fprintf(csvFile, "P,I,D,CV,RV\n");

  pid->Kp = 1;
  pid->Ki = 1;
  pid->Kd = 0;

  pid->limMax = 10;
  pid->limMin = -10;

  pid->limMaxInt = pid->limMax / 2;
  pid->limMinInt = pid->limMin / 2;

  makeSimulationOfSignal(pid, csvFile, 1);

  printf("%f\n",pid->fit);
  plotGraph();

  deletePid(pid);
  fclose(csvFile);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(testPIDCreate);

  return UNITY_END();
}