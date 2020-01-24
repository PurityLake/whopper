#include "zip.h"

#ifdef __cplusplus
extern "C" {
#endif

int _get_file_size(char *filename) {
    FILE *f = fopen(filename, "r");
    if (f) {
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        fclose(f);
        return size;
    }
    return -1;
}

int _recurse_read_dir(entry_array *arr, char *name, int iterations) {
    char buf[100];
    DIR *dir = opendir(name);
    dirent entry;
    int iters = iterations;
    memset(buf, '\0', 100);

    if (dir) {
        **arr = create_header(strlen(name), 0, name, 1);
        ++(*arr);
        ++iters;
        readdir(dir); readdir(dir);
        while ((entry = readdir(dir)) != NULL) {
            sprintf(buf, "%s/%s", name, entry->d_name);
            iters += _recurse_read_dir(arr, buf, 0);
            memset(buf, '\0', 100);
        }
        closedir(dir);
    } else {
        int i = _get_file_size(name);
        **arr = create_header(strlen(name), i, name, 0);
        ++(*arr);
        ++iters;
    }
    return iters;
}

int _recurse_write(entry_array *arr, FILE *f) {
    fwrite((**arr), sizeof(entry_header), 1, f);
    fwrite((**arr)->name, (**arr)->namesize, 1, f);
    if ((**arr)->isdir == 0) {
        FILE *file_to_write = fopen((**arr)->name, "r");
        if (file_to_write) {
            char c = fgetc(file_to_write);
            while (!feof(file_to_write)) {
                fprintf(f, "%c", c);
                c = fgetc(file_to_write);
            }
            fclose(file_to_write);
        }
    }
    ++(*arr);
    if (**arr != NULL) {
        _recurse_write(arr, f);
    }
    return 1;
}

int zip(char *dir_to_compress, char *filename) {
    entry_array arr = create_entry_arr(MAX_ENTRY_COUNT);
    int i = _recurse_read_dir(&arr, dir_to_compress, 0);
    int idx = i;
    while (i > 0) { --arr; --i; }
    FILE *out = fopen(filename, "w");
    _recurse_write(&arr, out);
    i = idx;
    while (i > 0) { --arr; --i; }
    free_entry_arr(&arr);
    return 1;
}

#ifdef __cplusplus
extern "C" {
#endif
