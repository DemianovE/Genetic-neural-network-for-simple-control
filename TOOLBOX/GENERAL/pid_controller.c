#include "include/pid_controller.h"

#include "include/signal_designer.h"
#include "include/systems_builder.h"

#include <stdio.h>


void createNewPidController(struct PID *pid){
    // first the coeficients are set to 0 for start
    pid->Kp = 0.0;
    pid->Ki = 0.0;
    pid->Kd = 0.0;

    // the tau is set to 1.0 to not affect code in case it is not needed
    pid->tauD = 1.0;
    pid->tauI = 1.0;

    // select signal and system
    pid->signal = (struct Signal*)malloc(sizeof(struct Signal));
    cliSignalSelector(pid->signal);

    
    selectSystem(&pid->func_system, pid);

    // set the output signal
    pid->output = (struct Signal*)malloc(sizeof(struct Signal));
    pid->output->length = pid->signal->length;
    pid->output->dt = pid->signal->dt;
    pid->output->signal = (float*)malloc(pid->signal->length * sizeof(float));

    // now the memory part is set to 0.0
    pid->prevError     = 0.0;
    pid->integralError = 0.0;
}

void deletePid(struct PID *pid){
    deleteSignal(pid->signal);
    deleteSignal(pid->output);

    free(pid->dataSystem);

    free(pid);
}

void resetOutputMemoryPid(struct PID *pid){
    for(int i=0; i < pid->signal->length; i++){
        pid->output->signal[i] = 0.0;
        //printf("%f\n", pid->output->signal[i]);
    }
}

void makeSimulationOfSignal(struct PID *pid, FILE *csvFile, int csv){
    resetOutputMemoryPid(pid);

    float error, CV, P, I, D;

    for(int i=1; i<pid->signal->length; i++){
        // first action desired signal minus current value
        error = pid->signal->signal[i] - pid->output->signal[i-1];
        
        pid->integralError += error;

        if(pid->integralError > pid->iMax){
            pid->integralError = pid->iMax;
        } else if(pid->integralError < pid->iMin){
            pid->integralError = pid->iMin;
        }

        // get all components of the PID
        P = pid->Kp * error;
        I = pid->Ki * pid->integralError;
        D = pid->Kd * ((error - pid->prevError)/pid->signal->dt);

        // get current controll value and get system output
        CV = P + I + D;
        // set data and pass to system
        pid->dataSystem[0] = CV;
        
        pid->output->signal[i] = pid->output->signal[i-1] + pid->func_system(pid->dataSystem);

        if(pid->output->signal[i] > pid->iMax){
            pid->output->signal[i] = pid->iMax;
        } else if(pid->output->signal[i] < pid->iMin){
            pid->output->signal[i] = pid->iMin;
        }

        if(csv == 1){
            fprintf(csvFile, "%f,%f,%f,%f,%f\n", P, I, D, pid->output->signal[i], pid->signal->signal[i]);
        }

        // set prevError
        pid->prevError = error;   
    }
}