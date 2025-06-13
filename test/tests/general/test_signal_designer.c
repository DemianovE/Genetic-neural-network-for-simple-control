#include "signal_designer.h"

#include <stdlib.h>
#include "unity/unity.h"

Signal *signal;

void setUp(void){
  signal = malloc(sizeof(Signal));
}
void tearDown(void){
  deleteSignal(signal);
}

void testSignalCreate(void){
  cliSignalSelector(signal);

  TEST_ASSERT_TRUE(1);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(testSignalCreate);

  return UNITY_END();
}