#include <stdio.h>
#include <assert.h>
#include <cdk.h>
#include <errno.h>
#include <string.h>

#include "prog6.h"

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void update_cell(int x, int y, const char*);

CDKMATRIX* myMatrix;           // CDK Screen Matrix

int main() {
  CDKSCREEN* cdkscreen;
  WINDOW* window;
  const char* rowTitles[6] = {"Z", "a", "b", "c", "d", "e"};
  const char* columnTitles[6] = {"Z", "a", "b", "c", "d", "e"};
  int boxWidths[6] = {18, 18, 18, 18, 18, 18};
  int boxTypes[6] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  const char* filename = "cs3377.bin";
  char buff[MAX_RECORD_STRING_LENGTH + 1];

  HBIN hfile = bin_open(filename);
  if (!hfile) {
    fprintf(stderr, "File %s failed to open: %s\n", filename, strerror(errno));
    return 1;
  }

  struct bin_header* header = bin_getHeader(hfile);

  // Initialize cdk screen
  window = initscr();
  cdkscreen = initCDKScreen(window);
  initCDKColor();

  // Create the matrix
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, 
      MATRIX_HEIGHT, MATRIX_WIDTH, "Worker Matrix", (char **) columnTitles, 
      (char **) rowTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);
  
  if (myMatrix == NULL) {
    fprintf(stderr, "Error creating Matrix\n");
    return 1;
  }

  drawCDKMatrix(myMatrix, true);
  
  sprintf(buff, "Magic: 0x%08X", header->magicNumber);
  update_cell(1,1, buff);

  sprintf(buff, "Version: %u", header->versionNumber);
  update_cell(1,2, buff);

  sprintf(buff, "NumRecords: %lu", header->numRecords);
  update_cell(1,3, buff);

  uint32_t display = MIN(MATRIX_HEIGHT - 1, header->numRecords);
  for (int i = 0; i < display; i++) {
    struct bin_record* next = bin_next(hfile);
    if (!next) {
      endCDK();
      fprintf(stderr, "Cannot read next entry: %s\n", strerror(errno));
      return 1;
    }
    
    sprintf(buff, "strlen: %u", next->strLength);
    update_cell(i+2, 1, buff);
    
    strncpy(buff, next->buff, sizeof(buff));
    buff[sizeof(buff) - 1] = 0;
    update_cell(i+2, 2, buff);
  }

  bin_close(hfile);

  // Wait for user input.
  getc(stdin);

  endCDK();
}


void update_cell(int x, int y, const char* label)
{
  cleanCDKMatrixCell(myMatrix, x, y);
  setCDKMatrixCell(myMatrix, x, y, label);
  drawCDKMatrix(myMatrix, true);
}


