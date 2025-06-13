#include "genetic/test_population.h"
#include "genetic/population.h"

#include <stdlib.h>
#include <stdio.h>

#include "unity/unity.h"

Population *population;
const float max[]  = {10.0, 100.0, -10.0};
const float min[]  = {.0, 50.0, -20.0};

void setUp(void){
  const int size[] = {3, 3};

  population = createFilledPopulation(max, min,  size);
}

void tearDown(void){
  clearPopulation(population);
}

void testCreateFilledPopulation(void){
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(population->S[0], max, 3);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(population->S[1], min, 3);

  for(int i=0; i<population->rows; i++){
    for(int j=0; j<population->cols; j++) TEST_ASSERT_TRUE(population->pop[i][j] > population->S[1][j] || population->pop[i][j] < population->S[0][j]);
  }
}

int main(){
  UNITY_BEGIN();

  RUN_TEST(testCreateFilledPopulation);

  return UNITY_END();
}