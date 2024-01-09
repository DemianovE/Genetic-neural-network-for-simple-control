#include "TEST/include/test_activation_fnc.h"
#include "TEST/include/test_neural_network.h"
#include "TEST/include/test_population.h"
#include "TEST/include/test_matrixes.h"
#include "TEST/include/test_sort.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"

void matrix_tests(){
  int success_count = 0;
  int count = 0;
  int flag;
  printf(ANSI_BOLD "=======TEST MATRIX STARTED=======" ANSI_COLOR_RESET "\n");

  flag = test_matrix_add_sub();
  success_count += flag;
  count++;

  flag = test_matrix_multiply();
  success_count += flag;
  count++;

  flag = test_matrix_all_values_formula();
  success_count += flag;
  count++;

  flag = test_matrix_create_from_pointer();
  success_count += flag;
  count++;

  flag = test_matrix_fully_coppy_matrix();
  success_count += flag;
  count++;

  if(success_count != count){
    printf(ANSI_BOLD ANSI_COLOR_RED "Tests resulted in %d errors" ANSI_COLOR_RESET "\n", count - success_count);
  } 
  printf(ANSI_BOLD ANSI_COLOR_YELLOW "=======TEST MATRIX ENDED [%d/%d]=======" ANSI_COLOR_RESET "\n", success_count, count);
}

void act_fnc_tests(){
  int success_count = 0;
  int count = 0;
  int flag;
  printf(ANSI_BOLD "=======TEST ACT FNC STARTED=======" ANSI_COLOR_RESET "\n");

  flag = test_activation_fnc_tanh();
  success_count += flag;
  count++;

  flag = test_activation_fnc_sigm();
  success_count += flag;
  count++;

  if(success_count != count){
    printf(ANSI_BOLD ANSI_COLOR_RED "Tests resulted in %d errors" ANSI_COLOR_RESET "\n", count - success_count);
  } 
  printf(ANSI_BOLD ANSI_COLOR_YELLOW "=======TEST ACT FNC ENDED [%d/%d]=======" ANSI_COLOR_RESET "\n", success_count, count);
}

void sort_test(){
  int success_count = 0;
  int count = 0;
  int flag;
  printf(ANSI_BOLD "=======TEST SORT FULL STARTED=======" ANSI_COLOR_RESET "\n");

  flag = test_quicksort();
  success_count += flag;
  count++;

  if(success_count != count){
    printf(ANSI_BOLD ANSI_COLOR_RED "Tests resulted in %d errors" ANSI_COLOR_RESET "\n", count - success_count);
  } 
  printf(ANSI_BOLD ANSI_COLOR_YELLOW "=======TEST SORT FULL ENDED [%d/%d]=======" ANSI_COLOR_RESET "\n", success_count, count);
}

void population_test(){
  int success_count = 0;
  int count = 0;
  int flag;
  printf(ANSI_BOLD "=======TEST POPULATION STARTED=======" ANSI_COLOR_RESET "\n");

  flag = test_population();
  success_count += flag;
  count++;

  if(success_count != count){
    printf(ANSI_BOLD ANSI_COLOR_RED "Tests resulted in %d errors" ANSI_COLOR_RESET "\n", count - success_count);
  } 
  printf(ANSI_BOLD ANSI_COLOR_YELLOW "=======TEST POPULATION ENDED [%d/%d]=======" ANSI_COLOR_RESET "\n", success_count, count);
}

void genetic_operations_test(){
  int success_count = 0;
  int count = 0;
  int flag;
  printf(ANSI_BOLD "=======TEST GENETIC OPERATIONS STARTED=======" ANSI_COLOR_RESET "\n");

  flag = test_selbest();
  success_count += flag;
  count++;

  flag = test_crossov();
  success_count += flag;
  count++;

  flag = test_mutx();
  success_count += flag;
  count++;

  flag = test_selrand();
  success_count += flag;
  count++;

  if(success_count != count){
    printf(ANSI_BOLD ANSI_COLOR_RED "Tests resulted in %d errors" ANSI_COLOR_RESET "\n", count - success_count);
  } 
  printf(ANSI_BOLD ANSI_COLOR_YELLOW "=======TEST GENETIC OPERATIONS ENDED [%d/%d]=======" ANSI_COLOR_RESET "\n", success_count, count);
}

void neural_network_test(){
  int success_count = 0;
  int count = 0;
  int flag;
  printf(ANSI_BOLD "=======TEST NEURAL NETWORK STARTED=======" ANSI_COLOR_RESET "\n");

  flag = test_neural_network_create();
  success_count += flag;
  count++;

  if(success_count != count){
    printf(ANSI_BOLD ANSI_COLOR_RED "Tests resulted in %d errors" ANSI_COLOR_RESET "\n", count - success_count);
  } 
  printf(ANSI_BOLD ANSI_COLOR_YELLOW "=======TEST URAL NETWORK ENDED [%d/%d]=======" ANSI_COLOR_RESET "\n", success_count, count);
}

int main(){
  srand(time(0));
  int userChoice;

  while (1) {
    printf("1. matrixes\n");
    printf("2. act fnc\n");
    printf("3. sort\n");
    printf("4. population\n");
    printf("5. genetic operations\n");
    printf("6. neural network\n");
    printf("99. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &userChoice);

    switch (userChoice) {
      case 1:
        matrix_tests();
        break;
      case 2:
        act_fnc_tests();
        break;
      case 3:
        sort_test();
        break;
      case 4:
        population_test();
        break;
      case 5:
        genetic_operations_test();
        break;
      case 6:
        neural_network_test();
        break;
      case 99:
        printf("Exiting the tests\n");
        return 0;
      default:
        printf("Invalid option. Please try again.\n");
    }
    }
  return 0;
}

