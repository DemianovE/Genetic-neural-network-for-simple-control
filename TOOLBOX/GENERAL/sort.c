#include "include/sort.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>


void clearArrayArray(int** array, int size){
  for(int i = 0; i<size; i++){
    free(array[i]);
  }
}

void quickSort(float *fit, int *result, int length){
  
  int** arrayOfPointers = (int **)malloc(1 * sizeof(int*));
  int* size = (int *)malloc(1 * sizeof(int));
  size[0] = length;

  

  // create array of indexes from 0 to 1;
  //printf("``````````````````START````````````````````\n");
  arrayOfPointers[0] = (int*)malloc(length* sizeof(int));
  for(int i=0; i<length; i++){
    //printf("%d ", i);
    arrayOfPointers[0][i] = i;
  }
  //printf("\n```````````````````END```````````````````\n");
  
  int numArrays = 1;
  while(1){
    int** newArrayOfPointers = (int**)malloc(1 * sizeof(int*));
    int* newSizeArray = (int*)malloc(1 * sizeof(int));
    int newSize       = 0;
    int globalIndex   = 0;
    for(int indexArr=0; indexArr<numArrays; indexArr++){
      if(size[indexArr] > 1){
        int size1 = 0;
        int size2 = 0;

        

        int index = size[indexArr] / 2;

        int* firstArray  = (int*)malloc(1* sizeof(int));
        int* secondArray = (int*)malloc(1* sizeof(int));
        float check = fit[arrayOfPointers[indexArr][index]];

        for(int i=0; i<size[indexArr]; i++){
          if(i != index){
            if(check >= fit[arrayOfPointers[indexArr][i]]){
              secondArray = (int*)realloc(secondArray, (size2 + 1)*sizeof(int));
              secondArray[size2] = arrayOfPointers[indexArr][i];
              size2++;
            } else if(check < fit[arrayOfPointers[indexArr][i]]){
              firstArray = (int*)realloc(firstArray, (size1 + 1)*sizeof(int));
              firstArray[size1] = arrayOfPointers[indexArr][i];
              size1++;
            }
          }
        }
        
        if(size1 != 0){
          newSize++;
          newArrayOfPointers = (int**)realloc(newArrayOfPointers, newSize * sizeof(int*));
          newSizeArray        = (int*)realloc(newSizeArray, newSize * sizeof(int));
          newArrayOfPointers[globalIndex] = (int*)malloc(size1* sizeof(int));
          for(int i = 0; i<size1; i++){
            newArrayOfPointers[globalIndex][i] = firstArray[i];
          }
          newSizeArray[globalIndex] = size1;
          globalIndex++;
        }

        newSize++;
        newArrayOfPointers = (int**)realloc(newArrayOfPointers, newSize * sizeof(int*));
        newSizeArray        = (int*)realloc(newSizeArray, newSize * sizeof(int));
        newArrayOfPointers[globalIndex]    = (int*)malloc(1* sizeof(int)); 
        newArrayOfPointers[globalIndex][0] = arrayOfPointers[indexArr][index];
        newSizeArray[globalIndex] = 1;
        globalIndex++;

        if(size2 != 0){
          newSize++;
          newArrayOfPointers = (int**)realloc(newArrayOfPointers, newSize * sizeof(int*));
          newSizeArray        = (int*)realloc(newSizeArray, newSize * sizeof(int));
          newArrayOfPointers[globalIndex] = (int*)malloc(size2* sizeof(int));
          for(int i = 0; i<size2; i++){
            newArrayOfPointers[globalIndex][i] = secondArray[i];
          }
          newSizeArray[globalIndex] = size2;
          globalIndex++;
        }

        free(firstArray);
        free(secondArray);
      } else {
        newSize++;
        newArrayOfPointers = (int**)realloc(newArrayOfPointers, newSize * sizeof(int*));
        newSizeArray        = (int*)realloc(newSizeArray, newSize * sizeof(int));
        newArrayOfPointers[globalIndex]    = (int*)malloc(1* sizeof(int)); 
        newArrayOfPointers[globalIndex][0] = arrayOfPointers[indexArr][0];
        newSizeArray[globalIndex] = 1;
        globalIndex++;
      }
    }

    bool allOne = true;

    clearArrayArray(arrayOfPointers, numArrays);
    arrayOfPointers = (int**)realloc(arrayOfPointers, newSize*sizeof(int*));
    size              = (int*)realloc(size, newSize*sizeof(int));
    //printf("``````````````````START````````````````````\n");
    for(int i=0; i<newSize; i++){
      arrayOfPointers[i] = (int*)malloc(newSizeArray[i] * sizeof(int));
      size[i] = newSizeArray[i];
      
      for(int y=0; y<size[i]; y++){
        //printf("%d ", newArrayOfPointers[i][y]);
        arrayOfPointers[i][y] = newArrayOfPointers[i][y];
      }
      //printf("\n");

      if(size[i] > 1){
        allOne = false;
      }
    }
    //printf("```````````````````END```````````````````\n");
    numArrays = newSize;
    clearArrayArray(newArrayOfPointers, numArrays);
    free(newArrayOfPointers);
    free(newSizeArray);
    if(allOne == true){
      break;
    }
  }

  for(int i=0;i<length; i++){
    result[i] = arrayOfPointers[i][0];
  }
  clearArrayArray(arrayOfPointers, numArrays);
  free(arrayOfPointers);
  free(size);
}