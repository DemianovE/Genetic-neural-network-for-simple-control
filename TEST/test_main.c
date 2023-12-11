#include "include/test_main.h"
#include "../TOOLBOX/GENERAL/include/matrix_math.h"
#include "../TOOLBOX/NEURAL/include/activation_fnc.h"

#include <stdlib.h>
#include <stdio.h>

void test_matrix_add(){
  int *sizes1 = (int *)malloc(2 * sizeof(int));
  sizes1[0] = 2;
  sizes1[1] = 2;
  
  int *sizes2 = (int *)malloc(2 * sizeof(int));
  sizes2[0] = 2;
  sizes2[1] = 2;

  struct Matrix *A = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *B = (struct Matrix*)malloc(sizeof(struct Matrix));

  struct Matrix *AB = (struct Matrix*)malloc(sizeof(struct Matrix));

  create_matrix(A, sizes1);
  create_matrix(B, sizes2);

  A->matrix[0][0] = 1;
  A->matrix[0][1] = 1;
  A->matrix[1][0] = 1;
  A->matrix[1][1] = 1;

  B->matrix[0][0] = 1;
  B->matrix[0][1] = 1;
  B->matrix[1][0] = 1;
  B->matrix[1][1] = 1;

  printf("B - %d %d, A - %d %d\n", A->sizes[0], A->sizes[1], B->sizes[0], B->sizes[1]);

  int type = 0; // 0 - sub, 1 - add
  matrix_subst_add(A, B, AB, type);

  for(int x=0; x<AB->sizes[0]; x++){
    for(int y=0; y<AB->sizes[1]; y++){
      printf("%f ", AB->matrix[x][y]);
    }
    printf("\n");
  }
}

void test_matrix_multiply(){
  int *sizes1 = (int *)malloc(2 * sizeof(int));
  sizes1[0] = 2;
  sizes1[1] = 3;
  
  int *sizes2 = (int *)malloc(2 * sizeof(int));
  sizes2[0] = 3;
  sizes2[1] = 2;

  struct Matrix *A = (struct Matrix*)malloc(sizeof(struct Matrix));
  struct Matrix *B = (struct Matrix*)malloc(sizeof(struct Matrix));

  struct Matrix *AB = (struct Matrix*)malloc(sizeof(struct Matrix));

  create_matrix(A, sizes1);
  create_matrix(B, sizes2);

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

  matrix_multiply(A, B, AB);

  for(int x=0; x<AB->sizes[0]; x++){
    for(int y=0; y<AB->sizes[1]; y++){
      printf("%f ", AB->matrix[x][y]);
    }
    printf("\n");
  }
}

void test_matrix_all_values_formula(){
  int *sizes1 = (int *)malloc(2 * sizeof(int));
  sizes1[0] = 2;
  sizes1[1] = 2;

  struct Matrix *matrix = (struct Matrix*)malloc(sizeof(struct Matrix));

  create_matrix(matrix, sizes1);

  matrix->matrix[0][0] = 1;
  matrix->matrix[0][1] = 1;

  matrix->matrix[1][0] = 2;
  matrix->matrix[1][1] = 2;

  float (*func_ptr)(float);
  select_activation_function(&func_ptr);

  matrix_all_values_formula(matrix, func_ptr);

  for(int x=0; x<matrix->sizes[0]; x++){
    for(int y=0; y<matrix->sizes[1]; y++){
      printf("%f ", matrix->matrix[x][y]);
    }
    printf("\n");
  }
}