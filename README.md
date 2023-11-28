# Genetic-neural-network-for-simple-controll\

## Overview
This project was created to create Neural Network models with much faster calculation then in C. 

The main purpose of this models is to be used in simple controll tasks replacing the PID, which can't normally controll complex non-linear systems. This controll in practice can be used on robotics and controll systems such as water level controll, air polution controll etc.

## Models
Status of the models' types:
- FF - under development 
- SD - planned
- RR - planned

## Activation functions
As activation functions following functions are used:
1) Sigmoids
$$
\sigma(x) = \fraq{1}{1 + e^{-2}}, \quad \sigma \in <0, 1>
$$
2) Tangenth
$$
\tanh(x) = \frac{e^{x} - e^{-x}}{e^{x} + e^{-x}}, \quad \sigma \in <-1, 1>
$$

Tangenth activation function is prefered due to better range.