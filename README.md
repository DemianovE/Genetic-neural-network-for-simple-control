# Genetic-neural-network-for-simple-controll\

## Overview
This project was created to create Neural Network models with much faster calculation then in C. 

The main purpose of this models is to be used in simple controll tasks replacing the PID, which can't normally controll complex non-linear systems. This controll in practice can be used on robotics and controll systems such as water level controll, air polution controll etc.

## Models
Status of the models' types:
- FF - under development 
- SD - under development 
- RR - planned

## Activation functions
As activation functions following functions are used:
1) Sigmoids ![equation](https://latex.codecogs.com/svg.image?%5Csigma(x)=%5Cfrac%7B1%7D%7B1&plus;e%5E%7B-2%7D%7D,%5Cquad%5Csigma%5Cin%3C0,1%3E)
2) Tangenth ![equation](https://latex.codecogs.com/svg.image?%5Ctanh(x)=%5Cfrac%7Be%5E%7Bx%7D-e%5E%7B-x%7D%7D%7Be%5E%7Bx%7D&plus;e%5E%7B-x%7D%7D,%5Cquad%5Csigma%5Cin%3C-1,1%3E)

Tangenth activation function is prefered due to better range.

## Testing
### Code testing
Currently the tests are writen in the folder TEST with test_main being used as a linking file to other test files. Each of specific test files includes methods to test different function of the parts of system. The 