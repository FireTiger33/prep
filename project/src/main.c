#define _GNU_SOURCE

#include <sys/mman.h>
#include <sys/stat.h>
#include <stdio.h>
#include "header_parser.h"


void free_data(char ***data, int size) {
    for (int i = 0; i < size; i++) {
        free(data[0][i]);
    }
    free(*data);
}


int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char *path_to_eml = argv[1];
    FILE *f = fopen(path_to_eml, "r");
    if (!f) {
        return -1;
    }

    struct stat st;
    fstat(fileno(f), &st);
    char *letter = mmap(
            NULL,
            st.st_size,
            PROT_READ,
            MAP_PRIVATE | MAP_FILE,
            fileno(f),
            0);
    fclose(f);

    if (letter == MAP_FAILED) {
        return MEMORY_ALLOCATION_ERROR;
    }

    off_t offset = 0;
    char *search_field[] = {
            "From:",
            "To:",
            "Date:",
            "Content-Type:",
    };
    int size_data = sizeof(search_field) / sizeof(char*);
    char **data = calloc(size_data, sizeof(char *));
    if (!data) {
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        int check_ret = get_field(search_field[i], letter, st.st_size, &offset, &data[i]);

        if (check_ret == MEMORY_ALLOCATION_ERROR) {
            free_data(&data, i);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    int amount_content = 1;

    if (data[3]) {
        amount_content = search_amount_parts(data[3], strlen(data[3]), letter, &st.st_size);
    }

    if (amount_content == MEMORY_ALLOCATION_ERROR) {
        free_data(&data, size_data);
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i < 3; i++) {
        if (!data[i]) {
            putchar('|');
            continue;
        }
        printf("%s|", data[i]);
    }
    printf("%d", amount_content);

    free_data(&data, size_data);

    return 0;
}
