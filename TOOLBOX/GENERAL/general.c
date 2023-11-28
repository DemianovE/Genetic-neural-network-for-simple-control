#include "include/general.h"
#include "../GENETIC/include/population.h"

void freeMyStruct(struct Pop* population) {
  if (population) {
    for (int i = 0; i < population->rows; i++) {
      free(population->pop[i]);
    }
    free(population->pop);
    free(population);
  }
}
