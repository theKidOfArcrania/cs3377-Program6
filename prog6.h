#include <inttypes.h>
#include <sys/types.h>
#define MAX_RECORD_STRING_LENGTH 25

// Screw the classes... I HATE C++ classes
struct bin_header {
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

struct bin_record {
  uint8_t strLength;
  char    buff[MAX_RECORD_STRING_LENGTH];
};

// bin file handle
typedef struct _bin_file {
  int _unused;
} *HBIN;

// Binary reading io
HBIN bin_open(const char* filename);
struct bin_header* bin_getHeader(HBIN hfile);
struct bin_record* bin_next(HBIN hfile);
void bin_close(HBIN hfile);
