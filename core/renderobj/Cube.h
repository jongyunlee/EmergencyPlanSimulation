#include <iostream>
#include "RenderObject.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glew.h>
#endif

using namespace std;

#ifndef CUBE_H
#define CUBE_H

class Cube: public RenderObject {
 private:
 protected:
  GLfloat size;
 public:
  Cube(GLfloat size) {
    this->size = size;
  }

  void drawObject() {
    /* glEnable(GL_TEXTURE_2D); */
    drawBox(size);
    /* glDisable(GL_TEXTURE_2D); */
  }

  void drawBox(GLfloat size) {
    /* std::cout << "drawBox" << std::endl; */
    glBegin(GL_QUADS);
    GLfloat p = size/2;
    // Front Face
    glVertex3f(-p, -p,  p);  // Bottom Left Of The Texture and Quad
    glVertex3f( p, -p,  p);  // Bottom Right Of The Texture and Quad
    glVertex3f( p,  p,  p);  // Top Right Of The Texture and Quad
    glVertex3f(-p,  p,  p);  // Top Left Of The Texture and Quad
    // Back Face
    glVertex3f(-p, -p, -p);  // Bottom Right Of The Texture and Quad
    glVertex3f(-p,  p, -p);  // Top Right Of The Texture and Quad
    glVertex3f( p,  p, -p);  // Top Left Of The Texture and Quad
    glVertex3f( p, -p, -p);  // Bottom Left Of The Texture and Quad
    // Top Face
    glVertex3f(-p,  p, -p);  // Top Left Of The Texture and Quad
    glVertex3f(-p,  p,  p);  // Bottom Left Of The Texture and Quad
    glVertex3f( p,  p,  p);  // Bottom Right Of The Texture and Quad
    glVertex3f( p,  p, -p);  // Top Right Of The Texture and Quad
    // Bottom Face
    glVertex3f(-p, -p, -p);  // Top Right Of The Texture and Quad
    glVertex3f( p, -p, -p);  // Top Left Of The Texture and Quad
    glVertex3f( p, -p,  p);  // Bottom Left Of The Texture and Quad
    glVertex3f(-p, -p,  p);  // Bottom Right Of The Texture and Quad
    // Right face
    glVertex3f( p, -p, -p);  // Bottom Right Of The Texture and Quad
    glVertex3f( p,  p, -p);  // Top Right Of The Texture and Quad
    glVertex3f( p,  p,  p);  // Top Left Of The Texture and Quad
    glVertex3f( p, -p,  p);  // Bottom Left Of The Texture and Quad
    // Left Face
    glVertex3f(-p, -p, -p);  // Bottom Left Of The Texture and Quad
    glVertex3f(-p, -p,  p);  // Bottom Right Of The Texture and Quad
    glVertex3f(-p,  p,  p);  // Top Right Of The Texture and Quad
    glVertex3f(-p,  p, -p);  // Top Left Of The Texture and Quad
    glEnd();
  }

  void drawBox(GLfloat size, int imageWidth, int imageHeight, GLuint color_tex, uchar4 *dst, GLfloat c, GLfloat lx, GLfloat ly, GLfloat lz, GLfloat oxn, GLfloat oyn) {
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    glBegin(GL_QUADS);
    GLfloat p = size/2;

    GLfloat ox = oxn * c;
    GLfloat oy = oyn * c;

    GLfloat px = lx * p;
    GLfloat py = ly * p;
    GLfloat pz = lz * p;
    GLfloat cx = lx * c;
    GLfloat cy = ly * c;
    GLfloat cz = lz * c;

    // Front Face
    glTexCoord2f(ox + cz,      oy + 0     ); glVertex3f(-px, -py,  pz);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(ox + cz + cx, oy + 0     ); glVertex3f( px, -py,  pz);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(ox + cz + cx, oy + cy    ); glVertex3f( px,  py,  pz);  // Top Right Of The Texture and Quad
    glTexCoord2f(ox + cz,      oy + cy    ); glVertex3f(-px,  py,  pz);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(ox + 2 * cz + 2 * cx, oy + 0 ); glVertex3f(-px, -py, -pz);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(ox + 2 * cz + 2 * cx, oy + cy); glVertex3f(-px,  py, -pz);  // Top Right Of The Texture and Quad
    glTexCoord2f(ox + 2 * cz + 1 * cx, oy + cy); glVertex3f( px,  py, -pz);  // Top Left Of The Texture and Quad
    glTexCoord2f(ox + 2 * cz + 1 * cx, oy + 0 ); glVertex3f( px, -py, -pz);  // Bottom Left Of The Texture and Quad
    // Top Face
    glTexCoord2f(ox + cz,      oy + cy + cz); glVertex3f(-px,  py, -pz);  // Top Left Of The Texture and Quad
    glTexCoord2f(ox + cz,      oy + cy     ); glVertex3f(-px,  py,  pz);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(ox + cz + cx, oy + cy     ); glVertex3f( px,  py,  pz);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(ox + cz + cx, oy + cy + cz); glVertex3f( px,  py, -pz);  // Top Right Of The Texture and Quad
    // Bottom Face
    glTexCoord2f(ox + cz + cx,     oy + cy     ); glVertex3f(-px, -py, -pz);  // Top Right Of The Texture and Quad
    glTexCoord2f(ox + cz + 2 * cx, oy + cy     ); glVertex3f( px, -py, -pz);  // Top Left Of The Texture and Quad
    glTexCoord2f(ox + cz + 2 * cx, oy + cy + cz); glVertex3f( px, -py,  pz);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(ox + cz + cx,     oy + cy + cz); glVertex3f(-px, -py,  pz);  // Bottom Right Of The Texture and Quad
    // Right face
    glTexCoord2f(ox + 2 * cz + cx, oy + 0 ); glVertex3f( px, -py, -pz);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(ox + 2 * cz + cx, oy + cy); glVertex3f( px,  py, -pz);  // Top Right Of The Texture and Quad
    glTexCoord2f(ox + cz + cx,     oy + cy); glVertex3f( px,  py,  pz);  // Top Left Of The Texture and Quad
    glTexCoord2f(ox + cz + cx,     oy + 0 ); glVertex3f( px, -py,  pz);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(ox + 0,  oy + 0 ); glVertex3f(-px, -py, -pz);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(ox + cz, oy + 0 ); glVertex3f(-px, -py,  pz);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(ox + cz, oy + cy); glVertex3f(-px,  py,  pz);  // Top Right Of The Texture and Quad
    glTexCoord2f(ox + 0,  oy + cy); glVertex3f(-px,  py, -pz);  // Top Left Of The Texture and Quad
    glEnd();
  }
};

#endif
