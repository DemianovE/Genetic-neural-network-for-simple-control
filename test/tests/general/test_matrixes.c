#include "general/test_matrixes.h"
#include "general/matrix_math.h"
#include "neural/activation_fnc.h"

#include <stdlib.h>
#include <stdio.h>
#include "unity/unity.h"

// define extern matrix's for the setUp
Matrix *desiredOne;
Matrix *desiredTwo;

Matrix *resultOne;
Matrix *resultTwo;

static void compareMatrixes(const Matrix *a, const Matrix *b){
  // check if both matrix's have the same size
  TEST_ASSERT_EQUAL(a->sizes[0], b->sizes[0]);
  TEST_ASSERT_EQUAL(a->sizes[1], b->sizes[1]);

  // check if the values are same
  for(int x=0; x<a->sizes[0]; x++){
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(a->matrix[x], b->matrix[x], a->sizes[1]);
  }
}

static int* allocSizes() {
  int *sizes = malloc(2 * sizeof(int));
  sizes[0] = 2;
  sizes[1] = 2;
  return sizes;
}

void setUp(){
  desiredOne = malloc(sizeof(Matrix));
  desiredTwo = malloc(sizeof(Matrix));

  resultOne = malloc(sizeof(Matrix));
  resultTwo = malloc(sizeof(Matrix));

  createMatrix(desiredOne, allocSizes());
  createMatrix(desiredTwo, allocSizes());

  createMatrix(resultOne, allocSizes());
  createMatrix(resultTwo, allocSizes());

  resultOne->matrix[0][0] = 1;
  resultOne->matrix[0][1] = 1;
  resultOne->matrix[1][0] = 1;
  resultOne->matrix[1][1] = 1;

  resultTwo->matrix[0][0] = 1;
  resultTwo->matrix[0][1] = 1;
  resultTwo->matrix[1][0] = 1;
  resultTwo->matrix[1][1] = 1;
}

void tearDown(){
  matrixDelete(desiredOne);
  matrixDelete(desiredTwo);

  matrixDelete(resultOne);
  matrixDelete(resultTwo);
}

void testMatrixAddSub(){
  Matrix *add = malloc(sizeof(struct Matrix));
  Matrix *sub = malloc(sizeof(struct Matrix));

  desiredOne->matrix[0][0] = 2;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 2;
  desiredOne->matrix[1][1] = 2;

  desiredTwo->matrix[0][0] = 0;
  desiredTwo->matrix[0][1] = 0;
  desiredTwo->matrix[1][0] = 0;
  desiredTwo->matrix[1][1] = 0;

  // type: 0 - sub, 1 - add
  matrixSubstAdd(resultOne, resultTwo, add, 1);
  PRINT_MATRIX(add, "add");

  // type: 0 - sub, 1 - add
  matrixSubstAdd(resultOne, resultTwo, sub, 0);
  PRINT_MATRIX(sub, "sub");

  // ensure the correct output of the function
  compareMatrixes(add, desiredOne);
  compareMatrixes(sub, desiredTwo);

  // clear all matrix's
  matrixDelete(add);
  matrixDelete(sub);
}

void testMatrixMultiply(){
  Matrix *mult = malloc(sizeof(struct Matrix));

  desiredOne->matrix[0][0] = 2;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 2;
  desiredOne->matrix[1][1] = 2;

  matrixMultiply(resultOne, resultTwo, mult);
  PRINT_MATRIX(mult , "multiply");

  // ensure the matrix is as desired
  compareMatrixes(mult, desiredOne);

  // clear all matrix's
  matrixDelete(mult);
}

void testMatrixAllValuesFormula(){
  float (*func_ptr_tanh)(float);
  selectTangActivationFunction(&func_ptr_tanh);

  float (*func_ptr_sigm)(float);
  selectSigmActivationFunction(&func_ptr_sigm);

  desiredOne->matrix[0][0] = func_ptr_tanh(1);
  desiredOne->matrix[0][1] = func_ptr_tanh(1);
  desiredOne->matrix[1][0] = func_ptr_tanh(1);
  desiredOne->matrix[1][1] = func_ptr_tanh(1);

  desiredTwo->matrix[0][0] = func_ptr_sigm(1);
  desiredTwo->matrix[0][1] = func_ptr_sigm(1);
  desiredTwo->matrix[1][0] = func_ptr_sigm(1);
  desiredTwo->matrix[1][1] = func_ptr_sigm(1);

  matrixAllValuesFormula(resultOne, func_ptr_tanh);
  PRINT_MATRIX(resultOne, "tahn");

  matrixAllValuesFormula(resultTwo, func_ptr_sigm);
  PRINT_MATRIX(resultTwo, "sigm");

  compareMatrixes(resultOne, desiredOne);
  compareMatrixes(resultTwo, desiredTwo);

  // free function pointers
  func_ptr_tanh = NULL;
  func_ptr_sigm = NULL;
}

void testMatrixCreateFromPointer(){
  Matrix *data = malloc(sizeof(struct Matrix));

  desiredOne->matrix[0][0] = 1;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 3;
  desiredOne->matrix[1][1] = 4;

  float dataPointer[] = {1, 2, 3, 4};

  createMatrixFromPointer(data, dataPointer, allocSizes());
  PRINT_MATRIX(data, "matrix from pointer");

  compareMatrixes(data, desiredOne);

  matrixDelete(data);
}

void testMatrixFullyCoppyMatrix(){
  Matrix *data    = malloc(sizeof(struct Matrix));

  desiredOne->matrix[0][0] = 1;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 3;
  desiredOne->matrix[1][1] = 4;

  fullyCopyMatrix(desiredOne, data);
  compareMatrixes(data, desiredOne);

  matrixDelete(data);
}

int main(void) {
  UNITY_BEGIN();

  RUN_TEST(testMatrixAddSub);
  RUN_TEST(testMatrixMultiply);
  RUN_TEST(testMatrixAllValuesFormula);
  RUN_TEST(testMatrixCreateFromPointer);
  RUN_TEST(testMatrixFullyCoppyMatrix);

  return UNITY_END();
}