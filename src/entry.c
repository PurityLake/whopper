#include "whopper/entry.h"

#ifdef __cplusplus
extern "C" {
#endif

int max(int a, int b) { return a > b ? a : b; }

entry_header *create_header(int namesize, int filesize, char *name, int8_t isdir) {
    entry_header *header = (entry_header *)malloc(sizeof(entry_header));
    if (header != NULL) {
        header->namesize = namesize + 1;
        header->filesize = filesize;
        header->isdir = isdir;
        header->name = (char *)malloc(namesize + 1);
        if (header->name != NULL) {
            memset(header->name, '\0', namesize + 1);
            memcpy(header->name, name, strlen(name));
        } else {
            fprintf(stderr, "Unable to create memory of size %d bytes\n", namesize + 1);
            free(header);
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Unable to create memory of size %lu bytes\n", sizeof(entry_header));
        exit(EXIT_FAILURE);
    }
    return header;
}

void free_header(entry_header *header) {
    free(header->name);
    free(header);
}


entry_array *create_entry_arr() {
    entry_array *ret = (entry_array *)malloc(sizeof(entry_array));
    if (ret != NULL) {
        ret->value = NULL;
        ret->next = NULL;
    } else {
        fprintf(stderr, "Unable to create memory of size %lu bytes\n", sizeof(entry_array));
        exit(EXIT_FAILURE);
    }
    return ret;
}

void add_to_entry_array(entry_array *dest, int namesize, int filesize, char *name, int8_t isdir) {
    if (dest->value == NULL) {
        dest->value = create_header(namesize, filesize, name, isdir);
    } else if (dest->next == NULL) {
        dest->next = create_entry_arr();
        add_to_entry_array(dest->next, namesize, filesize, name, isdir);
    } else {
        add_to_entry_array(dest->next, namesize, filesize, name, isdir);
    }
}

void free_entry_arr(entry_array *arr) {
    if (arr->next == NULL) {
        free_header(arr->value);
        free(arr);
    } else {
        free_entry_arr(arr->next);
        free(arr);
    }
}

#ifdef __cplusplus
}
#endif
