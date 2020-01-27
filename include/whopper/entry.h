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

#ifndef __cplusplus
typedef struct dirent* dirent;
#endif

typedef struct {
    int namesize, filesize;
    int8_t isdir;
    char *name;
} entry_header;

typedef struct _entry_array{
    entry_header *value;
    struct _entry_array *next;
} entry_array;

extern entry_header *create_header(int namesize, int filesize, char *name, int8_t isdir);
extern void free_header(entry_header *header);
extern entry_array *create_entry_arr();
extern void add_to_entry_array(entry_array *dest,  int namesize, int filesize, char *name, int8_t isdir);
extern void free_entry_arr(entry_array *arr);

#ifdef __cplusplus
}
#endif

#endif /* __H_ENTRY__ */
