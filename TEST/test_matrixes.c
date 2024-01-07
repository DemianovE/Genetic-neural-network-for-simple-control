#include "include/test_matrixes.h"
#include "../TOOLBOX/GENERAL/include/matrix_math.h"
#include "../TOOLBOX/NEURAL/include/activation_fnc.h"

#include <stdlib.h>
#include <stdio.h>

// used to print testing outputs
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_BOLD         "\x1b[1m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int compare_matrixes(struct Matrix *A, struct Matrix *B){
  // check if both matrixes have same size
  if(A->sizes[0] != B->sizes[0] || A->sizes[1] != B->sizes[1]){
    return 0;
  }

  // check if the values are same
  for(int x=0; x<A->sizes[0]; x++){
    for(int y=0; y<A->sizes[1]; y++){
      if(A->matrix[x][y] != B->matrix[x][y]){
        return 0;
      }
    }
  }
  return 1;
}

int test_matrix_add_sub(){
  printf(ANSI_BOLD "=======TEST MATRIX ADD SUB STARTED=======" ANSI_COLOR_RESET "\n");
  int type;

  int *sizes1 = (int *)malloc(2 * sizeof(int));
  sizes1[0] = 2;
  sizes1[1] = 2;
  
  int *sizes2 = (int *)malloc(2 * sizeof(int));
  sizes2[0] = 2;
  sizes2[1] = 2;

  int *sizesDesiredAdd = (int *)malloc(2 * sizeof(int));
  sizesDesiredAdd[0] = 2;
  sizesDesiredAdd[1] = 2;
  int *sizesDesiredSub = (int *)malloc(2 * sizeof(int));
  sizesDesiredSub[0] = 2;
  sizesDesiredSub[1] = 2;

  struct Matrix *A  = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *B  = (struct Matrix*)malloc(sizeof(struct Matrix));

  struct Matrix *ABSADD = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *ABSSUB = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *DESIREDADD = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *DESIREDSUB = (struct Matrix*)malloc(sizeof(struct Matrix));

  create_matrix(A, sizes1);
  create_matrix(B, sizes2);

  create_matrix(DESIREDADD, sizesDesiredAdd);
  create_matrix(DESIREDSUB, sizesDesiredSub);

  A->matrix[0][0] = 1;
  A->matrix[0][1] = 1;
  A->matrix[1][0] = 1;
  A->matrix[1][1] = 1;

  B->matrix[0][0] = 1;
  B->matrix[0][1] = 1;
  B->matrix[1][0] = 1;
  B->matrix[1][1] = 1;

  DESIREDADD->matrix[0][0] = 2;
  DESIREDADD->matrix[0][1] = 2;
  DESIREDADD->matrix[1][0] = 2;
  DESIREDADD->matrix[1][1] = 2;

  DESIREDSUB->matrix[0][0] = 0;
  DESIREDSUB->matrix[0][1] = 0;
  DESIREDSUB->matrix[1][0] = 0;
  DESIREDSUB->matrix[1][1] = 0;

  type = 1; // 0 - sub, 1 - add
  matrix_subst_add(A, B, ABSADD, type);
  printf("result of the add: \n");
  for(int x=0; x<ABSADD->sizes[0]; x++){
    for(int y=0; y<ABSADD->sizes[1]; y++){
      printf("%f ", ABSADD->matrix[x][y]);
    }
    printf("\n");
  }

  

  type = 0; // 0 - sub, 1 - add
  matrix_subst_add(A, B, ABSSUB, type);
  printf("result of the sub: \n");
  for(int x=0; x<ABSSUB->sizes[0]; x++){
    for(int y=0; y<ABSSUB->sizes[1]; y++){
      printf("%f ", ABSSUB->matrix[x][y]);
    }
    printf("\n");
  }

  // ensure the correct output of the function
  int flagAdd = compare_matrixes(ABSADD, DESIREDADD);
  int flagSub = compare_matrixes(ABSSUB, DESIREDSUB);

  // clear all matrixes
  matrix_delete(A);
  matrix_delete(B);

  matrix_delete(ABSADD);
  matrix_delete(ABSSUB);

  matrix_delete(DESIREDADD);
  matrix_delete(DESIREDSUB);

  if(flagAdd == 0 || flagSub == 0){
    if(flagAdd == 0){
      printf(ANSI_COLOR_RED "add function failed" ANSI_COLOR_RESET "\n");
    }

    if(flagSub == 0){
      printf(ANSI_COLOR_RED "sub function failed" ANSI_COLOR_RESET "\n");
    }

    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST MATRIX ADD SUB FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  } 


  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST MATRIX ADD SUB SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}

int test_matrix_multiply(){
  printf(ANSI_BOLD "=======TEST MATRIX MULTIPLY STARTED=======" ANSI_COLOR_RESET "\n");

  int *sizes1 = (int *)malloc(2 * sizeof(int));
  sizes1[0] = 2;
  sizes1[1] = 3;
  
  int *sizes2 = (int *)malloc(2 * sizeof(int));
  sizes2[0] = 3;
  sizes2[1] = 2;

  int *sizesDesiredMult = (int *)malloc(2 * sizeof(int));
  sizesDesiredMult[0] = 2;
  sizesDesiredMult[1] = 2;

  struct Matrix *A = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *B = (struct Matrix*)malloc(sizeof(struct Matrix));

  struct Matrix *AB = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *DESIREDMULT = (struct Matrix*)malloc(sizeof(struct Matrix));

  create_matrix(A, sizes1);
  create_matrix(B, sizes2);

  create_matrix(DESIREDMULT, sizesDesiredMult);

  A->matrix[0][0] = 1;
  A->matrix[0][1] = 1;
  A->matrix[0][2] = 1;

  A->matrix[1][0] = 2;
  A->matrix[1][1] = 2;
  A->matrix[1][2] = 2;

  B->matrix[0][0] = 1;
  B->matrix[1][0] = 1;
  B->matrix[2][0] = 1;

  B->matrix[0][1] = 2;
  B->matrix[1][1] = 2;
  B->matrix[2][1] = 2;

  DESIREDMULT->matrix[0][0] = 3;
  DESIREDMULT->matrix[0][1] = 6;
  DESIREDMULT->matrix[1][0] = 6;
  DESIREDMULT->matrix[1][1] = 12;

  matrix_multiply(A, B, AB);
  printf("Result of the multiply:\n");
  for(int x=0; x<AB->sizes[0]; x++){
    for(int y=0; y<AB->sizes[1]; y++){
      printf("%f ", AB->matrix[x][y]);
    }
    printf("\n");
  }

  // ensure the matrixe is as desired
  int flag = compare_matrixes(AB, DESIREDMULT);

  // clear all matrixes
  matrix_delete(A);
  matrix_delete(B);

  matrix_delete(AB);

  matrix_delete(DESIREDMULT);

  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST MATRIX MULTIPLY FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST MATRIX MULTIPLY SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}

int test_matrix_all_values_formula(){
  printf(ANSI_BOLD "=======TEST MATRIX ALL VALUES FORMULA STARTED=======" ANSI_COLOR_RESET "\n");
  int *sizesTanh = (int *)malloc(2 * sizeof(int));
  sizesTanh[0] = 2;
  sizesTanh[1] = 2;

  int *sizesSigm = (int *)malloc(2 * sizeof(int));
  sizesSigm[0] = 2;
  sizesSigm[1] = 2;

  int *sizesTanhDesired = (int *)malloc(2 * sizeof(int));
  sizesTanhDesired[0] = 2;
  sizesTanhDesired[1] = 2;

  int *sizesSigmDesired = (int *)malloc(2 * sizeof(int));
  sizesSigmDesired[0] = 2;
  sizesSigmDesired[1] = 2;

  struct Matrix *dataTanh = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *dataSigm = (struct Matrix*)malloc(sizeof(struct Matrix));

  struct Matrix *DESIREDTANH = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *DESIREDSIGM = (struct Matrix*)malloc(sizeof(struct Matrix));

  create_matrix(dataTanh, sizesTanh);
  create_matrix(dataSigm, sizesSigm);

  create_matrix(DESIREDTANH, sizesTanhDesired);
  create_matrix(DESIREDSIGM, sizesSigmDesired);

  dataTanh->matrix[0][0] = 1;
  dataTanh->matrix[0][1] = 1;
  dataTanh->matrix[1][0] = 2;
  dataTanh->matrix[1][1] = 2;

  dataSigm->matrix[0][0] = 1;
  dataSigm->matrix[0][1] = 1;
  dataSigm->matrix[1][0] = 2;
  dataSigm->matrix[1][1] = 2;

  float (*func_ptr_tanh)(float);
  select_tang_activation_function(&func_ptr_tanh);

  float (*func_ptr_sigm)(float);
  select_sigm_activation_function(&func_ptr_sigm);

  DESIREDTANH->matrix[0][0] = func_ptr_tanh(1);
  DESIREDTANH->matrix[0][1] = func_ptr_tanh(1);
  DESIREDTANH->matrix[1][0] = func_ptr_tanh(2);
  DESIREDTANH->matrix[1][1] = func_ptr_tanh(2);

  DESIREDSIGM->matrix[0][0] = func_ptr_sigm(1);
  DESIREDSIGM->matrix[0][1] = func_ptr_sigm(1);
  DESIREDSIGM->matrix[1][0] = func_ptr_sigm(2);
  DESIREDSIGM->matrix[1][1] = func_ptr_sigm(2);

  matrix_all_values_formula(dataTanh, func_ptr_tanh);
  printf("Result of the tanh:\n");
  for(int x=0; x<dataTanh->sizes[0]; x++){
    for(int y=0; y<dataTanh->sizes[1]; y++){
      printf("%f ", dataTanh->matrix[x][y]);
    }
    printf("\n");
  }

  matrix_all_values_formula(dataSigm, func_ptr_sigm);
  printf("Result of the sigm:\n");
  for(int x=0; x<dataSigm->sizes[0]; x++){
    for(int y=0; y<dataSigm->sizes[1]; y++){
      printf("%f ", dataSigm->matrix[x][y]);
    }
    printf("\n");
  }

  int flagTang = compare_matrixes(dataTanh, DESIREDTANH);
  int flagSigm = compare_matrixes(dataSigm, DESIREDSIGM);

  matrix_delete(dataTanh);
  matrix_delete(dataSigm);

  matrix_delete(DESIREDTANH);
  matrix_delete(DESIREDSIGM);

  func_ptr_tanh = NULL;
  func_ptr_sigm = NULL;

  if(flagTang == 0 || flagSigm == 0){
    if(flagTang == 0){
      printf(ANSI_COLOR_RED "tanh function failed" ANSI_COLOR_RESET "\n");
    }

    if(flagSigm == 0){
      printf(ANSI_COLOR_RED "sigm function failed" ANSI_COLOR_RESET "\n");
    }

    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST MATRIX ALL VALUES FORMULA FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST MATRIX ALL VALUES FORMULA SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}

int test_matrix_create_from_pointer(){
  printf(ANSI_BOLD "=======TEST MATRIX FROM POINTER STARTED=======" ANSI_COLOR_RESET "\n");
  int *sizes = (int *)malloc(2 * sizeof(int));
  sizes[0] = 3;
  sizes[1] = 2;

  int *sizesDesired = (int *)malloc(2 * sizeof(int));
  sizesDesired[0] = 3;
  sizesDesired[1] = 2;

  struct Matrix *data    = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *DESIRED = (struct Matrix*)malloc(sizeof(struct Matrix));

  create_matrix(DESIRED, sizesDesired);

  DESIRED->matrix[0][0] = 1.0;
  DESIRED->matrix[0][1] = 2.0;
  DESIRED->matrix[1][0] = 3.0;
  DESIRED->matrix[1][1] = 4.0;
  DESIRED->matrix[2][0] = 5.0;
  DESIRED->matrix[2][1] = 6.0;

  float data_pointer[] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

  create_matrix_from_pointer(data, data_pointer, sizes);
  printf("Result of the matrix from pointer:\n");
  for(int x=0; x<data->sizes[0]; x++){
    for(int y=0; y<data->sizes[1]; y++){
      printf("%f ", data->matrix[x][y]);
    }
    printf("\n");
  }

  int flag = compare_matrixes(data, DESIRED);

  matrix_delete(data);
  matrix_delete(DESIRED);

  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST MATRIX FROM POINTER FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST MATRIX FROM POINTER SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}

int test_matrix_fully_coppy_matrix(){
  printf(ANSI_BOLD "=======TEST MATRIX FULLY COPY STARTED=======" ANSI_COLOR_RESET "\n");

  int *sizesDesired = (int *)malloc(2 * sizeof(int));
  sizesDesired[0] = 3;
  sizesDesired[1] = 2;

  struct Matrix *data    = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *DESIRED = (struct Matrix*)malloc(sizeof(struct Matrix));

  create_matrix(DESIRED, sizesDesired);

  DESIRED->matrix[0][0] = 1.0;
  DESIRED->matrix[0][1] = 2.0;
  DESIRED->matrix[1][0] = 3.0;
  DESIRED->matrix[1][1] = 4.0;
  DESIRED->matrix[2][0] = 5.0;
  DESIRED->matrix[2][1] = 6.0;

  fully_copy_matrix(DESIRED, data);
  int flag = compare_matrixes(data, DESIRED);

  matrix_delete(data);
  matrix_delete(DESIRED);

  if(flag == 0){
    printf(ANSI_BOLD ANSI_COLOR_RED "=======TEST MATRIX FULLY COPY FAILED=======" ANSI_COLOR_RESET "\n");
    return 0;
  }
  printf(ANSI_BOLD ANSI_COLOR_GREEN "=======TEST MATRIX FULLY COPY SUCCESSFUL=======" ANSI_COLOR_RESET "\n");
  return 1;
}