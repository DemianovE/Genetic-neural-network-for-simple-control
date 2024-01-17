#ifndef SIGNAL_DESIGNER_H
#define SIGNAL_DESIGNER_H

typedef struct Signal {
    float *signal; // the value of the signal at each time point
    float dt;      // the sampling time for the signal
    int length;    // length of the signal in seconds                     
}Signal;

// function to select and create step signal
void selectStepSignal(struct Signal *signal);

// function to create custom signal of type A
void selectCustomASignal(struct Signal *signal);

// the function to clean the signal
void deleteSignal(struct Signal *signal);

// the function to select signal with CLI
void cliSignalSelector(struct Signal *signal);

#endif