#include "matrix.h"


int free_matrix(Matrix* matrix) {
    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->ret[i]);
    }
    free(matrix->ret);
    free(matrix);
    return 0;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->ret = (double **)malloc(sizeof(double *) * rows);
    if (!matrix->ret) {
        fprintf(stderr, "Can't create matrix. Memory error.\n");
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->ret[i] = (double *)calloc(cols, sizeof(double));
        if (!matrix->ret[i]) {
            matrix->rows = i;
            free_matrix(matrix);
            fprintf(stderr, "Can't create matrix. \n");
            return NULL;
        }
    }
    return matrix;
}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE *f = fopen(path_file, "r");
    size_t n_rows = 0;
    size_t n_cols = 0;
    if (!f) {
        fprintf(stderr, "Can't open file %s: err == %s\n", path_file, strerror(errno));
        return NULL;
    }
    int fields_read = fscanf(f, "%zu %zu", &n_rows, &n_cols);
    if (fields_read != 2) {
        fprintf(stderr, "Can't read n_rows/n_cols\n");
        fclose(f);
        return NULL;
    }
    Matrix *matrix = create_matrix(n_rows, n_cols);
    for (size_t i = 0; i < n_rows; i++) {
        for (size_t j = 0; j < n_cols; j++) {
            int read_objects = fscanf(f, "%lf", &matrix->ret[i][j]);
            if (read_objects != 1) {
                free_matrix(matrix);
                fclose(f);
                return NULL;
            }
        }
    }
    fclose(f);
    return matrix;
}

int get_rows(const Matrix* matrix, size_t* rows) {
    *rows = matrix->rows;
    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    *cols = matrix->cols;
    return 0;
}

int get_elem(const Matrix* matrix, int row, int col, double* val) {
    *val = matrix->ret[row][col];
    return 0;
}

int set_elem(Matrix* matrix, int row, int col, double val) {
    matrix->ret[row][col] = val;
    return 0;
}

Matrix* mul_scalar(const Matrix* matrix, double val) {
    Matrix *matrix_mul = create_matrix(matrix->rows, matrix->cols);
    if (!matrix_mul) {
        return NULL;
    }
    for (size_t i = 0; i < matrix_mul->rows; i++) {
        for (size_t j = 0; j < matrix_mul->cols; j++) {
            matrix_mul->ret[i][j] = matrix->ret[i][j] * val;
        }
    }
    return matrix_mul;
}

Matrix* transp(const Matrix* matrix) {
    Matrix *transp_matrix = create_matrix(matrix->cols, matrix->rows);
    if (!transp_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            transp_matrix->ret[j][i] = matrix->ret[i][j];
        }
    }
    return transp_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (l->rows != r->rows || l->cols != r->cols) {
        printf(stderr, "Can't sum matrixes.\n");
        return NULL;
    }
    Matrix *matrix_sum = create_matrix(l->rows, l->cols);
    for (size_t i = 0; i < matrix_sum->rows; i++) {
        for (size_t j = 0; j < matrix_sum->cols; j++) {
            matrix_sum->ret[i][j] = l->ret[i][j] + r->ret[i][j];
        }
    }
    return matrix_sum;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    if (l->rows != r->rows || l->cols != r->cols) {
        fprintf(stderr, "Can't sub matrixes\n");
        return NULL;
    }
    Matrix *matrix_sub = create_matrix(l->rows, l->cols);
    if (!matrix_sub) {
        return NULL;
    }
    for (size_t i = 0; i < matrix_sub->rows; i++) {
        for (size_t j = 0; j < matrix_sub->cols; j++) {
            matrix_sub->ret[i][j] = l->ret[i][j] - r->ret[i][j];
        }
    }
    return matrix_sub;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l->cols != r->rows) {
        fprintf(stderr, "Can't multiplication matrixes.\n");
        return NULL;
    }
    Matrix *matrix_mul = create_matrix(l->rows, r->cols);
    if (!matrix_mul) {
        return NULL;
    }
    for (size_t i = 0; i < r->cols; i++) {
        for (size_t j = 0; j < l->rows; j++) {
            for (size_t k = 0; k < r->rows; k++) {
                matrix_mul->ret[i][j] += l->ret[i][k] * r->ret[k][j];
            }
        }
    }
    return matrix_mul;
}

int det(/*const Matrix* matrix, double* val*/) {
    return 0;
}

Matrix* adj(/*const Matrix* matrix*/) {
    return NULL;
}

Matrix* inv(/*const Matrix* matrix*/) {
    return NULL;
}
