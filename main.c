#include "whopper.h"

int main(int argc, char **argv) {
    if (argc > 1) {
        char *option = argv[1];
        if (strcmp(option, "--zip") == 0) {
            char *dir_to_compress = argv[2];
            char *filename = argv[3];
            zip(dir_to_compress, filename);
        } else if (strcmp(option, "--unzip") == 0) {
            char *file_to_decompress = argv[2];
            char *where = argv[3];
            unzip(file_to_decompress, where);
        }
    }
    return EXIT_SUCCESS;
}
