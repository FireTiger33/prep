#include "header_parser.h"


static char *coustom_strcasestr(const char *str1, size_t len_str1, const char *str2, size_t len_str2) {
    if (len_str2 > len_str1) {
        return NULL;
    }
    for (size_t i = 0; i <= len_str1 - len_str2; i++) {
        if (tolower(str1[i]) == tolower(str2[0])) {
            size_t j = 0;

            for (j = 0; j < len_str2; j++) {
                if (tolower(str1[i + j]) != tolower(str2[j])) {
                    break;
                }
            }
            if (j == len_str2) {
                return (char *) str1 + i;
            }
        }
    }

    return NULL;
}


static int str_finished_symbol(char c, int add) {
    if (c == '\n') {
        return 1;
    }
    if (c == '\r') {
        return 1;
    }
    if (c == '\0') {
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


static int search_key(const char *key, const char *field, const off_t *len_field, char **p_key) {
    size_t len_key = strlen(key);
    *p_key = coustom_strcasestr(field, *len_field, key, len_key);

    if (!*p_key) {
        return 1;
    }

    return 0;
}

static int get_boundary(char **p_boundary, char **p_boundary_end, off_t *boundary_size, char **boundary) {
    *p_boundary_end = *p_boundary;
    while (!str_finished_symbol(**p_boundary_end, 1) && **p_boundary_end != '\0') {
        *p_boundary_end += 1;
    }
    if (**p_boundary == '"') {
        *p_boundary += 1;
        *p_boundary_end -= 1;
    }

    *boundary_size = *p_boundary_end - *p_boundary;
    *boundary = (char *) malloc(*boundary_size + 1);

    if (!*boundary) {
        return MEMORY_ALLOCATION_ERROR;
    }

    memcpy(*boundary, *p_boundary, *boundary_size);
    boundary[0][*boundary_size] = '\0';

    return 0;
}

int search_amount_parts(const char *content_type,
                        const off_t len_field,
                        const char *letter,
                        const off_t *size_letter) {
    char *p_boundary = NULL;
    if (search_key("multipart", content_type, &len_field, &p_boundary)) {
        return 1;
    }
    if (search_key("boundary=", letter, size_letter, &p_boundary)) {
        return 1;
    }

    unsigned int amount_boundary = 0;
    p_boundary += 9;
    char *boundary = NULL;
    char *p_boundary_end = NULL;
    off_t boundary_size = 0;

    if (get_boundary(&p_boundary, &p_boundary_end, &boundary_size, &boundary)) {
        return MEMORY_ALLOCATION_ERROR;
    }

    off_t remaining_size_letter = *size_letter - (p_boundary - letter);

    while (remaining_size_letter > boundary_size) {
        p_boundary = memmem(p_boundary + 1, remaining_size_letter, boundary, boundary_size);

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


static int search_field_from_header(const char *search_field,
                                    const char *p_to_file,
                                    const off_t *size_file,
                                    char **p_to_field) {
    size_t len_search_field = strlen(search_field);
    *p_to_field = memmem(p_to_file, *size_file, search_field, len_search_field);

    if (!*p_to_field) {
        return NOT_FOUND;
    }

    if (*p_to_field != p_to_file) {
        while (*(*p_to_field - 1) != '\n' && *(*p_to_field - 1) != '\r') {
            size_t remaining_size_letter = *size_file - (*p_to_field - p_to_file);
            *p_to_field = memmem(*p_to_field + 1, remaining_size_letter, search_field, len_search_field);

            if (!*p_to_field) {
                return NOT_FOUND;
            }
        }
    }

    *p_to_field += len_search_field;

    while (**p_to_field == ' ') {
        *p_to_field += 1;
    }

    return 0;
}

static int write_field(char *it_file, off_t *offset, off_t size_file, char **data) {
    *data = calloc(1, strlen(it_file));
    if (!(*data)) {
        return MEMORY_ALLOCATION_ERROR;
    }

    for (unsigned int k = 0; *offset < size_file; k++) {
        while (str_finished_symbol(*it_file, 0) && str_finished_symbol(*(it_file + 1), 0)) {
            if (*offset == size_file) {
                break;
            }
            it_file++;
            *offset += 1;
        }
        if (str_finished_symbol(*it_file, 0)) {
            it_file++;
            *offset += 1;

            if (*it_file != ' ') {
                break;
            }
            while (*(it_file + 1) == ' ') {
                it_file++;
                *offset += 1;
            }
        }

        data[0][k] = *it_file;
        it_file++;
        *offset += 1;
    }

    return 0;
}

int get_field(const char *search_field, const char *p_to_file, off_t size_file, off_t *offset, char **data) {
    char *p_to_field = NULL;

    if (search_field_from_header(search_field, p_to_file, &size_file, &p_to_field)) {
        return NOT_FOUND;
    }

    *offset = p_to_field - p_to_file;

    if (write_field(p_to_field, offset, size_file, data)) {
        return MEMORY_ALLOCATION_ERROR;
    }

    return 0;
}
