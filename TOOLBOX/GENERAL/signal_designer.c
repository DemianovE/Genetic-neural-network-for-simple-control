#include "include/signal_designer.h"

#define DT 0.01; // the time step constant

void selectStepSignal(struct Signal *signal){
    signal->length = 100;
    signal->dt     = DT;

    signal->signal = (float*)malloc(signal->length * sizeof(float));   
    int globalIndex = 0;
    for(float i = 0.0; i < 0.3; i += signal->dt){
        signal->signal[globalIndex] = 0.0;
        globalIndex++;
    } for(float i = 0.3 + signal->dt; i < 1.0 - signal->dt; i += signal->dt){
        signal->signal[globalIndex] = 1.0;
        globalIndex++;
    }
}

void selectCustomASignal(struct Signal *signal){
    signal->length = 500;
    signal->dt     = DT;

    signal->signal = (float*)malloc(signal->length * sizeof(float));   
    int globalIndex = 0;
    for(float i = 0.0; i < 1.0; i += signal->dt){
        signal->signal[globalIndex] = 0.0;
        globalIndex++;
    } for(float i = 1.0 + signal->dt; i < 3.0; i += signal->dt){
        signal->signal[globalIndex] = 30.0;
        globalIndex++;
    } for(float i = 3.0 + signal->dt; i < 5.0; i += signal->dt){
        signal->signal[globalIndex] = 15.0;
        globalIndex++;
    }
}


void deleteSignal(struct Signal *signal){
    free(signal->signal);
    free(signal);
}

void cliSignalSelector(struct Signal *signal){
    printf("Please select the Signal:\n");
    printf("1 - step\n");
    printf("2 - customa\n");
    printf("Select: ");
    int userChoice;
    scanf("%d", &userChoice);

    if (userChoice == 1) {
        selectStepSignal(signal);
    } else if(userChoice == 2){
        selectCustomASignal(signal);
    }
}