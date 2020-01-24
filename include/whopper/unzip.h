#ifndef __H_UNZIP__
#define __H_UNZIP__

#include "entry.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int unzip(char *file_to_decompress, char *where);

#ifdef __cplusplus
}
#endif

#endif /* __H_UNZIP__ */
