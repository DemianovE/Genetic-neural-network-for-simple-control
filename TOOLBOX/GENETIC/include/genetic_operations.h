#ifndef GENERIC_OPERATIONS_H
#define GENERIC_OPERATIONS_H

#include <stddef.h>

// is used to select best gens of population based on fit function output and create new population
struct Pop* selbest(float* fit, int length, struct Pop* population, struct Pop* new_population, int* selects, int size, int way);

// is used to do crossover of the gens of population and return population
void crosov(struct Pop* population, int* selects, int size);

// is used to mutate with chance the values of gen
void mutx(struct Pop* population, float chance);
#endif
