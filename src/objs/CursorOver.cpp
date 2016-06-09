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
    glBegin(GL_QUADS);
    // float rx = (float)gridConfigs->getCursorX() / (float)gridConfigs->getScreenWidth();
    // float ry = (float)(gridConfigs->getScreenHeight() - gridConfigs->getCursorY()) / (float)gridConfigs->getScreenHeight();
    // float x = -1.05 + 2 * rx;
    // float y = -1.05 + 2 * ry;
    // x = round(x*10)/10;
    // y = round(y*10)/10;
    float p[2];
    gridConfigs->getMapBlockInitialPosition(p);
    float x = p[0];
    float y = p[1];
    glVertex3f(x + 0, y + 0, 0);
    glVertex3f(x + 0, y + 0.1, 0);
    glVertex3f(x + 0.1, y + 0.1, 0);
    glVertex3f(x + 0.1, y + 0, 0);
    glEnd();
  }
};

#endif
