#include "general/test_matrices.h"
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

static void compareMatrices(const Matrix *a, const Matrix *b){
  // check if both matrix's have the same size
  TEST_ASSERT_EQUAL(a->rows, b->rows);
  TEST_ASSERT_EQUAL(a->cols, b->cols);

  // check if the values are same
  for(int x=0; x<a->rows; x++){
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(a->matrix[x], b->matrix[x], a->cols);
  }
}

void setUp(void){
  desiredOne = createMatrix(2, 2);
  desiredTwo = createMatrix(2, 2);

  resultOne = createMatrix(2, 2);
  resultTwo = createMatrix(2, 2);

  resultOne->matrix[0][0] = 1;
  resultOne->matrix[0][1] = 1;
  resultOne->matrix[1][0] = 1;
  resultOne->matrix[1][1] = 1;

  resultTwo->matrix[0][0] = 1;
  resultTwo->matrix[0][1] = 1;
  resultTwo->matrix[1][0] = 1;
  resultTwo->matrix[1][1] = 1;
}

void tearDown(void){
  matrixDelete(desiredOne);
  matrixDelete(desiredTwo);

  matrixDelete(resultOne);
  matrixDelete(resultTwo);
}

void testMatrixAddSub(void){
  desiredOne->matrix[0][0] = 2;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 2;
  desiredOne->matrix[1][1] = 2;

  desiredTwo->matrix[0][0] = 0;
  desiredTwo->matrix[0][1] = 0;
  desiredTwo->matrix[1][0] = 0;
  desiredTwo->matrix[1][1] = 0;

  // type: 0 - sub, 1 - add
  Matrix *add = matrixSubstAdd(resultOne, resultTwo, 1);
  PRINT_MATRIX(add, "add");

  // type: 0 - sub, 1 - add
  Matrix *sub = matrixSubstAdd(resultOne, resultTwo, 0);
  PRINT_MATRIX(sub, "sub");

  compareMatrices(add, desiredOne);
  compareMatrices(sub, desiredTwo);

  matrixDelete(add);
  matrixDelete(sub);
}

void testMatrixMultiply(void){
  desiredOne->matrix[0][0] = 2;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 2;
  desiredOne->matrix[1][1] = 2;

  Matrix *mult = matrixMultiply(resultOne, resultTwo);
  PRINT_MATRIX(mult , "multiply");

  compareMatrices(mult, desiredOne);
  matrixDelete(mult);
}

void testMatrixAllValuesFormula(void){
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

  compareMatrices(resultOne, desiredOne);
  compareMatrices(resultTwo, desiredTwo);

  // free function pointers
  func_ptr_tanh = NULL;
  func_ptr_sigm = NULL;
}

void testMatrixCreateFromPointer(void){
  desiredOne->matrix[0][0] = 1;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 3;
  desiredOne->matrix[1][1] = 4;

  const float dataPointer[] = {1, 2, 3, 4};

  Matrix *data = createMatrixFromPointer(dataPointer, 2, 2);
  PRINT_MATRIX(data, "matrix from pointer");

  compareMatrices(data, desiredOne);
  matrixDelete(data);
}

void testMatrixFullyCoppyMatrix(void){
  desiredOne->matrix[0][0] = 1;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 3;
  desiredOne->matrix[1][1] = 4;

  Matrix *data = matrixFullyCopy(desiredOne);
  compareMatrices(data, desiredOne);

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