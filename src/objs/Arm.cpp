#include <iostream>
#include "../../core/bitmap/bmploader.h"
#include "../../core/renderobj/Cube.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Arm: public Cube {
private:
  int imageWidth;
  int imageHeight;
  uchar4 *dst;
  GLuint color_tex;
  bool left;
public:

  Arm(GLfloat size, int imageWidth, int imageHeight, uchar4 *dst, bool left) : Cube(size) {
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    this->dst = dst;
    this->left = left;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &color_tex);
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  void drawObject() {
    glEnable(GL_TEXTURE_2D);
    if (left) {
      // drawBox(size, imageWidth, imageHeight, color_tex, dst, 1.0/16.0, 1, 3, 1, 0, 8);
      drawBox(size, imageWidth, imageHeight, color_tex, dst, 1.0/16.0, 1, 3, 1, 8, 0);
    } else {
      drawBox(size, imageWidth, imageHeight, color_tex, dst, 1.0/16.0, 1, 3, 1, 10, 8);
    }
    glDisable(GL_TEXTURE_2D);
  }

};
