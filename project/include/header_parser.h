#ifndef PROJECT_INCLUDE_HEADER_PARSER_H_
#define PROJECT_INCLUDE_HEADER_PARSER_H_

#define _GNU_SOURCE

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MEMORY_ALLOCATION_ERROR -2
#define NOT_FOUND -3


int search_amount_parts(const char *content_type,
                        off_t len_field,
                        const char *letter,
                        const off_t *size_letter);

int get_field(const char *search_field,
              const char *p_to_file,
              off_t size,
              off_t *offset,
              char **data);

#endif  // PROJECT_INCLUDE_HEADER_PARSER_H_
