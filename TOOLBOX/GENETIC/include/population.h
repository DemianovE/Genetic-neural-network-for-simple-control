#ifndef POPULATION_H
#define POPULATION_H

#include <stddef.h>

// strucute used to store all input values needed to create popualtion
typedef struct InputPop {
    int cols; // number of columns  of population
    int rows; // number of rows of population
    int **S;  // matrix of max and mins of each collumns in populations
}InputPop;

// structure used to store population 
typedef struct Pop {
    float **pop; // population matrix 
    int **S;     // matrix of max and min for each collumn 
    int cols;    // number of columns  of population
    int rows;    // number of rows of population
}Pop;

// function to create population from InputPop structure 
void create_structure(struct InputPop *input,  struct Pop *pop);

// function to clear population
void clear_population(struct Pop* population);

#endif
