#include "general/sort.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>

static int* safe_realloc(int* ptr, const size_t new_size, const char* varname) {
  int* tmp = realloc(ptr, new_size * sizeof(int));
  if (tmp == NULL && new_size > 0) {
    fprintf(stderr, "Error: realloc failed for %s\n", varname);
    free(ptr);
    exit(EXIT_FAILURE);
  }
  return tmp;
}


void quickSort(float *fit, int *result, const int length)
{
  // in this sort the fit is only used as a datasource for the result
  // the length is the data for the result, not fit
  // the isea is that the list of values will be recursed so that in a result the
  // input - the array of indexes which should be sorted based on fit

  // first, the indexes as well as arrays for a left and right are created
  const int index = length / 2;

  int indexMore = 0;
  int indexLess = 0;

  int *arrayMore = malloc(length* sizeof(int));
  int *arrayLess = malloc(length* sizeof(int));

  // now the check is made and arrays are filled with values
  for(int i=0; i<length; i++){
    if(i != index){
      // logic is, indexes with more equal are going right and less going left
      if(fit[result[i]] >= fit[result[index]]){
        arrayMore[indexMore] = result[i];
        indexMore++;
      } else if(fit[result[i]] < fit[result[index]]){
        arrayLess[indexLess] = result[i];
        indexLess++;
      }
    }
  }
  // now we have two lists with indexes less and more. Except for the middle one
  if (indexMore > 0) {arrayMore = safe_realloc(arrayMore, indexMore, "arrayMore");}
  if (indexLess > 0) {arrayLess = safe_realloc(arrayLess, indexLess, "arrayMore");}

  // now the recursion part should be made
  if(indexMore > 1){
    quickSort(fit, arrayMore, indexMore);
  }

  if(indexLess > 1){
    quickSort(fit, arrayLess, indexLess);
  }

  const int middle = result[index];
  int indexGlobal = 0;
  // the first the less part is updates
  for(int i=0; i<indexLess; i++){
    result[indexGlobal] = arrayLess[i];
    indexGlobal++;
  }

  // then middle added
  result[indexGlobal] = middle;
  indexGlobal++;

  // last the more part is updates 
  for(int i=0; i<indexMore; i++){
    result[indexGlobal] = arrayMore[i];
    indexGlobal++;
  }

  free(arrayLess);
  free(arrayMore);
}
