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

int getMinFit(float *fit, int length){
  int min = 0;

  for(int i=0; i<length; i++){
    if( fit[min] > fit[i]){
      min = i;
    }
  }
  return min;
}

int testPIDRun(){
  printf(ANSI_BOLD "=======TEST PID RUN STARTED=======" ANSI_COLOR_RESET "\n");

  FILE *csvFile = fopen("TOOLBOX/PYTHON/input/data_pid_run.csv", "w");
  fprintf(csvFile, "best\n");

  float chance = 0.1;
  int generations = 5000;
  int bestIndex[]    = {0,   10};
  int randOneIndex[] = {10,  195};
  int randTwoIndex[] = {195, 380};
  int randFulIndex[] = {380, 500};

  int sizeOneIndex = 185;
  int sizeTwoIndex = 185;

  int bestNums[] = {4, 2, 2, 2};
  int *restCros  = (int*)malloc(2 * sizeof(int));
  restCros[0] = 1;
  restCros[1] = 2;

  int bestFit;

  // create first the population
  struct InputPop *input = (struct InputPop*)malloc(sizeof(struct InputPop));
  struct Pop *pop = (struct Pop*)malloc(sizeof(struct Pop));
  //              |    P      |   I    |    D     | tau |
  float max[]  = {  1000000.0, 10000.0,  100000.0, 10.0};
  float min[]  = {   100000.0,   100.0,   10000.0,  0.0};

  int size[]    = {500, 4};
  int sizeFul[] = {120, 4};

  createInputPop(input, max, min, size);
  createStructure(input, pop);

  float *fit = (float*)malloc(pop->rows * sizeof(float));

  // then PID is created
  struct PID *pid = (struct PID*)malloc(sizeof(struct PID));
  createNewPidController(pid);  // then PID is created

  // set deffault min_max values

  // set deffault min_max values
  pid->limMax =  60.0;
  pid->limMin = -60.0;

  pid->limMaxInt = pid->limMax / 2.0;
  pid->limMinInt = pid->limMin / 2.0;

  for(int i=0; i<generations; i++){
    
    
    pidFitFunction(pop, fit, pid);
    bestFit = getMinFit(fit, pop->rows);
    
    
    fprintf(csvFile, "%f\n", fit[bestFit]);
    if(i % 100 == 0 || i>9990){
      printf("GENERATION[%05d] - fit: %f P: %f I: %f D: %f Tau: %f - %d\n", i, fit[bestFit], pop->pop[bestFit][0], pop->pop[bestFit][1], pop->pop[bestFit][2], pop->pop[bestFit][3], bestFit);
    }
    

    struct Pop *bestPop    = (struct Pop*)malloc(sizeof(struct Pop));
    struct Pop *randPopOne = (struct Pop*)malloc(sizeof(struct Pop));
    struct Pop *randPopTwo = (struct Pop*)malloc(sizeof(struct Pop));

    // now the genetic operations are runned
   
    // the best pop with 50 records is created
    selbest(fit, pop->rows, pop, bestPop, bestNums, 4, 1);

    // 2 seturn arrays are created
    selturn(pop, fit, randPopOne, sizeOneIndex);
    selturn(pop, fit, randPopTwo, sizeTwoIndex);

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

    // add the random 200 at the end of each generation
    struct InputPop *input = (struct InputPop*)malloc(sizeof(struct InputPop));
    struct Pop *popRandom  = (struct Pop*)malloc(sizeof(struct Pop));
    createInputPop(input, max, min, sizeFul);
    createStructure(input, popRandom);

    // now copy pops to main pop
    placePartOfPop(pop, bestPop,    bestIndex);
    placePartOfPop(pop, randPopOne, randOneIndex);
    placePartOfPop(pop, randPopTwo, randTwoIndex);
    placePartOfPop(pop, popRandom,  randFulIndex);

    if(i == generations - 1){
      FILE *csvFile2 = fopen("TOOLBOX/PYTHON/input/data_pid_.csv", "w");
      fprintf(csvFile2, "P,I,D,CV,RV\n");

      // plot best values
      pid->Kp   = bestPop->pop[0][0];
      pid->Ki   = bestPop->pop[0][1];
      pid->Kd   = bestPop->pop[0][2];
      pid->tauD = bestPop->pop[0][3];
      makeSimulationOfSignal(pid, csvFile2, 1);

      printf("BEST PID: P: %f I: %f D: %f Tau: %f - FIT: %f Count: %d\n", pid->Kp, pid->Ki, pid->Kd, pid->tauD, pid->fit, pid->maxCounter);

      fclose(csvFile2);
    }

    clearPopulation(bestPop);
    clearPopulation(randPopOne);
    clearPopulation(randPopTwo);
    clearPopulation(popRandom);
  }  

  clearPopulation(pop);

  deletePid(pid);

  fclose(csvFile);

  free(restCros);
  free(fit);


  plotGraph();

  int flag = 1;
  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST PID RUN FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST PID RUN SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}