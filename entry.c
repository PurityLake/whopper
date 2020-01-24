#include "entry.h"

#ifdef __cplusplus
extern "C" {
#endif

int max(int a, int b) { return a > b ? a : b; }

entry_header *create_header(int namesize, int filesize, char *name, int isdir) {
    entry_header *header = (entry_header *)malloc(sizeof(entry_header));
    header->namesize = namesize;
    header->filesize = filesize;
    header->isdir = isdir;
    header->name = (char *)malloc(namesize + 1);
    memset(header->name, '\0', namesize + 1);
    memcpy(header->name, name, strlen(name));
    return header;
}

void free_header(entry_header **header) {
    free((*header)->name);
    free(*header);
}


entry_array create_entry_arr(size_t len) {
    entry_array arr = (entry_array)malloc(sizeof(entry_header*) * len);
    for (int i = 0; i < len; ++i) {
        arr[i] = NULL;
    } 
    return arr;
}

void free_entry_arr(entry_array *arr) {
    entry_array a = *arr;
    while((*a) != NULL) {
        free_header(a);
        ++a;
    }
}
#ifdef __cplusplus
}
#endif
