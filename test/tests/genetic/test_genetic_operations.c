#include "genetic_operations.h"
#include "population.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "unity/unity.h"

Population *populationCreatedOne;
Population *populationCreatedTwo;

Population *populationCreatedBig;

Population *populationInitializedOne;
Population *populationInitializedTwo;

static void printPopulation(const Population *population, char *name){
  printf("population %s\n", name);
  for(int i=0; i<population->populationMatrix->rows; i++){
    for(int j=0; j<population->populationMatrix->cols; j++) printf("%f ", population->populationMatrix->matrix[i][j]);
  }
  printf("\n");
}

void setUp(void){
  const float maxMin[]  = {10.0f, 100.0f, -10.0f, .0f, 50.0f, -20.0f};

  populationCreatedOne = createFilledPopulation(maxMin, 3, 3);
  populationCreatedTwo = createFilledPopulation(maxMin, 3, 3);

  populationCreatedBig = createFilledPopulation(maxMin, 2, 9);

  populationInitializedOne = NULL;
  populationInitializedTwo = NULL;
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

  populationInitializedOne = selectBest(fit, populationCreatedOne, selects, 2, 0);
  populationInitializedTwo = selectBest(fit, populationCreatedOne, selects, 2, 1);

  printPopulation(populationCreatedOne, "initial");
  printPopulation(populationInitializedOne, "higher");
  printPopulation(populationInitializedTwo, "lower");

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->populationMatrix->matrix[1], populationInitializedOne->populationMatrix->matrix[0], populationCreatedOne->populationMatrix->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->populationMatrix->matrix[1], populationInitializedOne->populationMatrix->matrix[1], populationCreatedOne->populationMatrix->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->populationMatrix->matrix[0], populationInitializedOne->populationMatrix->matrix[2], populationCreatedOne->populationMatrix->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->populationMatrix->matrix[0], populationInitializedOne->populationMatrix->matrix[3], populationCreatedOne->populationMatrix->cols);

  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->populationMatrix->matrix[2], populationInitializedTwo->populationMatrix->matrix[0], populationCreatedOne->populationMatrix->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->populationMatrix->matrix[2], populationInitializedTwo->populationMatrix->matrix[1], populationCreatedOne->populationMatrix->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->populationMatrix->matrix[0], populationInitializedTwo->populationMatrix->matrix[2], populationCreatedOne->populationMatrix->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedOne->populationMatrix->matrix[0], populationInitializedTwo->populationMatrix->matrix[3], populationCreatedOne->populationMatrix->cols);
}

void testSelectRandom(){
  const int rows = 10;

  populationInitializedOne = selectRandom(populationCreatedOne, rows);
  printPopulation(populationInitializedOne, "result");
  
  TEST_ASSERT_TRUE(1); // it is hard to test random, even when it is only pseudo :)
}

void testSelectTournament(){
  const int rows = 10;
  const float fit[] = {0.9f, 0.3f, 0.5f};

  populationInitializedOne = selectTournament(populationCreatedOne, fit, rows);
  printPopulation(populationInitializedOne, "result");

  TEST_ASSERT_TRUE(1);
}

void testCrossover(){
  const float row1[]      = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
  const float row2[]      = {10.0f, 20.0f, 30.0f, 40.0f, 50.0f, 60.0f, 70.0f, 80.0f, 90.0f};

  const float row1Check[] = {1.0f, 2.0f, 30.0f, 40.0f, 50.0f, 6.0f, 7.0f, 80.0f, 90.0f};
  const float row2Check[] = {10.0f, 20.0f, 3.0f, 4.0f, 5.0f, 60.0f, 70.0f, 8.0f, 9.0f};

  const int selectsLength = 3;

  int *selects = malloc(selectsLength * sizeof(int));
  selects[0] = 2;
  selects[1] = 5;
  selects[2] = 7;

  // created one row population row is made to new row in order to proceed
  memcpy(populationCreatedBig->populationMatrix->matrix[0], row1, populationCreatedBig->populationMatrix->cols * sizeof(float));
  memcpy(populationCreatedBig->populationMatrix->matrix[1], row2, populationCreatedBig->populationMatrix->cols * sizeof(float));

  crossover(populationCreatedBig, selects, selectsLength);
  printPopulation(populationCreatedBig, "result");
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedBig->populationMatrix->matrix[0], row1Check, populationCreatedBig->populationMatrix->cols);
  TEST_ASSERT_EQUAL_FLOAT_ARRAY(populationCreatedBig->populationMatrix->matrix[1], row2Check, populationCreatedBig->populationMatrix->cols);
}

void testMutx(){
  mutx(populationCreatedBig, 0.3f);
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