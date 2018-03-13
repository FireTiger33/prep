#include <stdio.h>
#include "matrix.h"


int main() {
    size_t cols_matrix = 0;
    size_t rows_matrix = 0;
    double det_matrix = 0.;
    size_t cols = 0;
    Matrix *matrix = create_matrix_from_file("test_in3.txt");
    Matrix *matrix1 = create_matrix_from_file("test_in2.txt");
    Matrix *inv_matrix = inv(matrix);
    Matrix *matrix_mul = mul(matrix, matrix1);
    Matrix *matrix_sum = sum(matrix, matrix1);
    Matrix *matrix_sub = sub(matrix, matrix1);
    Matrix *matrix_scalar = mul_scalar(matrix, 5.56);
    Matrix *transp_matrix = transp(matrix);

    cout_matrix(matrix);
    get_cols(matrix, &cols);

    cout_matrix(inv_matrix);
    cout_matrix(matrix1);
    cout_matrix(matrix_sum);
    cout_matrix(matrix_sub);
    cout_matrix(matrix_scalar);
    cout_matrix(matrix_mul);
    cout_matrix(transp_matrix);

    get_cols(matrix, &cols_matrix);
    get_rows(matrix, &rows_matrix);
    adj(matrix);
    det(matrix, &det_matrix);
    inv(matrix);
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

