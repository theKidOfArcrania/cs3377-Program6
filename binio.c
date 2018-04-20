#include <stdio.h>
#include "prog5.h"

#define check_read(file, ptr, size) do {                 \
  if (fread((ptr), (size), 1, (file)->handle) != (size)) \
    goto errOut;                                         \
  }                                                      \
} while(0)

struct bin_file_data {
  FILE*      handle;
  bin_header head;
  bin_record next;
}

HBIN bin_open(char* filename) {
  struct bin_file_data* file = malloc(sizeof(struct bin_file_data));
  if (!file) {
    goto errOut;
  }

  if (!(file->handle = fopen(filename, "rb"))) {
    goto errOut;
  }

  check_read(file, &file->head, sizeof(struct bin_header));
  return (HBIN)f;

errOut:
  free(file);
  return NULL;
}

#define file ((struct bin_file_data)hfile)
struct bin_header* bin_getHeader(HBIN hfile) {
  return &file->head;
}

struct bin_record* bin_next(HBIN hfile) {
  check_read(file, &file->next, sizeof(struct bin_record));
  return &file->next;

errOut:
  return NULL;
}

void bin_close(HBIN hfile) {
  fclose(file->handle);
  free(hfile);
}
