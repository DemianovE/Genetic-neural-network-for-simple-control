#include "TOOLBOX/GENETIC/include/population.h"
#include "TOOLBOX/GENERAL/include/general.h"
#include "TOOLBOX/GENERAL/include/sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void create_input_pop(struct InputPop *inputPop, int* max, int* min){
  inputPop->cols = 5;
  inputPop->rows = 5;

  inputPop->S    = (int**)malloc(2 * sizeof(int*));
  inputPop->S[0] = (int* )malloc(inputPop->cols * sizeof(int));
  inputPop->S[1] = (int* )malloc(inputPop->cols * sizeof(int));

  for(int i=0; i < inputPop->cols; i++){
    inputPop->S[0][i] = max[i]; // maximum of population
    inputPop->S[1][i] = min[i]; // minimum of population
  }
}



int main(){
  srand(time(0));

  int max_pop[] = {10, 1, 7, 90,  1000}; 
  int min_pop[] = {0,  0, 0, 10, -1000};
  struct InputPop *inputPop = (struct InputPop*)malloc(sizeof(struct InputPop));
  create_input_pop(inputPop, max_pop, min_pop);

  struct Pop *population = (struct Pop*)malloc(sizeof(struct Pop));
  create_structure(inputPop, population);
  free(inputPop);

  clear_population(population);
  return 0;
}

