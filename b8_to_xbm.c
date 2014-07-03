#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bitops.h"

// Name your file.
#define IMAGE_NAME "makezine"
// Replace lines with your own data.
const uint8_t large_image[] = {
  B8(11111111),
  B8(11111111),
  B8(00001110),
  B8(00111100),
  B8(11110000),
  B8(11110000),
  B8(00111100),
  B8(00001110),
  B8(11111111),
  B8(11111111),
  B8(00000000),
  B8(01100000),
  B8(11110100),
  B8(10010100),
  B8(10010100),
  B8(11111100),
  B8(11111000),
  B8(10000000),
  B8(00000000),
  B8(11111111),
  B8(11111111),
  B8(00110000),
  B8(01111000),
  B8(11111100),
  B8(11001100),
  B8(10000000),
  B8(00000000),
  B8(01111000),
  B8(11111100),
  B8(11010100),
  B8(11010100),
  B8(11011100),
  B8(01011000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00001110),
  B8(11011111),
  B8(11011111),
  B8(00001110),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
  B8(00000000),
};

int main(void) {
    FILE *file = fopen(IMAGE_NAME ".xbm", "w");
    fputs("#define " IMAGE_NAME "_width 8\n", file);
    fprintf(file, "#define " IMAGE_NAME "_height %d\n", NUM_ELEM(large_image));
    fputs("static unsigned char " IMAGE_NAME "_bits[] = {\n", file);
    for (int i=0; i<NUM_ELEM(large_image); i++) {
        fprintf(file, "%s0x%x", (i==0?"   ":", "), large_image[i]);
    }
    fputs(" };\n", file);
    fclose(file);
    exit(EXIT_SUCCESS);
}
