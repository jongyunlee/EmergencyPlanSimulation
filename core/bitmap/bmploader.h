#ifndef BITMAPLOADER_H
#define BITMAPLOADER_H

typedef struct{
  unsigned char x, y, z, w;
} uchar4;
typedef unsigned char uchar;

// BMP loader
void LoadBMPFile(uchar4 **dst, int *width, int *height, const char *name);

#endif
