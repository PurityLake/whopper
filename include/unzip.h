#ifndef __H_UNZIP__
#define __H_UNZIP__

#include "entry.h"

int unzip(char *file_to_decompress, char *where) {
    FILE *f = fopen(file_to_decompress, "r");
    if (f) {
        entry_header entry;
        fread(&entry, sizeof(entry_header), 1, f);
        int len = entry.namesize + 1;
        int first = 1;
        int oldSize = entry.namesize;
        
        char *name = (char *)malloc(entry.namesize);
        memset(name, '\0', entry.namesize);
        fread(name, entry.namesize, 1, f);

        while(1) {
            if (name != NULL) {
                if (!first) {
                    char buf[100];
                    memset(buf, '\0', 100);
                    sprintf(buf, "%s/%s", where, name + len);
                    if (entry.isdir) {
                        mkdir(buf, 0777);
                    } else {
                        FILE *write_to = fopen(buf, "w");
                        if (write_to) {
                            for (int i = 0; i < entry.filesize; ++i) {
                                fprintf(write_to, "%c", fgetc(f));
                            }
                            fclose(write_to);
                        }
                    }
                } else {
                    mkdir(where, 0777);
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
        fclose(f);
    }
    return 1;
}

#endif /* __H_UNZIP__ */