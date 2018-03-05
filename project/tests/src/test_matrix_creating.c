#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "tests.h"
#include "utils.h"


#define ARRAY_SIZE(_a) (sizeof(_a) / sizeof((_a)[0]))

#define TEST_DIR "test_matrix_creating"
#define CASE_DIR_PREFIX "case_"
#define IN_FILE "in.txt"

#define N 100


typedef struct TestCase {
    size_t expected_rows_count;
    size_t expected_cols_count;
    double expected_matrix[N][N];
} TestCase;

static void _test_create_from_file(const char *, TestCase);


static TestCase test_cases[] = {
    {
        .expected_rows_count = 3,
        .expected_cols_count = 3,
        .expected_matrix = {
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9},
        }
    },
    {
        .expected_rows_count = 3,
        .expected_cols_count = 3,
        .expected_matrix = {
            {9, 8, 7},
            {6, 5, 4},
            {3, 2, 1},
        }
    },
};

// Dirty, but you must strictly relate the `test_cases` and dirs
void test_matrix_creating(const char *base_dir) {
    printf("Testing of creating matrix from file...");

    char case_dir[10] = {0};

    for (size_t i = 0; i < ARRAY_SIZE(test_cases); i++) {
        snprintf(case_dir, sizeof(case_dir), "%s%zu", CASE_DIR_PREFIX, i);
        char *in = path_join(base_dir, TEST_DIR, case_dir, IN_FILE, (const char *) NULL);

        _test_create_from_file(in, test_cases[i]);

        free(in);
    }

    puts("OK");
}

/*
 * - Create matrix from file.
 * - Check rows count, check cols count.
 * - Check every element of matrix.
 * - Free matrix.
 */
static void _test_create_from_file(const char *in, TestCase test_case) {
    Matrix *matrix = create_matrix_from_file(in);
    assert((matrix != NULL) && "Creating from file was failed");

    size_t rows = 0;
    int res = get_rows(matrix, &rows);
    assert((res == 0) && "Getting rows count was failed");
    assert((rows == test_case.expected_rows_count) && "Invalid rows count");

    size_t cols = 0;
    res = get_cols(matrix, &cols);
    assert((res == 0) && "Getting cols count was failed");
    assert((cols == test_case.expected_cols_count) && "Invalid cols count");

    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            double elem = 0.;
            get_elem(matrix, i, j, &elem);
            assert((elem == test_case.expected_matrix[i][j]) &&
                           "The value of the element does not match the expected");
        }
    }

    res = free_matrix(matrix);
    assert((res == 0) && "Release matrix was failed");
}
