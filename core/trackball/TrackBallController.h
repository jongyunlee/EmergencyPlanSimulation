#include <stdio.h>
#include <math.h>
#include "../angel/mat.h"
#include "../angel/vec.h"

#ifndef TRACKBALL_H
#define TRACKBALL_H
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
using namespace std;

int winWidth, winHeight;

float angle, axis[3], trans[3];
bool trackingMouse = false;
bool redrawContinue = false;
bool trackballMove = false;
float lastBallPos[] = {0, 0, 0};
vec3 panning;
vec3 lastPos;
float zooming;
int curx, cury;
int curButton;

typedef void (*ZoomCallBack)(float);
ZoomCallBack zoomCallBack;

void trackball_ptov(int x, int y, int width, int height, float v[3]) {
  float d, a;
  v[0] = (2.0F*x - width) / width;
  v[1] = (2.0F*y - height) / height;
  d = (float) sqrt(v[0]*v[0] + v[1]*v[1]);
  v[2] = (float) cos((M_PI/2.0F) * ((d < 1.0F) ? d : 1.0F));
  a = 1.0F / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  v[0] *= a;
  v[1] *= a;
  v[2] *= a;
}

void startMotion(int x, int y) {
  trackingMouse = true;
  redrawContinue = false;
  curx = x;
  cury = y;
  trackball_ptov(x, y, winWidth, winHeight, lastBallPos);
  trackballMove = true;
  lastPos.x = x;
  lastPos.y = y;
  lastPos.z = 0;
}

void stopMotion(int x, int y) {
  angle = 0.0;
  lastPos.x = 0;
  lastPos.y = 0;
  lastPos.z = 0;
  redrawContinue = false;
  trackballMove = false;
}

void initState(int button) {
  angle = 0;
  curButton = button;
  lastPos.x = 0;
  lastPos.y = 0;
  lastPos.z = 0;
  zooming = 0;
  panning = vec3();
}

void mouseButton(int button, int state, int x, int y) {
  initState(button);
  y=winHeight-y;
  if (button == GLUT_LEFT_BUTTON) {
    switch(state) {
    case GLUT_DOWN:
      startMotion(x, y);
      break;
    case GLUT_UP:
      stopMotion(x, y);
      break;
    }
  } else if (button == GLUT_RIGHT_BUTTON) {
    switch(state) {
    case GLUT_DOWN:
      startMotion(x, y);
      break;
    case GLUT_UP:
      stopMotion(x, y);
      break;
    }
  } else if (button == GLUT_MIDDLE_BUTTON) {
    switch(state) {
    case GLUT_DOWN:
      startMotion(x, y);
      break;
    case GLUT_UP:
      stopMotion(x, y);
      break;
    }
  }
}



void mouseMotion(int x, int y) {
  y = winHeight-y;
  if (curButton == GLUT_LEFT_BUTTON) {
    float curPos[3], dx, dy, dz;
    trackball_ptov(x, y, winWidth, winHeight, curPos);
    if (trackingMouse) {
      dx = curPos[0] - lastBallPos[0];
      dy = curPos[1] - lastBallPos[1];
      dz = curPos[2] - lastBallPos[2];
      /* cout << "dx : " << dx << " dy : " << dy << " dz : " << dz << endl; */
      if (dx || dy || dz) {
	angle = 90.0 * sqrt(dx*dx + dy*dy + dz*dz);
	axis[0] = lastBallPos[2]*curPos[1] - lastBallPos[1]*curPos[2];
	axis[1] = lastBallPos[0]*curPos[2] - lastBallPos[2]*curPos[0];
	axis[2] = lastBallPos[1]*curPos[0] - lastBallPos[0]*curPos[1];
	lastBallPos[0] = curPos[0];
	lastBallPos[1] = curPos[1];
	lastBallPos[2] = curPos[2];
      }
    }
  } else if (curButton == GLUT_RIGHT_BUTTON) {
    zooming = (y - lastPos.y) * 2 / winHeight;
    lastPos = vec3(x, y, 0);
    zoomCallBack(zooming);
    return;
  } else if (curButton == GLUT_MIDDLE_BUTTON) {
    vec3 curPos(x, y, 0);
    panning = curPos - lastPos;
    panning.x = panning.x*2 / winWidth;
    panning.y = panning.y*2 / winHeight;
    lastPos = curPos;
  }
  glutPostRedisplay();
}

void initTrackBall(int width, int height, ZoomCallBack cb) {
  winWidth = width;
  winHeight = height;
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMotion);
  zoomCallBack = cb;
}

void enableTrackball() {
  glutMouseFunc(mouseButton);
  glutMotionFunc(mouseMotion);
}

#endif
