#include "TOOLBOX/GENETIC/include/population.h"
#include "TOOLBOX/GENERAL/include/matrix_math.h"
#include "TOOLBOX/GENERAL/include/sort.h"
#include "TEST/include/test_main.h"

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

  test_matrix_all_values_formula();
}

