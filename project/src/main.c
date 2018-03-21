#define _GNU_SOURCE
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>


int str_finished_symbol(char c, int add) {
    if (c == '\n') {
        return 1;
    }
    if (c == '\r') {
        return 1;
    }
    if (add) {
        if (c == ' ') {
            return 1;
        }
        if (c == ';') {
            return 1;
        }
    }
    return 0;
}

int search_amount_parts(const char *content_type, const char *letter, const off_t *size_letter) {
    char *p_boundary = strcasestr(content_type, "multipart");

    if (p_boundary) {
        p_boundary = strcasestr(letter, "boundary=");

        if (p_boundary) {
            unsigned int amount_boundary = 0;
            char *p_boundary_end = p_boundary;
            p_boundary += 9;

            while (!str_finished_symbol(*p_boundary_end, 2)) {
                p_boundary_end++;
            }

            if (*p_boundary == '"') {
                p_boundary++;
                p_boundary_end--;
            }

            off_t boundary_size = p_boundary_end - p_boundary;

            char *boundary = (char *)malloc(boundary_size + 1);
            memcpy(boundary, p_boundary, boundary_size);
            boundary[boundary_size] = '\0';
            off_t remaining_size_letter = *size_letter - (p_boundary - letter);

            while (remaining_size_letter > boundary_size) {
                p_boundary = memmem(p_boundary+1, remaining_size_letter, boundary, boundary_size);

                if (!p_boundary) {
                    if (amount_boundary == 0 || remaining_size_letter > 2 * boundary_size) {
                        amount_boundary++;
                    }

                    break;
                }

                remaining_size_letter = *size_letter - (p_boundary - letter);
                p_boundary_end = p_boundary + boundary_size;
                amount_boundary++;
            }

            free(boundary);

            return amount_boundary - 1;
        }
    }

    return 1;
}


int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];
    FILE* f = fopen(path_to_eml, "r");
    if (!f) {
        return -1;
    }

    struct stat st;
    fstat(fileno(f), &st);
    char *p = NULL;
    off_t offset = 0;
    char *search_field[12] = {
            "From:",
            "To:",
            "Date:",
            "Content-Type:",
    };

    char* letter = mmap(
            NULL,
            st.st_size,
            PROT_READ,
            MAP_PRIVATE | MAP_FILE,
            fileno(f),
            0);
    fclose(f);

    if (letter == MAP_FAILED) {
        return -2;
    }

    char **data = calloc(4, sizeof(char*));
    if (!data) {
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        p = memmem(letter, st.st_size, search_field[i], strlen(search_field[i]));

        if (!p) {
            continue;
        }

        if (p != letter) {
            while (*(p - 1) != '\n' && *(p - 1) != '\r') {
                size_t remaining_size_letter = st.st_size - (p - letter);
                p = memmem(p + 1, remaining_size_letter, search_field[i], strlen(search_field[i]));
            }
        }

        p += strlen(search_field[i]);

        while (*p == ' ') {
            p++;
            offset++;
        }

        char *p_copy = p;
        offset = p - letter;
        data[i] = calloc(1, strlen(p_copy));
        if (!data[i]) {
            for (int k = i - 1; k > 0; k--) {
                free(data[k]);
            }
            free(data);
            return 1;
        }

        for (unsigned int k = 0; offset < st.st_size; k++) {
            while (str_finished_symbol(*p_copy, 0) && str_finished_symbol(*(p_copy+1), 0)) {
                if (offset == st.st_size) {
                    break;
                }
                p_copy++;
                offset++;
            }
            if (str_finished_symbol(*p_copy, 0)) {
                p_copy++;
                offset++;

                if (*p_copy != ' ') {
                    break;
                }
                while (*(p_copy+1) == ' ') {
                    p_copy++;
                    offset++;
                }
            }

            data[i][k] = *p_copy;
            p_copy++;
            offset++;
        }
    }

    int amount_content = 1;

    if (data[3]) {
        amount_content = search_amount_parts(data[3], letter, &st.st_size);
    }

    for (int i = 0; i < 3; i++) {
        if (!data[i]) {
            putchar('|');
            continue;
        }
        printf("%s|", data[i]);
        free(data[i]);
    }
    printf("%d", amount_content);
    puts("");
    free(data[3]);
    free(data);

    return 0;
}
