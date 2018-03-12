#include "matrix.h"


int cout_matrix(const Matrix *matrix) {
    if (!matrix) {
        return -1;
    }

    double var = 0;
    size_t cols = 0;
    size_t rows = 0;

    get_cols(matrix, &cols);
    get_rows(matrix, &rows);
    putchar('\n');
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            get_elem(matrix, i, j, &var);
            printf("%f ", var);
        }
        putchar('\n');
    }
    putchar('\n');
    return 0;
}


int free_matrix(Matrix* matrix) {
    if (!matrix) {
        return -1;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        free(matrix->ret[i]);
    }
    free(matrix->ret);
    free(matrix);
    return 0;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    Matrix *matrix = (Matrix *)malloc(sizeof(Matrix));
    if (!matrix) {
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->ret = (double **)malloc(sizeof(double *) * rows);
    if (!matrix->ret) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->ret[i] = (double *)calloc(cols, sizeof(double));
        if (!matrix->ret[i]) {
            matrix->rows = i - 1;
            free_matrix(matrix);
            return NULL;
        }
    }
    return matrix;
}

Matrix* create_matrix_from_file(const char* path_file) {
    FILE *f = fopen(path_file, "r");

    if (!f) {
        return NULL;
    }

    size_t n_rows = 0;
    size_t n_cols = 0;

    int fields_read = fscanf(f, "%zu %zu", &n_rows, &n_cols);
    if (fields_read != 2) {
        fclose(f);
        return NULL;
    }

    Matrix *matrix = create_matrix(n_rows, n_cols);

    if (!matrix) {
        fclose(f);
        return NULL;
    }
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
    if (!matrix || !rows) {
        return -1;
    }

    *rows = matrix->rows;

    return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (!matrix || !cols) {
        return -1;
    }

    *cols = matrix->cols;

    return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val) {
    if (!matrix || !val) {
        return -1;
    }
    if (row > matrix->rows || col > matrix->cols) {
        return -2;
    }

    *val = matrix->ret[row][col];

    return 0;
}

int set_elem(Matrix* matrix, size_t row, size_t col, double val) {
    if (!matrix) {
        return -1;
    }
    if (row > matrix->rows || col > matrix->cols) {
        return -2;
    }

    matrix->ret[row][col] = val;

    return 0;
}

Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (!matrix) {
        return NULL;
    }

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
    if (!matrix) {
        return NULL;
    }

    Matrix *transp_matrix = create_matrix(matrix->cols, matrix->rows);

    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            transp_matrix->ret[j][i] = matrix->ret[i][j];
        }
    }
    return transp_matrix;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }
    if (l->rows != r->rows || l->cols != r->cols) {
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
    if (!l || !r) {
        return NULL;
    }
    if (l->rows != r->rows || l->cols != r->cols) {
        return NULL;
    }

    Matrix *matrix_sub = create_matrix(l->rows, l->cols);

    for (size_t i = 0; i < matrix_sub->rows; i++) {
        for (size_t j = 0; j < matrix_sub->cols; j++) {
            matrix_sub->ret[i][j] = l->ret[i][j] - r->ret[i][j];
        }
    }
    return matrix_sub;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (!l || !r) {
        return NULL;
    }
    if (l->cols != r->rows) {
        return NULL;
    }

    Matrix *matrix_mul = create_matrix(l->rows, r->cols);

    for (size_t i = 0; i < r->cols; i++) {
        for (size_t j = 0; j < l->rows; j++) {
            for (size_t k = 0; k < r->rows; k++) {
                matrix_mul->ret[i][j] += l->ret[i][k] * r->ret[k][j];
            }
        }
    }
    return matrix_mul;
}


Matrix* matrix_copy(const Matrix* matrix) {
    Matrix *new_matrix = create_matrix(matrix->rows, matrix->cols);

    if (!new_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            new_matrix->ret[i][j] = matrix->ret[i][j];
        }
    }
    return new_matrix;
}

Matrix* custom_matrix_copy(const Matrix* matrix, size_t x, size_t y) {
    Matrix *new_matrix = create_matrix(matrix->rows - 1, matrix->cols - 1);

    if (!new_matrix) {
        return NULL;
    }
    for (size_t i = 0, i_new = 0; i < matrix->rows; i++) {
        for (size_t j = 0, j_new = 0; j < matrix->cols; j++) {
            if (i == x) {
                i_new--;
                break;
            }
            if (j == y) {
                continue;
            }
            new_matrix->ret[i_new][j_new] = matrix->ret[i][j];
            j_new++;
        }
        i_new++;
    }
    return new_matrix;
}

int search_null(Matrix *matrix, size_t *x, size_t *y, size_t start_i_j) {
    size_t scale = matrix->cols;

    for (size_t i = start_i_j; i < scale; i++) {
        for (size_t j = start_i_j; j < scale; j++) {
            if (matrix->ret[i][j] != 0) {
                *y = i;
                *x = j;
                return 0;
            }
        }
    }
    return 1;
}

void swap_rows(Matrix *matrix, size_t x1, size_t x2) {
    double *buf = matrix->ret[x1];

    matrix->ret[x1] = matrix->ret[x2];
    matrix->ret[x2] = buf;
}

void swap_cols(Matrix *matrix, size_t x1, size_t x2) {
    for (size_t x = 0; x < matrix->rows; x++) {
        double tmp = matrix->ret[x][x1];
        matrix->ret[x][x1] = matrix->ret[x][x2];
        matrix->ret[x][x2] = tmp;
    }
}

int det(const Matrix* matrix, double* val) {
    if (!matrix) {
        return 1;
    }

    size_t cols = matrix->cols;

    if (cols != matrix->rows || cols == 0) {
        return 1;
    }
    if (cols == 1) {
        *val = matrix->ret[0][0];
        return 0;
    }
    if (cols == 2) {
        *val = matrix->ret[0][0] * matrix->ret[1][1] - matrix->ret[0][1] * matrix->ret[1][0];
        return 0;
    }

    Matrix *new_matrix = matrix_copy(matrix);
    int sign = 0;
    size_t x = 0;
    size_t y = 0;
    *val = 1;

    for (size_t i = 0; i < cols; i++) {
        if (new_matrix->ret[i][i] == 0) {
            if (search_null(new_matrix, &x, &y, i)) {
                free_matrix(new_matrix);
                *val = 0;
                return 0;
            }
            if (i != y) {
                swap_rows(new_matrix, i, y);
                sign = !sign;
            }
            if (i != x) {
                swap_cols(new_matrix, i, x);
                sign = !sign;
            }
        }
        *val *= new_matrix->ret[i][i];
        double tmp = new_matrix->ret[i][i];
        for (x = i; x < cols; x++) {
            new_matrix->ret[i][x] = new_matrix->ret[i][x] / tmp;
        }
        for (y = i + 1; y < cols; y++) {
            tmp = new_matrix->ret[y][i];
            for (x = i; x < cols; x++)
                new_matrix->ret[y][x] -= (new_matrix->ret[i][x] * tmp);
        }
    }
    if (*val < 0) {
        *val = (unsigned long long int)(*val*100000*(-1));
        *val = (double)(*val*(-1));
    } else {
        *val = (unsigned long long int)(*val*100000);
    }
    *val /= 100000;
    if (sign) {
        *val *= -1;
    }
    free_matrix(new_matrix);
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }

    Matrix *adj_matrix = create_matrix(matrix->rows, matrix->cols);
    Matrix *new_matrix = NULL;

    if (!adj_matrix) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            new_matrix = custom_matrix_copy(matrix, i, j);
            if (!new_matrix) {
                return NULL;
            }
            if (det(new_matrix, &adj_matrix->ret[j][i])) {
                return NULL;
            }
            if ((i + j) % 2) {
                adj_matrix->ret[j][i] *= -1;
            }
            free_matrix(new_matrix);
        }
    }
    return adj_matrix;
}

Matrix* inv(const Matrix* matrix) {
    if (!matrix) {
        return NULL;
    }

    double det_matrix = 0;
    Matrix *inv_matrix = NULL;

    if (det(matrix, &det_matrix)) {
        return NULL;
    }
    if (det_matrix == 0) {
        inv_matrix = create_matrix(matrix->rows, matrix->cols);
        if (!inv_matrix) {
            return NULL;
        }
        for (size_t i = 0; i < matrix->cols; i++) {
            inv_matrix->ret[i][i] = 1;
        }
        return inv_matrix;
    }

    Matrix *adj_matrix = adj(matrix);

    if (!adj_matrix) {
        return NULL;
    }

    inv_matrix = mul_scalar(adj_matrix, 1/det_matrix);

    if (!inv_matrix) {
        return NULL;
    }
    return inv_matrix;
}
