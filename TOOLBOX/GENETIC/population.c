#include "include/population.h"
#include "../GENERAL/include/general.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

void alocate_population(struct InputPop* input, struct Pop* population){
  population->cols = input->cols;
  population->rows = input->rows;

  population->pop = (float **)malloc(population->rows * sizeof(float *));
  for (int i = 0; i < population->rows; i++) {
    population->pop[i] = (float *)malloc(population->cols * sizeof(float));
  }

  population->S    = (int**)malloc(2 * sizeof(int));
  population->S[0] = (int* )malloc(population->cols * sizeof(int));
  population->S[1] = (int* )malloc(population->cols * sizeof(int));

  population->S[0] = input->S[0];
  population->S[1] = input->S[1];
}


void create_structure(struct InputPop *input, struct Pop *population) {
    int randomInt;
    float newValue;

    alocate_population(input, population);

    for(int y = 0; y < population->rows; y++){
      for(int i=0; i < population->cols; i++ ){
        newValue = (rand() % (input->S[0][i] - input->S[1][i] + 1)) + input->S[1][i];
        population->pop[y][i] = newValue;
      }
      printf("\n");
    }
}
