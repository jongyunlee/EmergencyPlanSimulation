#include <stdio.h>

#ifndef TABLE_OBJ
#define TABLE_OBJ

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../../core/renderobj/RenderObject.h"
#include "../../core/bitmap/bmploader.h"

class Table: public RenderObject {
private:
  GLfloat x; GLfloat y; GLfloat z;
  GLfloat xWidth; GLfloat zWidth; GLfloat reg; GLfloat thick;
  uchar4 *dst;
  GLuint color_tex;
  GLuint cube_tex;
  int imageWidth;
  int imageHeight;

public:
  Table(GLfloat x, GLfloat y, GLfloat z,
    GLfloat xWidth, GLfloat zWidth, GLfloat reg, GLfloat thick) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->xWidth = xWidth;
    this->zWidth = zWidth;
    this->reg = reg;
    this->thick = thick;

    LoadBMPFile(&dst, &imageWidth, &imageHeight, "images/marbletexture.bmp"); // this is how to load image
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &color_tex);
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    zoom(-0.9);
    float axis[3] = {1.0, 0.0, 0.0};
    rotateByAxis(-90, axis);
    translate(0.0, 0.0, 0.05);
  }

  void drawObject() {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);

    glColor3f(0.5, 0.5, 0.5);

    glBegin(GL_QUADS);

    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(x-xWidth/2, y, z-zWidth/2);
    glVertex3f(x-xWidth/2, y, z-zWidth/2+thick);
    glVertex3f(x-xWidth/2+thick, y, z-zWidth/2+thick);
    glVertex3f(x-xWidth/2+thick, y, z-zWidth/2);

    glVertex3f(x-xWidth/2, y, z+zWidth/2);
    glVertex3f(x-xWidth/2, y, z+zWidth/2-thick);
    glVertex3f(x-xWidth/2+thick, y, z+zWidth/2-thick);
    glVertex3f(x-xWidth/2+thick, y, z+zWidth/2);

    glVertex3f(x+xWidth/2, y, z+zWidth/2);
    glVertex3f(x+xWidth/2, y, z+zWidth/2-thick);
    glVertex3f(x+xWidth/2-thick, y, z+zWidth/2-thick);
    glVertex3f(x+xWidth/2-thick, y, z+zWidth/2);

    glVertex3f(x+xWidth/2, y, z-zWidth/2);
    glVertex3f(x+xWidth/2, y, z-zWidth/2+thick);
    glVertex3f(x+xWidth/2-thick, y, z-zWidth/2+thick);
    glVertex3f(x+xWidth/2-thick, y, z-zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);

    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2);

    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2+thick, y, z-zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2+thick, y+reg, z-zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2-thick, y, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y, z-zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2-thick, y+reg, z-zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2-thick, y, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z+zWidth/2-thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2-thick, y+reg, z+zWidth/2-thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2+thick, y, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2+thick, y+reg, z+zWidth/2-thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z+zWidth/2-thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);

    glNormal3f(0.0f, 0.0f, -1.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y, z-zWidth/2+thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2+thick, y, z-zWidth/2+thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2+thick, y+reg, z-zWidth/2+thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z-zWidth/2+thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2-thick, y, z-zWidth/2+thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y, z-zWidth/2+thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z-zWidth/2+thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2-thick, y+reg, z-zWidth/2+thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2-thick, y, z+zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y, z+zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2-thick, y+reg, z+zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y, z+zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2+thick, y, z+zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2+thick, y+reg, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2);

    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2+thick, y, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2+thick, y, z-zWidth/2+thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2+thick, y+reg, z-zWidth/2+thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2+thick, y+reg, z-zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2, y, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y, z-zWidth/2+thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z-zWidth/2+thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2, y, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y, z+zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2, y+reg, z+zWidth/2-thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2+thick, y, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2+thick, y, z+zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2+thick, y+reg, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2+thick, y+reg, z+zWidth/2-thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);

    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y, z-zWidth/2+thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2, y, z-zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z-zWidth/2+thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2-thick, y, z-zWidth/2+thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2-thick, y, z-zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2-thick, y+reg, z-zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2-thick, y+reg, z-zWidth/2+thick);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x+xWidth/2-thick, y, z+zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x+xWidth/2-thick, y, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x+xWidth/2-thick, y+reg, z+zWidth/2-thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x+xWidth/2-thick, y+reg, z+zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y, z+zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2, y, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z+zWidth/2-thick);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);

    glTexCoord2f(0.0, 0.0);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.0);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2);
    glTexCoord2f(0.0, 0.5);
    glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2);

    glEnd();
    glDisable(GL_TEXTURE_2D);
  }

  void setPosition(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};

#endif
