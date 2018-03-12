#include <stdio.h>
#include "matrix.h"


void cout_matrix(Matrix *matrix) {
    double var = 0;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            get_elem(matrix, i, j, &var);
            printf("%f ", var);
        }
        putchar('\n');
    }
    putchar('\n');
    free_matrix(matrix);
}

int main() {
    size_t cols_matrix = 0;
    size_t rows_matrix = 0;
    Matrix *matrix = create_matrix_from_file("test_in1.txt");
    Matrix *matrix1 = create_matrix_from_file("test_in2.txt");
    Matrix *matrix_mul = mul(matrix, matrix1);
    Matrix *matrix_sum = sum(matrix, matrix1);
    Matrix *matrix_sub = sub(matrix, matrix1);
    Matrix *matrix_scalar = mul_scalar(matrix, 5.56);
    Matrix *transp_matrix = transp(matrix);
    cout_matrix(matrix);
    cout_matrix(matrix1);
    cout_matrix(matrix_sum);
    cout_matrix(matrix_sub);
    cout_matrix(matrix_scalar);
    cout_matrix(matrix_mul);
    cout_matrix(transp_matrix);
    get_cols(matrix, &cols_matrix);
    get_rows(matrix, &rows_matrix);
    adj();
    det();
    inv();
    set_elem(matrix, 2, 2, 5);
    free_matrix(matrix);
    free_matrix(matrix1);
    free_matrix(matrix_mul);
    free_matrix(matrix_scalar);
    free_matrix(matrix_sub);
    free_matrix(matrix_sum);
    free_matrix(transp_matrix);
    return 0;
}

