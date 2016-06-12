#include <iostream>
#include "../../core/bitmap/bmploader.h"
#include "../../core/renderobj/Cube.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Night: public Cube {
private:
  int imageWidth;
  int imageHeight;
  uchar4 *dst;
  GLuint color_tex;
public:

  Night(GLfloat size) : Cube(size) {
      LoadBMPFile(&dst, &imageWidth, &imageHeight, "images/night.bmp"); // this is how to load image
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
      glGenTextures(1, &color_tex);
      glBindTexture(GL_TEXTURE_2D, color_tex);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  Night(GLfloat size, Night *mob) : Cube(size) {
    this->imageWidth = mob->imageWidth;
    this->imageHeight = mob->imageHeight;
    this->color_tex = mob->color_tex;
    this->dst = mob->dst;
  }

  void drawObject() {
    glEnable(GL_TEXTURE_2D);
    drawBox(size);
    glDisable(GL_TEXTURE_2D);
  }

  void drawBox(GLfloat size) {
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_QUADS);
    GLfloat p = size/2;
    // Front Face
    glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p,  p);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0, 1.0); glVertex3f( p, -p,  p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0, 1.0); glVertex3f( p,  p,  p);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0, 0.0); glVertex3f(-p,  p,  p);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p, -p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(0.0, 1.0); glVertex3f(-p,  p, -p);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0, 1.0); glVertex3f( p,  p, -p);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0, 0.0); glVertex3f( p, -p, -p);  // Bottom Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(0.0, 0.0); glVertex3f(-p,  p, -p);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0, 1.0); glVertex3f(-p,  p,  p);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0, 1.0); glVertex3f( p,  p,  p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0, 0.0); glVertex3f( p,  p, -p);  // Top Right Of The Texture and Quad
    // Bottom Face
    glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p, -p);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0, 1.0); glVertex3f( p, -p, -p);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0, 1.0); glVertex3f( p, -p,  p);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0, 0.0); glVertex3f(-p, -p,  p);  // Bottom Right Of The Texture and Quad
    // Right face
    glTexCoord2f(0.0, 0.0); glVertex3f( p, -p, -p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(0.0, 1.0); glVertex3f( p,  p, -p);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0, 1.0); glVertex3f( p,  p,  p);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0, 0.0); glVertex3f( p, -p,  p);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0, 0.0); glVertex3f(-p, -p, -p);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0, 1.0); glVertex3f(-p, -p,  p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0, 1.0); glVertex3f(-p,  p,  p);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0, 0.0); glVertex3f(-p,  p, -p);  // Top Left Of The Texture and Quad
    glEnd();
  }
};
