#include "include/test_sort.h"
#include "../TOOLBOX/GENERAL/include/sort.h"

#include "../TOOLBOX/GENETIC/include/fit_functions.h"
#include "../TOOLBOX/GENETIC/include/genetic_operations.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


// used to print testing outputs
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

float getMinFit(float *fit, int length){
  float min = fit[0];

  for(int i=0; i<length; i++){
    if( min > fit[i]){
      min = fit[i];
    }
  }
  return min;
}

int testPIDRun(){
  printf(ANSI_BOLD "=======TEST PID RUN STARTED=======" ANSI_COLOR_RESET "\n");

  FILE *csvFile = fopen("TOOLBOX/PYTHON/input/data_pid_run.csv", "w");
  fprintf(csvFile, "best\n");

  FILE *csvFile2 = fopen("TOOLBOX/PYTHON/input/data_pid_.csv", "w");
  fprintf(csvFile2, "P,I,D,CV,RV\n");

  float chance = 0.1;
  int generations = 5000;
  int bestIndex[]    = {0, 100};
  int randOneIndex[] = {100, 550};
  int randTwoIndex[] = {550, 1000};

  int bestNums[] = {40, 20, 20, 20};
  int *restCros  = (int*)malloc(2 * sizeof(int));
  restCros[0] = 1;
  restCros[1] = 2;

  float bestFit;

  // create first the population
  struct InputPop *input = (struct InputPop*)malloc(sizeof(struct InputPop));
  struct Pop *pop = (struct Pop*)malloc(sizeof(struct Pop));
  float max[]  = { 1.0,  0.1,  0.1};
  float min[]  = {-1.0, -0.1, -0.1};
  //EST PID: 0.509101 0.002693 0.059616
  int size[]   = {1000, 3};

  createInputPop(input, max, min, size);
  createStructure(input, pop);

  float *fit = (float*)malloc(pop->rows * sizeof(float));

  // then PID is created
  struct PID *pid = (struct PID*)malloc(sizeof(struct PID));
  createNewPidController(pid);

  // set deffault min_max values
  pid->iMax = 50;
  pid->iMin = -50;

  for(int i=0; i<generations; i++){
    
    pidFitFunction(pop, fit, pid, csvFile2);
    bestFit = getMinFit(fit, pop->rows);

    fprintf(csvFile, "%f\n", bestFit);
    if(i % 100 == 0){
      printf("GENERATION[%d] - %f\n", i, bestFit);
    }
    

    struct Pop *bestPop = (struct Pop*)malloc(sizeof(struct Pop));
    struct Pop *randPopOne = (struct Pop*)malloc(sizeof(struct Pop));
    struct Pop *randPopTwo = (struct Pop*)malloc(sizeof(struct Pop));

    // now the genetic operations are runned

    // the best pop with 50 records is created
    selbest(fit, pop->rows, pop, bestPop, bestNums, 4, 1);
    
    // 2 rand arrays are created
    selrand(pop, randPopOne, 450);
    selrand(pop, randPopTwo, 450);

    // now crosov is run
    int *restCrosOne  = (int*)malloc(2 * sizeof(int));
    restCrosOne[0] = 1;
    restCrosOne[1] = 2;
    crosov(randPopOne, restCrosOne, 2);
    int *restCrosTwo  = (int*)malloc(2 * sizeof(int));
    restCrosTwo[0] = 1;
    restCrosTwo[1] = 2;
    crosov(randPopTwo, restCrosTwo, 2);

    // and finnaly the mutx
    mutx(randPopOne, chance);
    mutx(randPopTwo, chance);

    // now copy pops to main pop
    placePartOfPop(pop, bestPop, bestIndex);
    placePartOfPop(pop, randPopOne, randOneIndex);
    placePartOfPop(pop, randPopTwo, randTwoIndex);

    if(i == generations - 1){
      // plot best values
      pid->Kp = bestPop->pop[0][0];
      pid->Ki = bestPop->pop[0][1];
      pid->Kd = bestPop->pop[0][2];
      makeSimulationOfSignal(pid, csvFile2, 1);
      printf("BEST PID: %f %f %f\n", pid->Kp, pid->Ki, pid->Kd);
    }

    clearPopulation(bestPop);
    clearPopulation(randPopOne);
    clearPopulation(randPopTwo);

  }  

  clearPopulation(pop);

  deletePid(pid);

  fclose(csvFile);

  free(restCros);
  free(fit);

  fclose(csvFile2);

  plotGraph();

  int flag = 1;
  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST PID RUN FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST PID RUN SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}