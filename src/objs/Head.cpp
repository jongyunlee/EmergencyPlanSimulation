#include <iostream>
#include "../../core/bitmap/bmploader.h"
#include "../../core/renderobj/Cube.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Head: public Cube {
private:
  int imageWidth;
  int imageHeight;
  uchar4 *dst;
  GLuint color_tex;
public:

  Head(GLfloat size, int imageWidth, int imageHeight, uchar4 *dst) : Cube(size) {
    this->imageWidth = imageWidth;
    this->imageHeight = imageHeight;
    this->dst = dst;
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
    // drawBox(size);
    drawBox(size, imageWidth, imageHeight, color_tex, dst, 1.0/16.0, 2, 2, 2, 0, 12);
    glDisable(GL_TEXTURE_2D);
  }

  // void drawBox(GLfloat size) {
  //   glBindTexture(GL_TEXTURE_2D, color_tex);
  //   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
  //   glBegin(GL_QUADS);
  //   GLfloat p = size/2;
  //   GLfloat c = 1.0/8.0;
  //   // Front Face
  //   glTexCoord2f(1 * c, 6 * c); glVertex3f(-p, -p,  p);  // Bottom Left Of The Texture and Quad
  //   glTexCoord2f(2 * c, 6 * c); glVertex3f( p, -p,  p);  // Bottom Right Of The Texture and Quad
  //   glTexCoord2f(2 * c, 7 * c); glVertex3f( p,  p,  p);  // Top Right Of The Texture and Quad
  //   glTexCoord2f(1 * c, 7 * c); glVertex3f(-p,  p,  p);  // Top Left Of The Texture and Quad
  //   // Back Face
  //   glTexCoord2f(4 * c, 6 * c); glVertex3f(-p, -p, -p);  // Bottom Right Of The Texture and Quad
  //   glTexCoord2f(4 * c, 7 * c); glVertex3f(-p,  p, -p);  // Top Right Of The Texture and Quad
  //   glTexCoord2f(3 * c, 7 * c); glVertex3f( p,  p, -p);  // Top Left Of The Texture and Quad
  //   glTexCoord2f(3 * c, 6 * c); glVertex3f( p, -p, -p);  // Bottom Left Of The Texture and Quad
  //   // Top Face
  //   glTexCoord2f(1 * c, 8 * c); glVertex3f(-p,  p, -p);  // Top Left Of The Texture and Quad
  //   glTexCoord2f(1 * c, 7 * c); glVertex3f(-p,  p,  p);  // Bottom Left Of The Texture and Quad
  //   glTexCoord2f(2 * c, 7 * c); glVertex3f( p,  p,  p);  // Bottom Right Of The Texture and Quad
  //   glTexCoord2f(2 * c, 8 * c); glVertex3f( p,  p, -p);  // Top Right Of The Texture and Quad
  //   // Bottom Face
  //   glTexCoord2f(2 * c, 7 * c); glVertex3f(-p, -p, -p);  // Top Right Of The Texture and Quad
  //   glTexCoord2f(3 * c, 7 * c); glVertex3f( p, -p, -p);  // Top Left Of The Texture and Quad
  //   glTexCoord2f(3 * c, 8 * c); glVertex3f( p, -p,  p);  // Bottom Left Of The Texture and Quad
  //   glTexCoord2f(2 * c, 8 * c); glVertex3f(-p, -p,  p);  // Bottom Right Of The Texture and Quad
  //   // Right face
  //   glTexCoord2f(3* c, 6 * c); glVertex3f( p, -p, -p);  // Bottom Right Of The Texture and Quad
  //   glTexCoord2f(3 * c, 7 * c); glVertex3f( p,  p, -p);  // Top Right Of The Texture and Quad
  //   glTexCoord2f(2 * c, 7 * c); glVertex3f( p,  p,  p);  // Top Left Of The Texture and Quad
  //   glTexCoord2f(2 * c, 6 * c); glVertex3f( p, -p,  p);  // Bottom Left Of The Texture and Quad
  //   // Left Face
  //   glTexCoord2f(0 * c, 6 * c); glVertex3f(-p, -p, -p);  // Bottom Left Of The Texture and Quad
  //   glTexCoord2f(1 * c, 6 * c); glVertex3f(-p, -p,  p);  // Bottom Right Of The Texture and Quad
  //   glTexCoord2f(1 * c, 7 * c); glVertex3f(-p,  p,  p);  // Top Right Of The Texture and Quad
  //   glTexCoord2f(0 * c, 7 * c); glVertex3f(-p,  p, -p);  // Top Left Of The Texture and Quad
  //   glEnd();
  // }
};
