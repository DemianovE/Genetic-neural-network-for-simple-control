#ifndef TEST_MATRIXES_H
#define TEST_MATRIXES_H

// function to test matrix add and sub
void testMatrixAddSub();

// function to test matrix multiply
void testMatrixMultiply();

// function to test matrix act fnc multiplication
void testMatrixAllValuesFormula();

// functon to test creatio og matrix's from a pointer
void testMatrixCreateFromPointer();

// function to test the fully copy of the matrix
void testMatrixFullyCoppyMatrix();

// macro to print the matrix's
#define PRINT_MATRIX(A, text) do {                        \
    printf("result of the %s:\n", text);                  \
    for (int x = 0; x < (A)->sizes[0]; x++) {             \
        for (int y = 0; y < (A)->sizes[1]; y++) {         \
            printf("%f ", (A)->matrix[x][y]);             \
        }                                                 \
        printf("\n");                                     \
    }                                                     \
} while (0)

#endif