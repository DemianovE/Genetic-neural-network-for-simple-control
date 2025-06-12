#ifndef GENETIC_OPERATIONS_H
#define GENETIC_OPERATIONS_H

#include "genetic/population.h"

/*
 * This function is used to select best gens of population based on fit function output and create new population
 * Input:
 *    float *fit - pointer to the fit array based on which the select is made
 *    int fitLength - the length of the fit array
 *    const Pop *population - population struct pointer which is used to create new population
 *    Pop *newPopulation - empty population struct pointer which will be filled with new values
 *    const int *selects - array of values which shows which genes to add. Example: [1, 0, 2]. Means 1 best and 2 third-best genes to be added
 *    const int selectsLength - length of the selected array
 *    const int way - value it which shows if the count is from best to worst or vice versa. 1 -> from lowest to highest, 0 -> from highest to lowest
 * Output;
 *    There is no output in the function, but the newPopulation is manipulated instead
 */
void selectBest(float *fit, const Pop *population, Pop *newPopulation, const int *selects, const int selectsLength, const int way);

/*
 * This function is used to select is used to select random genes to result in new population
 * Input:
 *    Pop *population - population struct pointer which is used to create new population
 *    Pop *newPopulation - empty population struct pointer which will be filled with new values
 *    int rows - number of genes required in new population
 * Output;
 *    There is no output in the function, but the newPopulation is manipulated instead
 */
void selectRandom(const Pop *population, Pop *newPopulation, const int rows);

/*
 * This function is used to select is used to select by turn genes for new population
 * Input:
 *    Pop *population - population struct pointer which is used to create new population
 *    float* fit - the array of fit values of the population
 *    Pop *newPopulation - empty population struct pointer which will be filled with new values
 *    int rows - number of genes required in new population
 * Output;
 *    There is no output in the function, but the newPopulation is manipulated instead
 */
void selectTournament(const Pop *population, const float* fit, Pop *newPopulation, const int rows);

/*
 * This function is used to do crossover of the gens of population and return population
 * Input:
 *    Pop *population - population struct pointer on which changes are made
 *    int *selects - the indexes of the splits of genes
 *    int selectsLength - number of splits of genes in selects
 * Output;
 *    There is no output in the function, but the population is manipulated instead
 */
void crossover(const Pop *population, int *selects, int selectsLength);

/*
 * This function is used to mutate with chance the values of gen
 * Input:
 *    Pop *population - population struct pointer on which changes are made
 *    float chance - the chance of the mutation of one chromosome of the gene
 * Output;
 *    There is no output in the function, but the population is manipulated instead
 */
void mutx(const Pop *population, const float chance);

#endif
