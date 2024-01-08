#include "include/population.h"

#include "../GENERAL/include/general_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

void create_input_pop(struct InputPop *inputPop, float* max, float* min, int* size){
  
  inputPop->cols = size[1];
  inputPop->rows = size[0];

  inputPop->S    = (float**)malloc(2 * sizeof(float*));
  inputPop->S[0] = (float* )malloc(inputPop->cols * sizeof(float));
  inputPop->S[1] = (float* )malloc(inputPop->cols * sizeof(float));

  memcpy(inputPop->S[0], max, inputPop->cols * sizeof(float));
  memcpy(inputPop->S[1], min, inputPop->cols * sizeof(float));
}

void alocate_population(struct InputPop* input, struct Pop* population){
  population->cols = input->cols;
  population->rows = input->rows;

  population->pop = (float **)malloc(population->rows * sizeof(float *));
  for (int i = 0; i < population->rows; i++) {
    population->pop[i] = (float *)malloc(population->cols * sizeof(float));
  }

  population->S    = (float**)malloc(2 * sizeof(float*));
  population->S[0] = (float* )malloc(population->cols * sizeof(float));
  population->S[1] = (float* )malloc(population->cols * sizeof(float));

  memcpy(population->S[0], input->S[0], population->cols * sizeof(float));
  memcpy(population->S[1], input->S[1], population->cols * sizeof(float));

  // clear the input pop
  clear_input_pop(input);
}

void clear_population(struct Pop* population) {
  if (population) {
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
}

void clear_input_pop(struct InputPop* input){
  if(input){
    free(input->S[0]);
    free(input->S[1]);
    free(input->S);
    free(input);
  }
}

void create_structure(struct InputPop *input, struct Pop *population) {
    float newValue;

    alocate_population(input, population);

    for(int y = 0; y < population->rows; y++){
      for(int i=0; i < population->cols; i++ ){
        
        newValue = create_random_float(population->S[1][i], population->S[0][i]);
        population->pop[y][i] = newValue;
      }
      printf("\n");
    }
}
