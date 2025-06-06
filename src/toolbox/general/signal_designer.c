#include "general/signal_designer.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// the time step constant
#define DT001 0.001; 
#define DT01  0.01;

static void buildFromMap(Signal *signal, const float map[][3], const int size){
    assert(signal != NULL);
    assert(signal->signal != NULL);

    int globalIndex = 0;
    for (int i = 0; i < size; i++){
        const int start = (int)(map[i][0] / signal->dt);
        const int end   = (int)(map[i][1] / signal->dt);

        for  (int j = start; j < end; j++){
            signal->signal[globalIndex] = map[i][2];
            globalIndex++;
        }
    }

    signal->length = globalIndex;
}

static void selectStepSignal(Signal *signal){
    signal->length = 1000;
    signal->dt     = DT01;

    signal->signal = (float*)malloc(signal->length * sizeof(float));

    const float map[2][3] = {
        {0,  1, 0},
        {1, 10, 1}};
    const int size = 2;

    buildFromMap(signal, map, size);
}

static void selectCustomASignal(Signal *signal){
    signal->length = 1002;
    signal->dt     = DT01;

    signal->signal = (float*)malloc(signal->length * sizeof(float));

    const float map[6][3] = {
        {0,  1,  0},
        {1,  3, 30},
        {3,  5, 15},
        {5,  8,  5},
        {8,  9, 25},
        {9, 10,  0}};
    const int size = 6;

    buildFromMap(signal, map, size);
}


void deleteSignal(struct Signal *signal){
    free(signal->signal);
    free(signal);
}

void cliSignalSelector(struct Signal *signal){
    printf("Please select the Signal:\n");
    printf("1 - step\n");
    printf("2 - custom\n");
    printf("Select: ");
    int userChoice;
    scanf("%d", &userChoice);

    if (userChoice == 1) {
        selectStepSignal(signal);
    } else if(userChoice == 2){
        selectCustomASignal(signal);
    }
}