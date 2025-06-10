#include "general/test_signal_designer.h"
#include "general/signal_designer.h"

#include <stdlib.h>
#include "unity/unity.h"

Signal *signal;

void setUp(){
  signal = malloc(sizeof(Signal));
}
void tearDown(){
  deleteSignal(signal);
}

void testSignalCreate(){
  cliSignalSelector(signal);

  TEST_ASSERT_TRUE(1);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(testSignalCreate);

  return UNITY_END();
}