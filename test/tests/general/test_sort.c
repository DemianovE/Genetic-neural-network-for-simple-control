#include "general/test_sort.h"
#include "general/sort.h"

#include <stdlib.h>
#include <stdio.h>

#include "../../../external/unity/unity.h"
#include "unity/unity.h"

void setUp(void) {}
void tearDown(void) {}

void testQuicksort(void){
  const int length = 5;
  float fit[] = {9.6, 3.4, 10, 4.6, 0.4};

  int *result = malloc(length*sizeof(int));
  for(int i=0; i<length; i++){
    result[i] = i;
  }

  const int resultCorrect[] = {4, 1, 3, 0, 2};

  quickSort(fit, result, length);

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(result, resultCorrect, length);
  free(result);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(testQuicksort);

  return UNITY_END();
}