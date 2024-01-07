#include "include/test_sort.h"
#include "../TOOLBOX/GENERAL/include/sort.h"

#include <stdlib.h>
#include <stdio.h>

// used to print testing outputs
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int test_sort(){
  printf(ANSI_BOLD "=======TEST SORT STARTED=======" ANSI_COLOR_RESET "\n");

  int length = 5;
  float fit[] = {9.6, 3.4, 10, 4.6, 0.4};
  int *result = (int*)malloc(length*sizeof(int));

  int resultCorrect[] = {2, 0, 3, 1, 4};

  quick_sort(fit, result, length);

  int flag = 1;
  for(int i=0; i<length; i++){
    if(resultCorrect[i] != result[i]){
      flag = 0;
    }
  }
  free(result);

  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST SORT FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST SORT SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}