#include "include/activation_fnc.h"

#include <stdio.h>
#include <math.h>

float tangenth(float x){
    return tan(x);
}

float sigmoid(float x) {
    return 1.0 / (1.0 + exp(-x));
}

void select_activation_function(float (*func_ptr)(float)){
    printf("Enter 1 to calculate tangent or 2 to calculate sigmoid: ");
    int userChoice;
    scanf("%d", &userChoice);

    if (userChoice == 1) {
        func_ptr = &tangenth;
    } else if (userChoice == 2) {
        func_ptr = &sigmoid;
    }
}