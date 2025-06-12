#include "genetic/test_genetic_operations.h"
#include "genetic/genetic_operations.h"
#include "genetic/population.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "unity/unity.h"

Pop *populationCreatedOne;
Pop *populationCreatedTwo;

Pop *populationCreatedBig;

Pop *populationInitializedOne;
Pop *populationInitializedTwo;

static void createPopulation(struct Pop *population, int* size){
  InputPop *input = malloc(sizeof(struct InputPop));
  float max[]  = {10.0, 100.0, -10.0};
  float min[]  = {.0, 50.0, -20.0};

  createInputPop(input, max, min, size);
  createStructure(input, population);
}

void setUp(void){
  populationCreatedOne = malloc(sizeof(Pop));
  populationCreatedTwo  = malloc(sizeof(Pop));

  populationCreatedBig  = malloc(sizeof(Pop));

  populationInitializedOne = malloc(sizeof(Pop));
  populationInitializedTwo = malloc(sizeof(Pop));

  int size[] = {3, 3};
  int sizeBig[] = {2, 9};

  createPopulation(populationCreatedOne, size);
  createPopulation(populationCreatedTwo, size);

  createPopulation(populationCreatedBig, sizeBig);
}

void tearDown(void){
  clearPopulation(populationCreatedOne);
  clearPopulation(populationCreatedTwo);

  clearPopulation(populationCreatedBig);

  clearPopulation(populationInitializedOne);
  clearPopulation(populationInitializedTwo);
}

void testSelectBest(){
  float fit[]       = {-1, 15, -3};
  const int selects[]     = {2, 2};

  selectBest(fit, populationCreatedOne, populationInitializedOne, selects, 2, 0);
  selectBest(fit, populationCreatedOne, populationInitializedTwo,  selects, 2, 1);

  PRINT_POPULATION(populationCreatedOne, "initial");
  PRINT_POPULATION(populationInitializedOne, "higher");
  PRINT_POPULATION(populationInitializedTwo, "lower");

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->pop[1], populationInitializedOne->pop[0], populationCreatedOne->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->pop[1], populationInitializedOne->pop[1], populationCreatedOne->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->pop[0], populationInitializedOne->pop[2], populationCreatedOne->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->pop[0], populationInitializedOne->pop[3], populationCreatedOne->cols);

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->pop[2], populationInitializedTwo->pop[0], populationCreatedOne->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->pop[2], populationInitializedTwo->pop[1], populationCreatedOne->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->pop[0], populationInitializedTwo->pop[2], populationCreatedOne->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->pop[0], populationInitializedTwo->pop[3], populationCreatedOne->cols);
}

void testSelectRandom(){
  const int rows = 10;

  selectRandom(populationCreatedOne, populationInitializedOne, rows);
  PRINT_POPULATION(populationInitializedOne, "result");
  
  TEST_ASSERT_TRUE(1); // it is hard to test random, even when it is only pseudo :)
}

void testSelectTournament(){
  const int rows = 10;
  const float fit[] = {0.9, 0.3, 0.5};

  selectTournament(populationCreatedOne, fit, populationInitializedOne, rows);
  PRINT_POPULATION(populationInitializedOne, "result");

  TEST_ASSERT_TRUE(1);
}

void testCrossover(){
  const float row1[]      = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0};
  const float row2[]      = {10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0};

  const float row1Check[] = {1.0, 2.0, 30.0, 40.0, 50.0, 6.0, 7.0, 80.0, 90.0};
  const float row2Check[] = {10.0, 20.0, 3.0, 4.0, 5.0, 60.0, 70.0, 8.0, 9.0};

  const int selectsLength = 3;

  int *selects = malloc(selectsLength * sizeof(int));
  selects[0] = 2;
  selects[1] = 5;
  selects[2] = 7;

  // created one row population row is made to new row in order to proceed
  memcpy(populationCreatedBig->pop[0], row1, populationCreatedBig->cols * sizeof(float));
  memcpy(populationCreatedBig->pop[1], row2, populationCreatedBig->cols * sizeof(float));

  crossover(populationCreatedBig, selects, selectsLength);
  PRINT_POPULATION(populationCreatedBig, "result");
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedBig->pop[0], row1Check, populationCreatedBig->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedBig->pop[1], row2Check, populationCreatedBig->cols);
}

void testMutx(){
  mutx(populationCreatedBig, 0.3);
  TEST_ASSERT_TRUE(1);
}

int main (void){
  UNITY_BEGIN();

  RUN_TEST(testSelectBest);
  RUN_TEST(testSelectRandom);
  RUN_TEST(testSelectTournament);
  RUN_TEST(testCrossover);
  RUN_TEST(testMutx);

  return UNITY_END();
}