#include "general/pid_controller.h"

#include "general/signal_designer.h"
#include "general/systems_builder.h"

#include <stdio.h>
#include <float.h>
#include <stdlib.h>

// I thank https://github.com/pms67/PID for the detailed info on how to program PID in C properly

static void resetOutputMemoryPid(PID *pid){
    for(int i=0; i < pid->signal->length; i++){
        pid->output->signal[i] = 0;
    }
    for(int i=0; i<pid->sizeDataSystem; i++){
        pid->dataSystem[i] = 0;
    }
    pid->dataSystem[1] = pid->signal->dt;

    pid->proportiError = 0;
    pid->integralError = 0;
    pid->differenError = 0;

    pid->prevError     = 0;

    pid->steadyRiseCheck = 1;
    pid->maxCounter = 0;
}

void createNewPidController(PID *pid){
    // first, the coefficients are set to 0 for start
    pid->Kp = 0;
    pid->Ki = 0;
    pid->Kd = 0;

    // the tau is set to 1.0 to not affect code in case it is unnecessary
    pid->tauD = 1;
    pid->tauI = 1;

    // select signal and system
    pid->signal = malloc(sizeof(Signal));
    cliSignalSelector(pid->signal);

    pid->sizeDataSystem = selectSystem(&pid->func_system);
    pid->dataSystem = malloc(pid->sizeDataSystem * sizeof(float));
    for(int i=0; i<pid->sizeDataSystem; i++){
        pid->dataSystem[i] = 0;
    }

    // set the output signal
    pid->output = malloc(sizeof(Signal));
    pid->output->length = pid->signal->length;
    pid->output->dt = pid->signal->dt;
    pid->output->signal = malloc(pid->signal->length * sizeof(float));
}

void deletePid(PID *pid){
    deleteSignal(pid->signal);
    deleteSignal(pid->output);

    free(pid->dataSystem);

    free(pid);
}

void makeSimulationOfSignal(struct PID *pid, FILE *csvFile, int csv){
    resetOutputMemoryPid(pid);
    pid->fit = 0;

    WRITE_TO_FILE(csv, csvFile, pid, 0);

    // we start from index 2 due to D parameter which requires the -2 time delay of y[t]
    for(int i=2; i<pid->signal->length; i++){
        // first action desired signal minus current value

        // P = e[t] * Kp
        // I = I + Ki * (e[t] + e[t-1]) * dt
        // D = -(Kd * (y[t-1] - y[t-2]) + (tau - dt) * D)/(tau + dt)
        // minus because it is on y[t] and not e[t]

        // e[t] = w[t] - y[t-1]
        const float error = pid->signal->signal[i] - pid->output->signal[i-1];
        
        // P = e[t] * Kp
        pid->proportiError = pid->Kp * error;

        // I = I + 0.5Ki * (e[t] + e[t-1]) * dt
        pid->integralError = pid->integralError + 0.5f * pid->Ki * (error - pid->prevError) * pid->signal->dt;

        // D = -(Kd * 2(y[t-1] - y[t-2]) + (2tau - dt) * D) / (2tau + dt)
        pid->differenError = -(2.0f * pid->Kd * (pid->output->signal[i-1] - pid->output->signal[i-2]) + (2.0f * pid->tauD - pid->signal->dt) * pid->differenError) 
                                / (2.0f * pid->tauD + pid->signal->dt);

        if(pid->integralError > pid->limMaxInt){
            pid->integralError =pid->limMaxInt;
        } else if(pid->integralError < pid->limMinInt){
            pid->integralError = pid->limMinInt;
        }

        // set data and pass to a system
        pid->dataSystem[0] = pid->proportiError + pid->integralError + pid->differenError;
        
        pid->output->signal[i] = pid->func_system(pid->dataSystem);

        if(pid->output->signal[i] > pid->limMax){
            pid->output->signal[i] = pid->limMax;
            pid->maxCounter++;
        } else if(pid->output->signal[i] < pid->limMin){
            pid->output->signal[i] = pid->limMin;
            pid->maxCounter++;
        }

        WRITE_TO_FILE(csv, csvFile, pid, i);

        // set prevError
        pid->prevError = error;   

        const float diff = pid->signal->signal[i] - pid->output->signal[i];
        pid->fit += diff > 0 ? diff : diff * (-1);

        if(pid->output->signal[i-1] > pid->output->signal[i]){
            pid->steadyRiseCheck = 0;
        }
    }

    
    if(pid->steadyRiseCheck == 1 || pid->maxCounter > pid->signal->length * 1 / 100){
        pid->fit =  FLT_MAX; // make fit max value to not consider the steady rise solutions
    }
}