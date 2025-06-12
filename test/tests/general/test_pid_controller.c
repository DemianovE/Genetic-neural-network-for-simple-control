#include "general/test_pid_controller.h"

#include "general/pid_controller.h"

#include <stdlib.h>
#include <stdio.h>
#include "unity/unity.h"

PID *pid;
FILE *csvFile;

void setUp(void) {
  pid = malloc(sizeof(PID));
  createNewPidController(pid);

  csvFile = fopen("data_pid_.csv", "w");
  fprintf(csvFile, "P,I,D,CV,RV\n");
}
void tearDown(void) {
  deletePid(pid);
  fclose(csvFile);
}

void testPIDCreate(void){
  pid->Kp = 1;
  pid->Ki = 1;
  pid->Kd = 0;

  pid->limMax = 10;
  pid->limMin = -10;

  pid->limMaxInt = pid->limMax / 2;
  pid->limMinInt = pid->limMin / 2;

  makeSimulationOfSignal(pid, csvFile, 1);

  printf("%f\n",pid->fit);

  TEST_ASSERT_TRUE(1);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(testPIDCreate);

  return UNITY_END();
}