#include <iostream>
#include <assert.h>
#include "../../core/bitmap/bmploader.h"
#include "../../core/renderobj/RenderObject.h"
#include "../utils/GridConfigs.cpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef CURSOROVER_H
#define CURSOROVER_H

class CursorOver: public RenderObject {
private:
  GridConfigs *gridConfigs;
public:
  CursorOver(GridConfigs *gridConfigs) {
    this->gridConfigs = gridConfigs;
  }

  void drawObject() {
    glPushMatrix();
    glColor3f(1.0f,1.0f,0.0f);
    if (gridConfigs ->getDimension() == 2) {
      glBegin(GL_QUADS);
      float p[2];
      gridConfigs->getMapBlockInitialPosition(p);
      float x = p[0];
      float y = p[1];
      glVertex3f(x + 0, y + 0, 0);
      glVertex3f(x + 0, y + 0.1, 0);
      glVertex3f(x + 0.1, y + 0.1, 0);
      glVertex3f(x + 0.1, y + 0, 0);
      glEnd();
    } else if (gridConfigs ->getDimension() == 3) {
      glBegin(GL_QUADS);
      float p[2];
      gridConfigs->get3dCursorMovePosition(p);
      float x = p[0];
      float y = p[1];
      glVertex3f(x + 0, y + 0, 0.01);
      glVertex3f(x + 0, y + 0.1, 0.01);
      glVertex3f(x + 0.1, y + 0.1, 0.01);
      glVertex3f(x + 0.1, y + 0, 0.01);
      glEnd();
    }
    glPopMatrix();
  }
};

#endif
