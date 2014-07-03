#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "bitops.h"

// Name your file.
#define IMAGE_NAME "Smilie_bits"
// Replace lines with your own data.
static unsigned char image[] = {
   0x3c, 0x42, 0xa9, 0x85, 0x85, 0xa9, 0x42, 0x3c };

int main(void) {
    FILE *file = fopen(IMAGE_NAME "_b8.c", "w");
    fputs("const uint8_t large_image[] PROGMEM = {\n", file);
    for (int i=0; i<NUM_ELEM(image); i++) {
        fprintf(file, "%s%s%u%u%u%u%u%u%u%u%s", (i==0?"   ":", "), "B8(",
//Extracting the ones and zeros.
                !!(image[i] & 0x1), 
                !!(image[i] & 0x2), 
                !!(image[i] & 0x4), 
                !!(image[i] & 0x8), 
                !!(image[i] & 0x10), 
                !!(image[i] & 0x20), 
                !!(image[i] & 0x40), 
                !!(image[i] & 0x80), 
                ")" );
    }
    fputs(" };\n", file);
    fclose(file);
    exit(EXIT_SUCCESS);
}
