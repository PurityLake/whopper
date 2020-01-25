#include "whopper/zip.h"

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

void _recurse_read_dir(entry_array *arr, char *name) {
    static int curr_buf_size = 128;
    char *buf = (char *)malloc(curr_buf_size);
    if (buf != NULL) {
        DIR *dir = opendir(name);
        dirent entry;
        memset(buf, '\0', curr_buf_size);

        if (dir) {
            add_to_entry_array(arr, strlen(name), 0, name, 1);
            readdir(dir); readdir(dir);
            while ((entry = readdir(dir)) != NULL) {
                size_t buf_len = strlen(buf);
                size_t entry_len = strlen(entry->d_name);
                if (buf_len + entry_len + 1 > curr_buf_size) {
                    curr_buf_size += strlen(entry->d_name) + 50;
                    buf = (char *)realloc(buf, curr_buf_size);
                    if (buf != NULL) {
                        memset(buf, '\0', curr_buf_size);
                    } else {
                        fprintf(stderr, "Unable to create memory of size %d\n", curr_buf_size);
                        exit(EXIT_FAILURE);
                    }
                }
                sprintf(buf, "%s/%s", name, entry->d_name);
                _recurse_read_dir(arr, buf);
                memset(buf, '\0', curr_buf_size);
            }
            closedir(dir);
        } else {
            int i = _get_file_size(name);
            add_to_entry_array(arr, strlen(name), i, name, 0);
        }
        free(buf);
    } else {
        fprintf(stderr, "Unable to create memory of size %d\n",  curr_buf_size);
        exit(EXIT_FAILURE);
    }
}

int _recurse_write(entry_array *arr, FILE *f) {
    fwrite(arr->value, sizeof(entry_header), 1, f);
    fwrite(arr->value->name, arr->value->namesize, 1, f);
    if (arr->value->isdir == 0) {
        FILE *file_to_write = fopen(arr->value->name, "r");
        if (file_to_write) {
            char c = fgetc(file_to_write);
            while (!feof(file_to_write)) {
                fprintf(f, "%c", c);
                c = fgetc(file_to_write);
            }
            fclose(file_to_write);
        }
    }
    if (arr->next != NULL) {
        _recurse_write(arr->next, f);
    }
    return 1;
}

int zip(char *dir_to_compress, char *filename) {
    entry_array *arr = create_entry_arr();
    _recurse_read_dir(arr, dir_to_compress);
    FILE *out = fopen(filename, "w");
    _recurse_write(arr, out);
    free_entry_arr(arr);
    fclose(out);
    return 1;
}

#ifdef __cplusplus
extern "C" {
#endif
