#include "include/input_toolbox.h"

#include "include/model_system.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void typeOne(float *data) {

  // data[0] - dt

  // data[1] - e[t]
  // data[2] - u[t]
  // data[3] - y[t]

  // data[4] -  de[t]
  // data[5] -  ie[t]
  // data[6] -  dy[t]
  // data[7] - ddy[t]
  // data[8] -  du[t]

  // data[9]  -  e[t-1]
  // data[10] -  u[t-1]
  // data[11] -  y[t-1]
  // data[12] - dy[t-1]

  // e
  data[4]  = (data[1] - data[9])/data[0];
  data[5] +=  data[1];
  data[9]  =  data[1];

  // u
  data[8]  = (data[2] - data[10])/data[0];
  data[10] =  data[2];

  // y
  data[6]  = (data[3] - data[11])/data[0];
  data[7]  = (data[6] - data[12])/data[0];
  data[11] =  data[3];
  data[12] =  data[6];
}

void makeInputDataSystem(struct SystemNN *systemInput, int size, int full){
  systemInput->inputData = (float*)malloc(full * sizeof(float));
  for(int i=0; i<full; i++){
      systemInput->inputData[i] = 0.0;
  }

  systemInput->inputDataSize = (int*)malloc(3 * sizeof(int));
  systemInput->inputDataSize[2] = full;
  systemInput->inputDataSize[2] = 1;
  systemInput->inputDataSize[2] = size + 1;
}

void selectInputNNFunction(void (**func_ptr)(float*), struct SystemNN *systemInput){
    printf("Please select the AF:\n1 - typeOne\nSelect: ");
    int userChoice;
    scanf("%d", &userChoice);

    if (userChoice == 1) {
        *func_ptr = typeOne;
        makeInputDataSystem(systemInput, 8, 13);
    }
}