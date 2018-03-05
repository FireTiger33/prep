#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "matrix.h"
#include "tests.h"
#include "utils.h"


#define ARRAY_SIZE(_a) (sizeof(_a) / sizeof((_a)[0]))

#define TEST_DIR "test_matrix_determinant"
#define CASE_DIR_PREFIX "case_"
#define IN_FILE "in.txt"


static void _test_determinant(const char *, double);


static double determinants[] = {
    -200., 18.,
};

void test_matrix_determinant(const char *base_dir) {
    printf("Testing of getting matrix determinant...");

    char case_dir[10] = {0};

    for (size_t i = 0; i < ARRAY_SIZE(determinants); i++) {
        snprintf(case_dir, sizeof(case_dir), "%s%zu", CASE_DIR_PREFIX, i);
        char *in = path_join(base_dir, TEST_DIR, case_dir, IN_FILE, (const char *) NULL);

        _test_determinant(in, determinants[i]);

        free(in);
    }

    puts("OK");
}

void _test_determinant(const char *in, double expected_det) {
    Matrix *matrix = create_matrix_from_file(in);

    double result_det = 0.;
    int res = det(matrix, &result_det);
    assert((res == 0) && "Getting determinant was failed");
    assert((result_det == expected_det) && "The determinants do not coincide");

    free_matrix(matrix);
}
