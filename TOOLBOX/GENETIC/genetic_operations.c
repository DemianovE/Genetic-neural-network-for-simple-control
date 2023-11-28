#include  "include/genetic_operations.h"
#include "../GENETIC/include/population.h"
#include "../GENERAL/include/sort.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void create_input_pop_custom(struct InputPop *inputPop, int rows, struct Pop *population){
  inputPop->cols = population->cols;
  inputPop->rows = rows;

  inputPop->S    = (int**)malloc(2 * sizeof(int));
  inputPop->S[0] = (int *)malloc(inputPop->cols * sizeof(int));
  inputPop->S[1] = (int *)malloc(inputPop->cols * sizeof(int));

  inputPop->S[0] = population->S[0];
  inputPop->S[1] = population->S[1];
}



struct Pop* selbest(float* fit, int length, struct Pop* population, struct Pop* new_population, int* selects, int size, int way){
  // if way == 1 -> from lowest to highest
  // if way == 0 -> from highest to lowest
  // this function is selecting best values out of the pop

  int rows = 0;
  for(int i=0; i<size; i++){
    rows += selects[i];
  }

  int* result = (int*)malloc(length * sizeof(int));

  quick_sort(fit, result, length);


  int index = 0;
  if(way == 0){
    index = 0;
  } else if(way == 1){
    index = length -1;
  } else{
    fprintf(stderr, "Error: way should be 0 or 1\n");
    exit(EXIT_FAILURE);
  }

  struct InputPop *inputPop = (struct InputPop*)malloc(sizeof(struct InputPop));
  create_input_pop_custom(inputPop, rows, population);

  create_structure(inputPop, new_population);
  free(inputPop);

  int global_index = 0;
  for(int i=0; i<size; i++){
    int num = selects[i];
    for(int y=0; y<num; y++){
      for(int x=0; x<population->cols; x++){
        new_population->pop[global_index][x] = population->pop[result[index]][x];
      }
      global_index++;
    }
    if(way == 0){
      index++;
    } else{
      index--;
    }
  }
  free(result);
  return new_population;
}

void crosov(struct Pop* population, int* selects, int size){

  int index = 0;
  while(index < population->rows - 1){

    for(int i = 0; i<size; i++){
      int start = selects[i];
      int end = 0;

      if(i==size - 1){
        end = population->cols;
      } else{
        end = selects[i+1];
      }

      int* first  = (int*)malloc((end - start) * sizeof(int));
      int* second = (int*)malloc((end - start) * sizeof(int));
      for(int x = start; x<end; x++){
        first[x]  = population->pop[index][x];
        second[x] = population->pop[index+1][x];
      }
      for(int x = start; x<end; x++){
        population->pop[index][x]   = second[x];
        population->pop[index+1][x] = first[x];
      }
      free(first);
      free(second);
      i++;
    }
    index += 2;
    
  }
}

void mutx(struct Pop* population, float chance){
  float randomFloat;

  for(int x=0; x<population->rows; x++){
    for(int y=0; y<population->cols; y++){
      if(randomFloat < chance){
        randomFloat = (rand() % (population->S[0][y] - population->S[1][y] + 1)) + population->S[1][y];
        population->pop[x][y] = randomFloat;
      }
    }
  }

}