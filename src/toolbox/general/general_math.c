#include "general/general_math.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stddef.h>

float createRandomFloat(const float min, const float max){
  const float random = ((float) rand()) / (float) RAND_MAX;
  return min + (random * (max - min));
}