#include <iostream>
#include <math.h>
using namespace std;

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef GRIDCONFIGS_H
#define GRIDCONFIGS_H

#define	roundd(x)	((x-floor(x))>0.5 ? ceil(x) : floor(x))


class GridConfigs {
private:
  int cursorX;
  int cursorY;
  int screenWidth;
  int screenHeight;
  int dimension;
  float lookDistance2D;
  float lookDistance3D;
  int cursor3dPositionX;
  int cursor3dPositionY;
  bool walkMode;
  float fromWX, fromWY, toWX, toWY;
public:
  GridConfigs() {
	cursor3dPositionX = 0;
	cursor3dPositionY = 0;
    screenWidth = 720;
    screenHeight = 720;
    dimension = 2;
    lookDistance2D = 3.0;
    lookDistance3D = 2.3;
    walkMode = false;
  }

  int getScreenWidth() {
    return screenWidth;
  }

  int getScreenHeight() {
    return screenHeight;
  }

  void lookAtGrid() {
    if (walkMode) {
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(90.0, (GLfloat) screenWidth/(GLfloat)screenHeight, 0.1, 300.0);
      glMatrixMode(GL_MODELVIEW);
      gluLookAt(fromWX, fromWY, 0.07,
      		toWX, toWY, 0.07,
      		0.0f,0.0f,1.0f);
      return;
    }
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
    x = roundd(x*10.0)/10.0;
    y = roundd(y*10.0)/10.0;
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
    if (dimension == 3) {
      cursor3dPositionX = 0;
      cursor3dPositionY = 0;
    }
  }
  int getDimension() {
    return dimension;
  }

  void get3dCursorMovePosition(float (&ret)[2]) {
    ret[0] = ((float)cursor3dPositionX) * 0.1;
    ret[1] = ((float)cursor3dPositionY) * 0.1;
  }

  void move3dPositionX(int m) {
    cursor3dPositionX += m;
  }

  void move3dPositionY(int m) {
    cursor3dPositionY += m;
  }

  void setWalkMode() {
    if (walkMode) {
      walkMode = false;
    } else {
      walkMode = true;
    }
    cout << "setWalkMode : " << walkMode << endl;
  }

  bool getWalkMode() {
    return walkMode;
  }

  void setWalkModeLookAt(float fromX, float fromY, float toX, float toY) {
    fromWX = fromX;
    fromWY = fromY;
    toWX = toX;
    toWY = toY;
  }
};

#endif
