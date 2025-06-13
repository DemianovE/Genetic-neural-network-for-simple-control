#include "population.h"
#include "general_math.h"
#include "matrix.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearPopulation(Population* population) {
  if (population == NULL) { return; }
  assert(population->populationMatrix && population->minMaxMatrix);

  MatrixDelete(population->minMaxMatrix);
  MatrixDelete(population->populationMatrix);

  // free population struct
  free(population);
}

static Population* createPopulationFromData(const float* minMax, const int rows, const int cols){
  assert(minMax  != NULL &&  "Min/Max values array should not be empty!");

  assert(rows > 0 && "Population rows must be positive");
  assert(cols > 0 && "Population columns must be positive");

  Population *population = NULL;
  population = malloc(sizeof(Population));
  if (population == NULL){ perror("Failed to allocate Population struct"); exit(EXIT_FAILURE); }

  population-> populationMatrix = MatrixCreate(rows,  cols);
  population->minMaxMatrix = MatrixCreateFromPointer(minMax, 2, population->populationMatrix->cols);

  return population;
}

Population* createFilledPopulationWithSizeMatrix(const Matrix *minMaxMatrix, const int rows, const int cols){
  assert(minMaxMatrix != NULL &&  "Min/Max values matrix should not be empty!");
  assert(rows > 0 && "Population rows must be positive");
  assert(cols > 0 && "Population columns must be positive");

  Matrix *copy = MatrixMakeCopy(minMaxMatrix);
  MatrixReshape(copy, 1, minMaxMatrix->cols * minMaxMatrix->rows);

  Population *population = createFilledPopulation(copy->matrix[0], rows, cols);
  MatrixDelete(copy);

  return population;
}


Population* createFilledPopulation(const float* minMax, const int rows, const int cols){
  assert(minMax != NULL &&  "Min/Max values array should not be empty!");
  assert(rows > 0 && "Population rows must be positive");
  assert(cols > 0 && "Population columns must be positive");

  Population *population = createPopulationFromData(minMax, rows, cols);
  generateRandomPopulation(population);

  return population;
}

void generateRandomPopulation(const Population *population){
  ASSERT_POPULATION(population);
  assert(population->populationMatrix != NULL && "hack to make sure empty possibility is disabled");
  assert(population->minMaxMatrix     != NULL && "hack to make sure empty possibility is disabled");

  for(int y = 0; y < population->populationMatrix->rows; y++){
    for(int i=0; i < population->populationMatrix->cols; i++ ){

      const float newValue = createRandomFloat(population->minMaxMatrix->matrix[1][i], population->minMaxMatrix->matrix[0][i]);
      population->populationMatrix->matrix[y][i] = newValue;
    }
  }
}

void copyPartOfPop(const Population *population, const Population *source, const int *indexes){
  ASSERT_POPULATION(population);
  assert(population->populationMatrix != NULL &&  "population pop matrix should not be empty!");

  ASSERT_POPULATION(source);
  assert(source->populationMatrix != NULL &&  "source pop matrix should not be empty!");

  // the rows of the source are placed into pop between two indexes in the indexes, not including the second index
  int globalIndex = 0;
  for(int i=indexes[0]; i<indexes[1]; i++){
    memcpy(population->populationMatrix->matrix[i], source->populationMatrix->matrix[globalIndex], source->populationMatrix->cols * sizeof(float));
    globalIndex++;
  }
}
