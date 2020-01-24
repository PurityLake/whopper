#ifndef __H_ENTRY__
#define __H_ENTRY__

#ifdef __cplusplus
extern "C" {
#endif

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_ENTRY_COUNT 32

int _max(int a, int b);

#ifndef __cplusplus
typedef struct dirent* dirent;
#endif

typedef struct {
    int namesize, filesize, isdir;
    char *name;
} entry_header;

typedef entry_header** entry_array;

extern entry_header *create_header(int namesize, int filesize, char *name, int isdir);
extern void free_header(entry_header **header);
extern entry_array create_entry_arr(size_t len);
extern void free_entry_arr(entry_array *arr);

#ifdef __cplusplus
}
#endif

#endif /* __H_ENTRY__ */
