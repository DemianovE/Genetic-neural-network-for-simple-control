#ifndef POPULATION_H
#define POPULATION_H

#include <stddef.h>

#include "matrix_math.h"

// structure used to store population
typedef struct Population {
    Matrix *populationMatrix; // population matrix
    Matrix *minMaxMatrix;     // matrix of max and min for each column
}Population;

/*
 * This function is used to create population from InputPop structure
 * Input:
*     const float* minMax - the array of siye [1, cols*2] which holds the min and max values of the matrix
 *    const int rows -.the number of rows of the matrix
 *    const int cols -.the number of cols in the matrix
 * Output;
 *    Pop* - pointer to the created population
 */
Population* createFilledPopulation(const float* minMax, const int rows, const int cols);

/*
 * This function is used to clear population
 * Input:
 *    Pop *population - the population struct pointer
 * Output;
 *    There is no output in the function, but the population is manipulated instead
 */
void clearPopulation(Population* population);

/*
 * This function is used to copy rows from the source to pop between two indexes in the index array, not including the second one
 * Input:
 *    Pop *population - the population struct pointer
 *    Pop *source - the population struct pointer which is used as a source of the rows
 *    int *indexes - the pointer to int array of list of intended to be copied rows
 * Output;
 *    There is no output in the function, but the population is manipulated instead
 */
void copyPartOfPop(const Population *population, const Population *source, const int *indexes);

/*
 * This function is used to re-generate random population in the size matrix
 * Input:
 *    Pop *population - the population struct pointer
 * Output;
 *    There is no output in the function, but the population is manipulated instead
 */
void generateRandomPopulation(const Population *population);

// macro to make redundant check of the inputPop or pop
#define ASSERT_POPULATION(item) do {                                                                       \
    assert(item != NULL &&  "population pointer should not be empty!");                                    \
    assert(item->populationMatrix != NULL &&  "population size matrix should not be empty!");              \
    assert(item->minMaxMatrix     != NULL &&  "population size max and min matrix should not be empty!");  \
} while (0);

#endif
