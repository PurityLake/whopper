#include "whopper/entry.h"

#ifdef __cplusplus
extern "C" {
#endif

int max(int a, int b) { return a > b ? a : b; }

entry_header *create_header(int namesize, int filesize, char *name, int isdir) {
    entry_header *header = (entry_header *)malloc(sizeof(entry_header));
    header->namesize = namesize + 1;
    header->filesize = filesize;
    header->isdir = isdir;
    header->name = (char *)malloc(namesize + 1);
    memset(header->name, '\0', namesize + 1);
    memcpy(header->name, name, strlen(name));
    return header;
}

void free_header(entry_header *header) {
    free(header->name);
    free(header);
}


entry_array *create_entry_arr() {
    entry_array *ret = (entry_array *)malloc(sizeof(entry_array));
    ret->value = NULL;
    ret->next = NULL;
    return ret;
}
void add_to_entry_array(entry_array *dest, entry_header *value) {
    if (dest->value == NULL) {
        dest->value = value;
    } else if (dest->next == NULL) {
        dest->next = create_entry_arr();
        add_to_entry_array(dest->next, value);
    } else {
        add_to_entry_array(dest->next, value);
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
