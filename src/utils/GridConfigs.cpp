#include <iostream>
#include <math.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef GRIDCONFIGS_H
#define GRIDCONFIGS_H

class GridConfigs {
private:
  int cursorX;
  int cursorY;
  int screenWidth;
  int screenHeight;
  int dimension;
  float lookDistance2D;
  float lookDistance3D;
public:
  GridConfigs() {
    screenWidth = 512;
    screenHeight = 512;
    dimension = 2;
    lookDistance2D = 3.0;
    lookDistance3D = 2.3;
  }

  int getScreenWidth() {
    return screenWidth;
  }

  int getScreenHeight() {
    return screenHeight;
  }

  void lookAtGrid() {
    if (dimension == 2) {
      lookAt2DGrid();
    } else if (dimension == 3) {
      lookAt3DGrid();
    }
  }

  void lookAt2DGrid() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 400);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0.0,0.0,lookDistance2D,
    	      0.0,0.0,0.0,
    	      0.0f,1.0f,0.0f);
  }

  void lookAt3DGrid() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, (GLfloat) screenWidth/(GLfloat)screenHeight, 1.0, 300.0);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(-lookDistance3D,-lookDistance3D,lookDistance3D,
    	      0.0,0.0,0.0,
    	      1.0f,1.0f,1.0f);
  }

  void setCursorPosition(int x, int y) {
    cursorX = x;
    cursorY = y;
  }

  int getCursorX() {
    return cursorX;
  }

  int getCursorY() {
    return cursorY;
  }

  void getMapBlockInitialPosition(float (&ret)[2]) {
    float rx = (float)this->getCursorX() / (float)this->getScreenWidth();
    float ry = (float)(this->getScreenHeight() - this->getCursorY()) / (float)this->getScreenHeight();
    float x = -1.05 + 2 * rx;
    float y = -1.05 + 2 * ry;
    x = round(x*10)/10;
    y = round(y*10)/10;
    ret[0] = x;
    ret[1] = y;
  }

  void getMapBlockIndex(int (&ret)[2]) {
    float p[2];
    getMapBlockInitialPosition(p);
    int x = p[0] * 10 + 10;
    int y = p[1] * 10 + 10;
    ret[0] = x;
    ret[1] = y;
  }

  void setDimension(int dimension) {
    this->dimension = dimension;
  }
  int getDimension() {
    return dimension;
  }
};

#endif
