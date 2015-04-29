#include "print.h"
#include <stdio.h>

void postscript_from_matrix(matrix_t *matrix, uint32_t (*colorfunction)(uint32_t), char *filename) {
  FILE *file = fopen(filename, "wb");
  int scale = 10;

  fprintf(file, "%%!PC-Adobe-3.0 EPSF-3,0\n");
  fprintf(file, "%%%%BoundingBox: 0 0 %d %d \n", matrix->width*scale, matrix->height*scale);

  fprintf(file, "/cell {\n");
  fprintf(file, "%d 0 rlineto\n", scale);
  fprintf(file, "0 %d rlineto\n", scale);
  fprintf(file, "-%d 0 rlineto\n", scale);
  fprintf(file, "closepath\n");
  fprintf(file, "gsave\n");
  fprintf(file, "fill\n");
  fprintf(file, "grestore\n");
  fprintf(file, "0 0 0 setrgbcolor\n");
  fprintf(file, "stroke\n");
  fprintf(file, "} def\n");

  for (int z = 0; z < 1; z++) {
    for (int y = 0; y < matrix->height; y++) {
      for (int x = 0; x < matrix->width; x++) {
        uint32_t value = matrix->values[z][y][x];

        uint32_t rgb = (*colorfunction)(value);

        int red = rgb >> 16 & 0xFF;
        int green = rgb >> 8 & 0xFF;
        int blue = rgb >> 0 & 0xFF;

        fprintf(file, "newpath\n");
        fprintf(file, "%d %d moveto\n", x*scale, (matrix->height - y - 1)*scale);
        fprintf(file, "%d %d %d setrgbcolor\n", red, green, blue);
        fprintf(file, "cell\n");
      }
    }
  }
  fclose(file);
}
