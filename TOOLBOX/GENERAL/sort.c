#include "include/sort.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <stdbool.h>


void clear_array_array(int** array, int size){
  for(int i = 0; i<size; i++){
    free(array[i]);
  }
}

void quick_sort(float *fit, int *result, int length){
  
  int** array_of_pointers = (int **)malloc(1 * sizeof(int*));
  int* size = (int *)malloc(1 * sizeof(int));
  size[0] = length;

  

  // create array of indexes from 0 to 1;
  //printf("``````````````````START````````````````````\n");
  array_of_pointers[0] = (int*)malloc(length* sizeof(int));
  for(int i=0; i<length; i++){
    //printf("%d ", i);
    array_of_pointers[0][i] = i;
  }
  //printf("\n```````````````````END```````````````````\n");
  
  int num_arrays = 1;
  while(1){
    int** new_array_of_pointers = (int**)malloc(1 * sizeof(int*));
    int* new_size_array = (int*)malloc(1 * sizeof(int));
    int new_size       = 0;
    int global_index   = 0;
    for(int index_arr=0; index_arr<num_arrays; index_arr++){
      if(size[index_arr] > 1){
        int size1 = 0;
        int size2 = 0;

        

        int index = size[index_arr] / 2;

        int* first_array  = (int*)malloc(1* sizeof(int));
        int* second_array = (int*)malloc(1* sizeof(int));
        float check = fit[array_of_pointers[index_arr][index]];

        for(int i=0; i<size[index_arr]; i++){
          if(i != index){
            if(check >= fit[array_of_pointers[index_arr][i]]){
              second_array = (int*)realloc(second_array, (size2 + 1)*sizeof(int));
              second_array[size2] = array_of_pointers[index_arr][i];
              size2++;
            } else if(check < fit[array_of_pointers[index_arr][i]]){
              first_array = (int*)realloc(first_array, (size1 + 1)*sizeof(int));
              first_array[size1] = array_of_pointers[index_arr][i];
              size1++;
            }
          }
        }
        
        if(size1 != 0){
          new_size++;
          new_array_of_pointers = (int**)realloc(new_array_of_pointers, new_size * sizeof(int*));
          new_size_array        = (int*)realloc(new_size_array, new_size * sizeof(int));
          new_array_of_pointers[global_index] = (int*)malloc(size1* sizeof(int));
          for(int i = 0; i<size1; i++){
            new_array_of_pointers[global_index][i] = first_array[i];
          }
          new_size_array[global_index] = size1;
          global_index++;
        }

        new_size++;
        new_array_of_pointers = (int**)realloc(new_array_of_pointers, new_size * sizeof(int*));
        new_size_array        = (int*)realloc(new_size_array, new_size * sizeof(int));
        new_array_of_pointers[global_index]    = (int*)malloc(1* sizeof(int)); 
        new_array_of_pointers[global_index][0] = array_of_pointers[index_arr][index];
        new_size_array[global_index] = 1;
        global_index++;

        if(size2 != 0){
          new_size++;
          new_array_of_pointers = (int**)realloc(new_array_of_pointers, new_size * sizeof(int*));
          new_size_array        = (int*)realloc(new_size_array, new_size * sizeof(int));
          new_array_of_pointers[global_index] = (int*)malloc(size2* sizeof(int));
          for(int i = 0; i<size2; i++){
            new_array_of_pointers[global_index][i] = second_array[i];
          }
          new_size_array[global_index] = size2;
          global_index++;
        }

        free(first_array);
        free(second_array);
      } else {
        new_size++;
        new_array_of_pointers = (int**)realloc(new_array_of_pointers, new_size * sizeof(int*));
        new_size_array        = (int*)realloc(new_size_array, new_size * sizeof(int));
        new_array_of_pointers[global_index]    = (int*)malloc(1* sizeof(int)); 
        new_array_of_pointers[global_index][0] = array_of_pointers[index_arr][0];
        new_size_array[global_index] = 1;
        global_index++;
      }
    }

    bool all_1 = true;

    clear_array_array(array_of_pointers, num_arrays);
    array_of_pointers = (int**)realloc(array_of_pointers, new_size*sizeof(int*));
    size              = (int*)realloc(size, new_size*sizeof(int));
    //printf("``````````````````START````````````````````\n");
    for(int i=0; i<new_size; i++){
      array_of_pointers[i] = (int*)malloc(new_size_array[i] * sizeof(int));
      size[i] = new_size_array[i];
      
      for(int y=0; y<size[i]; y++){
        //printf("%d ", new_array_of_pointers[i][y]);
        array_of_pointers[i][y] = new_array_of_pointers[i][y];
      }
      //printf("\n");

      if(size[i] > 1){
        all_1 = false;
      }
    }
    //printf("```````````````````END```````````````````\n");
    num_arrays = new_size;
    clear_array_array(new_array_of_pointers, num_arrays);
    free(new_array_of_pointers);
    free(new_size_array);
    if(all_1 == true){
      break;
    }
  }

  for(int i=0;i<length; i++){
    result[i] = array_of_pointers[i][0];
  }
  clear_array_array(array_of_pointers, num_arrays);
  free(array_of_pointers);
  free(size);
}