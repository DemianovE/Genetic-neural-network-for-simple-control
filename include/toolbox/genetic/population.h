#ifndef POPULATION_H
#define POPULATION_H

#include <stddef.h>

// structure used to store population
typedef struct Population {
    float **pop; // population matrix
    float **S;   // matrix of max and min for each column
    int cols;    // number of columns  of population
    int rows;    // number of rows of population
}Population;

/*
 * This function is used to create population from InputPop structure
 * Input:
*     InputPop *inputPop - the inputPop struct pointer
 *    float* max -.the pointer to float array of max matrix
 *    float* min -.the pointer to float array of min matrix
 *    int* size - the pointer to int array of population size matrix
 * Output;
 *    Pop* - pointer to the created population
 */
Population* createFilledPopulation(const float* max, const float* min, const int* size);

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

#define CLEAR_MATRIX_UNTIL(matrix, count_to_free) do { \
    if (matrix != NULL) {                              \
        for (int i = 0; i < (count_to_free); i++) {    \
            if (matrix[i] != NULL) {                   \
                free(matrix[i]);                       \
                matrix[i] = NULL;                      \
            }                                          \
        }                                              \
    }                                                  \
} while (0)

// macro to make redundant check of the inputPop or pop
#define ASSERT_POPULATION(item) do {                                                            \
    assert(item != NULL &&  "population(input) pointer should not be empty!");                     \
    assert(item->S != NULL &&  "population(input) size matrix should not be empty!");              \
                                                                                                \
    assert(item->S[0] != NULL &&  "population(input) size max array should not be empty!");        \
    assert(item->S[1] != NULL &&  "population(input) size min array matrix should not be empty!"); \
                                                                                                \
    assert(item->rows > 0 && "Population(input) rows must be positive");                        \
    assert(item->cols > 0 && "Population(input) columns must be positive");                     \
} while (0);

#endif
