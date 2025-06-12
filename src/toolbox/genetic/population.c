#include "genetic/population.h"
#include "general/general_math.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearPopulation(Population* population) {
  printf("delete\n");
  fflush(stdout);
  if (population == NULL) { return; }
  assert(population->pop && population->S);

  // free the pop part
  for (int i = 0; i < population->rows; i++) {
    free(population->pop[i]);
  }
  free(population->pop);

  // free the S part
  free(population->S[0]);
  free(population->S[1]);
  free(population->S);

  // free population struct
  free(population);
}

static Population* createPopulationFromData(const float* max, const float* min, const int* size){
  assert(max  != NULL &&  "Max values array should not be empty!");
  assert(min  != NULL &&  "Min values array should not be empty!");
  assert(size != NULL &&  "Size values array should not be empty!");

  assert(size[0] > 0 && "Population rows must be positive");
  assert(size[1] > 0 && "Population columns must be positive");

  Population *population = NULL;
  population = malloc(sizeof(Population));
  if (population == NULL){ perror("Failed to allocate Population struct"); exit(EXIT_FAILURE); }

  population->rows = size[0];
  population->cols = size[1];

  population->S = NULL;
  population->pop = NULL;

  population->pop = (float **)malloc(population->rows * sizeof(float *));
  if (population->pop == NULL) { perror("Failed to allocate Population matrix"); free(population); exit(EXIT_FAILURE); }

  for (int i = 0; i < population->rows; i++) {
    population->pop[i] = NULL;
    population->pop[i] = (float *)malloc(population->cols * sizeof(float));
    if (population->pop[i] == NULL) { perror("Failed to allocate Population "
                                             "matrix row"); CLEAR_MATRIX_UNTIL(population->pop, i); free(population->pop); free(population); exit(EXIT_FAILURE); }
  }

  population->S    = (float**)malloc(2 * sizeof(float*));
  if (population->S == NULL) { perror("Failed to allocate Population "
                                      "Size matrix"); CLEAR_MATRIX_UNTIL(population->pop, population->rows); free(population->pop); free(population); exit(EXIT_FAILURE);}

  population->S[0] = NULL;
  population->S[1] = NULL;

  population->S[0] = (float* )malloc(population->cols * sizeof(float));
  if (population->S[0] == NULL) { perror("Failed to allocate Population Size min array");
                                  free(population->S); CLEAR_MATRIX_UNTIL(population->pop, population->rows); free(population->pop); free(population); exit(EXIT_FAILURE);}

  population->S[1] = (float* )malloc(population->cols * sizeof(float));
  if (population->S[1] == NULL) { perror("Failed to allocate Population Size max array");
                                  free(population->S[0]); free(population->S); CLEAR_MATRIX_UNTIL(population->pop, population->rows); free(population->pop);
                                  free(population); exit(EXIT_FAILURE);}


  memcpy(population->S[0], max, population->cols * sizeof(float));
  memcpy(population->S[1], min, population->cols * sizeof(float));

  return population;
}

void generateRandomPopulation(const Population *population){
  ASSERT_POPULATION(population);
  assert(population->pop != NULL &&  "population pop matrix should not be empty!");
  assert(population->S != NULL &&  "population S array should not be empty!"); // hack to prevent warning; This is done i macro

  for(int y = 0; y < population->rows; y++){
    for(int i=0; i < population->cols; i++ ){

      const float newValue = createRandomFloat(population->S[1][i], population->S[0][i]);
      population->pop[y][i] = newValue;
    }
  }
}

Population* createFilledPopulation(const float* max, const float* min, const int* size) {

  Population *population = createPopulationFromData(max, min, size);
  generateRandomPopulation(population);

  return population;
}

void copyPartOfPop(const Population *population, const Population *source, const int *indexes){
  ASSERT_POPULATION(population);
  assert(population->pop != NULL &&  "population pop matrix should not be empty!");

  ASSERT_POPULATION(source);
  assert(source->pop != NULL &&  "source pop matrix should not be empty!");

  // the rows of the source are placed into pop between two indexes in the indexes, not including the second index
  int globalIndex = 0;
  for(int i=indexes[0]; i<indexes[1]; i++){
    memcpy(population->pop[i], source->pop[globalIndex], source->cols * sizeof(float));
    globalIndex++;
  }
}
