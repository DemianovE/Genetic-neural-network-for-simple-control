#include "general/test_system_builder.h"
#include "general/systems_builder.h"

#include "general/pid_controller.h"

#include <stdlib.h>
#include <stdio.h>

#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void testSelectSystem(void){
  float (*func_ptr)(float*);
  selectSystem(&func_ptr);

  TEST_ASSERT_TRUE(1);
}

int main(void){
  UNITY_BEGIN();

  RUN_TEST(testSelectSystem);

  return UNITY_END();
}