#include <errno.h>
#include "whopper/unzip.h"

#ifdef __cplusplus
extern "C" {
#endif

int unzip(char *file_to_decompress, char *where) {
    FILE *f = fopen(file_to_decompress, "r");
    if (f) {
        entry_header entry;
        entry.namesize = 0;
        entry.filesize = 0;
        entry.isdir = 0;
        entry.name = "";
        fread(&entry, sizeof(entry_header), 1, f);
        int len = entry.namesize;
        int first = 1;
        int oldSize = entry.namesize;
        
        char *name = (char *)malloc(entry.namesize);
        if (name != NULL) {
            memset(name, '\0', entry.namesize);
            fread(name, entry.namesize, 1, f);

            while(1) {
                if (name != NULL) {
                    if (!first) {
                        size_t buf_size = strlen(where) + strlen(name + len);
                        char *buf = (char *)malloc(buf_size);
                        memset(buf, '\0', buf_size);
                        sprintf(buf, "%s/%s", where, name + len);
                        if (entry.isdir) {
                            mkdir(buf, 0700);
                        } else {
                            FILE *write_to = fopen(buf, "w");
                            if (write_to) {
                                for (int i = 0; i < entry.filesize; ++i) {
                                    fprintf(write_to, "%c", fgetc(f));
                                }
                                fclose(write_to);
                            }
                        }
                        free(buf);
                    } else {
                        mkdir(where, 0700);
                        first = 0;
                    }
                    if (!feof(f)) {
                        fread(&entry, sizeof(entry_header), 1, f);
                        memset(name, '\0', oldSize);
                        oldSize = entry.namesize;
                        name = (char *)realloc(name, entry.namesize);
                        memset(name, '\0', entry.namesize);
                        fread(name, entry.namesize, 1, f);
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
            free(name);
        }
        fclose(f);
    }
    return 1;
}
#ifdef __cplusplus
}
#endif
