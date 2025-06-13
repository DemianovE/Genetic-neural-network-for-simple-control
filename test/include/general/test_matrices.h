#ifndef TEST_MATRICES_H
#define TEST_MATRICES_H

// function to test matrix add and sub
void testMatrixAddSub(void);

// function to test matrix multiply
void testMatrixMultiply(void);

// function to test matrix act fnc multiplication
void testMatrixAllValuesFormula(void);

// functon to test creatio og matrix's from a pointer
void testMatrixCreateFromPointer(void);

// function to test the fully copy of the matrix
void testMatrixFullyCoppyMatrix(void);

// macro to print the matrix's
#define PRINT_MATRIX(A, text) do {                        \
    printf("result of the %s:\n", text);                  \
    for (int x = 0; x < (A)->rows; x++) {             \
        for (int y = 0; y < (A)->cols; y++) {         \
            printf("%f ", (A)->matrix[x][y]);             \
        }                                                 \
        printf("\n");                                     \
    }                                                     \
} while (0)

#endif