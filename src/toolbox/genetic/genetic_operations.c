#include "genetic/genetic_operations.h"

#include "genetic/population.h"
#include "general/sort.h"
#include "general/general_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

// this code is a C implementation of the code created by prof. Ivan Sekaj STU 2002 using Matlab

Population* selectBest(float *fit, const Population *population, const int *selects, const int selectsLength, const int way){
  /*
   * int rows - number of rows in the newPopulation
   * int* result - the indexing of the sorted array on the places
   * int resultIndex - the indexing used to access results. Depends on the way
   * int globalIndex - index in the newPopulation
   */
  assert(way == 0 || way == 1); // make sure way is in the range
  assert(population != NULL); // make sure the population exists
  assert(selectsLength > 0); // make sure we have the select
  assert(selectsLength <= population->rows); // make sure it is not going out of population scope

  int rows = 0;

  int* result = malloc(population->rows * sizeof(int));
  if (result == NULL){ perror("Failed to allocate support result array"); exit(EXIT_FAILURE);}

  for(int i=0; i<selectsLength; i++){
    rows += selects[i];
  }
  for(int i=0; i<population->rows; i++){
    result[i] = i;
  }

  assert(rows > 0); // make sure the number of new rows is more than 0
  quickSort(fit, result, population->rows);

  // now depending on the way the starting index is selected
  int resultIndex = (way == 0) ? population->rows -1 : 0;

  const int size[] = {rows, population->cols};
  Population *newPopulation = createFilledPopulation(population->S[0], population->S[1], size);

  // the main purpose of this loop is iterated though that selects and add new rows to new population based on the sorted fit and old population
  int globalIndex = 0;
  for (int i = 0; i < selectsLength; i++){
    for (int y = 0; y < selects[i]; y++){
      // the desired row is copied to the population
      memcpy(newPopulation->pop[globalIndex], population->pop[result[resultIndex]], newPopulation->cols * sizeof(float));
      globalIndex++;
    }
    resultIndex = (way == 0) ? resultIndex - 1 : resultIndex + 1;
  }

  free(result);

  return newPopulation;
}

Population* selectRandom(const Population *population, const int rows){
  /*
   * const int index - the index of the gene
   */

  assert(population != NULL);
  assert(rows > 0);

  const int size[] = {rows, population->cols};
  Population *newPopulation = createFilledPopulation(population->S[0], population->S[1], size);

  for(int i=0; i<rows; i++){
    const int index  = rand() % population->rows;
    memcpy(newPopulation->pop[i], population->pop[index], population->cols * sizeof(float));
  }

  return newPopulation;
}

Population* selectTournament(const Population *population, const float* fit, const int rows){
  /*
  * const int index - the index of the gene
  * const int j - index of one of random genes from population
  * const int k - index of one of random genes from population
  */

  assert(population != NULL); // check if the population exists
  assert(rows > 0); // check if the rows are greater than 0
  assert(fit != NULL); // check if the fit exists

  const int size[] = {rows, population->cols};
  Population *newPopulation = createFilledPopulation(population->S[0], population->S[1], size);
  
  for(int i=0; i<rows; i++){
    const int j = rand() % population->rows;
    const int k = rand() % population->rows;

    if(j == k){
      memcpy(newPopulation->pop[i], population->pop[j], population->cols * sizeof(float));
    } else if (fit[j] <= fit[k]){
      memcpy(newPopulation->pop[i], population->pop[j], population->cols * sizeof(float));
    } else{
      memcpy(newPopulation->pop[i], population->pop[k], population->cols * sizeof(float));
    }
  }

  return newPopulation;
}

void crossover(const Population *population, int *selects, int selectsLength){
  /*
  * const int start - index of the start of current frame
  * const int end - index of the end of current frame
  * float *additionalSaving - array for the temporary storing of the frame
  * int globalIndex - index for the frame going through additionalSaving
  */

  assert(population != NULL); // check if the population exists
  assert(selectsLength > 0); // check if there are frames

  // add one more index in case the number is odd
  if(selectsLength % 2 != 0){
    selects = (int *)realloc(selects, (selectsLength + 1) * sizeof(int));
    selects[selectsLength] = population->cols;
    selectsLength++;
  }

  for(int index = 0; index < population->rows - 1; index += 2){
    
    for(int i = 0; i<selectsLength; i+=2){
      const int start = selects[i];
      const int end   = selects[i + 1];

      float *additionalSaving = malloc((end - start) * sizeof(float));
      int globalIndex = 0;

      for(int x = start; x<end; x++){
        additionalSaving[globalIndex]  = population->pop[index][x];
        globalIndex++;
      }
      globalIndex = 0;

      for(int x = start; x<end; x++){
        population->pop[index][x]   = population->pop[index+1][x];
        population->pop[index+1][x] = additionalSaving[globalIndex];
        globalIndex++;
      }
      free(additionalSaving);
    }
  }
  free(selects);
}

void mutx(const Population *population, const float chance){
  /*
  * float randomFloat - the value which is a modified chromosome
  */
  assert(population != NULL); // check if the population exists
  assert(chance > 0); // check if the chance of mutation exists

  for(int x=0; x<population->rows; x++){
    for(int y=0; y<population->cols; y++){
      float randomFloat = (float)rand() / RAND_MAX;
      if(randomFloat < chance){
        randomFloat = createRandomFloat(population->S[1][y], population->S[0][y]);
        population->pop[x][y] = randomFloat;
      }
    }
  }

}