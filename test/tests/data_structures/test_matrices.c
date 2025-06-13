#include "data_structures/matrix.h"
#include "neural/activation_fnc.h"

#include <stdlib.h>
#include <stdio.h>
#include "unity/unity.h"

// define extern matrix's for the setUp
Matrix *desiredOne;
Matrix *desiredTwo;

Matrix *resultOne;
Matrix *resultTwo;

static void printMatrix(const Matrix *matrix, char *name){
  printf("result of the %s:\n", name);
  for (int x = 0; x < matrix->rows; x++){
    for (int y = 0; y < matrix->cols; y++) printf("%f ", matrix->matrix[x][y]);
  }
  printf("\n");
}

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
  desiredOne = MatrixCreate(2, 2);
  desiredTwo = MatrixCreate(2, 2);

  resultOne = MatrixCreate(2, 2);
  resultTwo = MatrixCreate(2, 2);

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
  MatrixDelete(desiredOne);
  MatrixDelete(desiredTwo);

  MatrixDelete(resultOne);
  MatrixDelete(resultTwo);
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
  Matrix *add = MatrixSubstAdd(resultOne, resultTwo, 1);
  printMatrix(add, "add");

  // type: 0 - sub, 1 - add
  Matrix *sub = MatrixSubstAdd(resultOne, resultTwo, 0);
  printMatrix(sub, "sub");

  compareMatrices(add, desiredOne);
  compareMatrices(sub, desiredTwo);

  MatrixDelete(add);
  MatrixDelete(sub);
}

void testMatrixMultiply(void){
  desiredOne->matrix[0][0] = 2;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 2;
  desiredOne->matrix[1][1] = 2;

  Matrix *mult = MatrixMultiply(resultOne, resultTwo);
  printMatrix(mult , "multiply");

  compareMatrices(mult, desiredOne);
  MatrixDelete(mult);
}

void testMatrixAllValuesFormula(void){
  float (*func_ptr_tan)(float);
  selectTangActivationFunction(&func_ptr_tan);

  float (*func_ptr_sigma)(float);
  selectSigmActivationFunction(&func_ptr_sigma);

  desiredOne->matrix[0][0] = func_ptr_tan(1);
  desiredOne->matrix[0][1] = func_ptr_tan(1);
  desiredOne->matrix[1][0] = func_ptr_tan(1);
  desiredOne->matrix[1][1] = func_ptr_tan(1);

  desiredTwo->matrix[0][0] = func_ptr_sigma(1);
  desiredTwo->matrix[0][1] = func_ptr_sigma(1);
  desiredTwo->matrix[1][0] = func_ptr_sigma(1);
  desiredTwo->matrix[1][1] = func_ptr_sigma(1);

  MatrixApplyFormula(resultOne, func_ptr_tan);
  printMatrix(resultOne, "tan");

  MatrixApplyFormula(resultTwo, func_ptr_sigma);
  printMatrix(resultTwo, "sigma");

  compareMatrices(resultOne, desiredOne);
  compareMatrices(resultTwo, desiredTwo);

  // free function pointers
  func_ptr_tan   = NULL;
  func_ptr_sigma = NULL;
}

void testMatrixCreateFromPointer(void){
  desiredOne->matrix[0][0] = 1;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 3;
  desiredOne->matrix[1][1] = 4;

  const float dataPointer[] = {1.0f, 2.0f, 3.0f, 4.0f};

  Matrix *data = MatrixCreateFromPointer(dataPointer, 2, 2);
  printMatrix(data, "matrix from pointer");

  compareMatrices(data, desiredOne);
  MatrixDelete(data);
}

void testMatrixFullyCoppyMatrix(void){
  desiredOne->matrix[0][0] = 1;
  desiredOne->matrix[0][1] = 2;
  desiredOne->matrix[1][0] = 3;
  desiredOne->matrix[1][1] = 4;

  Matrix *data = MatrixMakeCopy(desiredOne);
  compareMatrices(data, desiredOne);

  MatrixDelete(data);
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