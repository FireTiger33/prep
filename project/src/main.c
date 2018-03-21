#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>


int search_content(char *boundary, char *p, off_t *offset, const off_t *st_size) {
    //printf("search_content\n\n");
    //printf("boundary = %s\n", boundary);
    int ret = 0;
    while (*offset < *st_size) {

        printf("state = ");
        for (int i = 0; i < 20; i++) {
            printf("%c", *(p+i));
        }
        printf("\nret = %d\n" ,ret);
        puts("");

        if (*p == '-' && *(p+2) == boundary[0]) {
            p += 2;
            *offset += 2;
            unsigned int i = 0;
            for (i = 0; i < strlen(boundary) && p[0] == boundary[i]; i++) {
                p++;
                *offset += 1;
            }
            if (i == strlen(boundary)) {
                ret++;
                //printf("ret = %d\n", ret);
            }
        }
        while (*p++ != '\n' && *p != '\r' && *offset < *st_size) {
            *offset += 1;
        }
        while (*p == '\n' || *p == '\r') {
            *offset += 1;
            p++;
        }
    }
    return ret/2;
}

int search_parts(char *content_type, char *p, off_t *offset, const off_t *st_size) {
    if (!content_type) {
        return 0;
    }
    char *boundary = "boundary=";
    if (content_type[0] == 'm') {
        for (unsigned int i = 0; i < strlen(content_type); i++, content_type++) {
            if (content_type[0] == 'b') {
                for (int j = 0; content_type[0] == boundary[j]; j++) {
                    content_type++;
                }
                if (content_type[0] == '"') {
                    content_type++;
                    content_type[strlen(content_type)-1] = '\0';
                }
                break;
            }
        }
        return search_content(content_type, p, offset, st_size);
    }
    return 1;
}


int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }

    const char *path_to_eml = argv[1];
    //puts(path_to_eml);

    FILE* f = fopen(path_to_eml, "r");
    if (!f)
    {
        return -1;
    }

    struct stat st;
    fstat(fileno(f), &st);

    char* letter = mmap(
            NULL,
            st.st_size,
            PROT_READ,
            MAP_PRIVATE | MAP_FILE,
            fileno(f),
            0
    );
    if (letter == MAP_FAILED) {
        return -2;
    }

    char *p = letter;
    off_t offset = 0;
    char *search_field[12] = {
            "From:",
            "To:",
            "Date:",
            "Content-Type:",
            "boundary="
    };
    char **data = calloc(4, sizeof(char*));
    if (!data) {
        return 1;
    }


    int amount_str = 0;
    while (offset < st.st_size && *p != '\n' && *p != '\r') {
        //printf("offset = %ld p = %d\n", offset, *p);
        //printf("state = %c\n", *p);
        for (unsigned int i = 0; i < 4; i++) {  // поиск искомых строк
            if (search_field[i][0] == *p && !data[i]) {
                unsigned int j = 0;
                for (j = 0; j < strlen(search_field[i]) && *p++ == search_field[i][j]; j++) {
                    offset++;
                }
                while (*p == ' ') {  // избавляемся от лишних пробелов после заголовка
                    p++;
                    offset++;
                }

                if (j == strlen(search_field[i])) {  // запись при находе
                    data[i] = calloc(1, strlen(p));
                    for (unsigned int k = 0; ; k++, offset++, p++) {
                        if (!data[i]) {
                            return 1;
                        }
                        if (*p == '\n') {
                            //offset++;
                            //p++;
                            amount_str++;
                            if (*(p+1) != ' ') {
                                break;
                            }
                            while (*(p+1) == ' ') {
                                offset++;
                                p++;
                            }
                        }
                        data[i][k] = *p;
                    }
                }
            }
        }
        while (*p++ != '\n' && *p != '\r') {
            offset++;
            //printf("size = %ld, offset = %ld\n", st.st_size, offset);
        }
        /*if (*p == '\n' || *p == '\r') {
            p++;
        }*/
        amount_str++;
    }

    //printf("str = %d\n", amount_str);
    /*
    for (int i = 0; i < 4; i++) {
        printf("%s%s\n", search_field[i], data[i]);
    }
    */

    while (*p++ == '\n' && *p == '\r') {
        offset++;
    }
    int amount_content = search_parts(data[3], p, &offset, &st.st_size);
    for (int i = 0; i < 3; i++) {
        printf("%s|", data[i]);
        //printf("%s%s\n", search_field[i], data[i]);
        free(data[i]);
    }
    printf("%d", amount_content);
    puts("");
    free(data);

    return 0;
}
