#ifndef TEST_GENETIC_OPERATIONS_H
#define TEST_GENETIC_OPERATIONS_H

// the function to test selectBest in two ways
void testSelectBest();

// the function to test selectRandom operation
void testSelectRandom();

// the function to test selectTournament operation
void testSelectTournament();

// the function to test cross
void testCrossover();

// the function is not a test but code to test function for memory leaks
void testMutx();

// macro for printing population
#define PRINT_POPULATION(population, text) do { \
  printf("population %s\n", text);       \
  for(int i=0; i<population->rows; i++){        \
    for(int j=0; j<population->cols; j++){      \
      printf("%f ", population->pop[i][j]);     \
    }                                    \
    printf("\n");                        \
  }                                      \
} while (0)

#endif