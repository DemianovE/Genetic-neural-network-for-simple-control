#include "include/general_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

float create_random_float(float min, float max){
  float random = ((float) rand()) / (float) RAND_MAX;
  float diff = max - min;
  float r = random * diff;
  return min + r;
}