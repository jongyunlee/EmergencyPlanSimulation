/*
 * Final Project for CSE471 Computer Graphics Course
 * Project : Emergency Plan Simulation
 * Author:
 * Jongyun Lee, jongyun@nspoons.com
 * Hyungmin Ganh,
 */

#include <stdio.h>
#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <iostream>
#include <assert.h>
#include "math.h"

#include "objs/Grid.cpp"
#include "objs/CursorOver.cpp"
#include "objs/Map.cpp"
#include "objs/Night.cpp"
#include "objs/Chair.cpp"
#include "utils/GridConfigs.cpp"

#include "../core/bitmap/bmploader.h"
#include "../core/shader/textfile.h"
// #include "../core/trackball/TrackBallController.h"

#include <stdlib.h>
#include <stdio.h>

int width, height;
float lpos[4] = {2,-4,3,0};
GridConfigs *gridConfigs;
CursorOver *cursorOver;
Map *map;
Grid *grid;
Night *bg;
GLuint p;
bool drag = false;
int positionCount;
int intervalCount;
int turningCount;
Chair *chair;

void init(void) {
  glewInit();
  glClearColor (0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHT0);

  glShadeModel(GL_SMOOTH);

  // init objects
  grid = new Grid(gridConfigs);
  cursorOver = new CursorOver(gridConfigs);
  map = new Map(gridConfigs);
  bg = new Night(8);
  chair = new Chair(0,-0.5,0,0.5,0.5,0.5,0.4, 0.05);
  grid->enableTrackball(true);
#ifdef __APPLE__
  p = createGLSLProgram( "./shader/apple/ex.vert", NULL, "./shader/apple/ex.frag" );
#else
  p = createGLSLProgram( "./shader/win/ex.vert", "./shader/win/ex.geom", "./shader/win/ex.frag" );
#endif

}

void displayObjects() {
  glUseProgram(p);
  grid->render();
  cursorOver->render();
  map->render();
  glUseProgram(0);
  bg->render();
  chair->render();
}


void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // test
  glClearColor (0.0, 0.0, 0.0, 0.0);
  // glMatrixMode(GL_PROJECTION);
  // glLoadIdentity();
  // glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 400);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_POSITION, lpos); // test
  gridConfigs->lookAtGrid();
  displayObjects();
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  // initTrackBall(w, h, NULL);
  // disableTrackball();
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  width = w;
  height = h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, 0.0, 100);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glLightfv(GL_LIGHT0, GL_POSITION, lpos); // test
  gridConfigs->lookAtGrid();
}

void keyboard (unsigned char key, int x, int y) {
  if (key == 'p') {
    if (gridConfigs->getDimension() == 2)gridConfigs->setDimension(3);
    else if (gridConfigs->getDimension() == 3)gridConfigs->setDimension(2);
  } else if (key == 'w') {
    if (gridConfigs->getDimension() == 3)gridConfigs->move3dPositionY(1);
  } else if (key == 's') {
    if (gridConfigs->getDimension() == 3)gridConfigs->move3dPositionY(-1);
  } else if (key == 'a') {
    if (gridConfigs->getDimension() == 3)gridConfigs->move3dPositionX(-1);
  } else if (key == 'd') {
    if (gridConfigs->getDimension() == 3)gridConfigs->move3dPositionX(+1);
  } else if (key == ' ') {
    if (gridConfigs->getDimension() == 3)map->addPathPosition();
  } else if (key == 'o') {
    positionCount = 0;
    intervalCount = 0;
    turningCount = 0;
    gridConfigs->setWalkMode();
  }
}



void idle()
{
  if (gridConfigs->getWalkMode()) {
    if (map->hasWalkPosition(positionCount) && map->hasWalkPosition(positionCount+1)) {

      float fromX = map->getXPosition(positionCount);
      float fromY = map->getYPosition(positionCount);
      float toX = map->getXPosition(positionCount+1);
      float toY = map->getYPosition(positionCount+1);
      // if (intervalCount > 200) {
      if (turningCount > 100) {
	intervalCount = 0;
	turningCount = 0;
	positionCount++;
      } else if (intervalCount > 100) {
	turningCount++;
	if (intervalCount <= 200)intervalCount++;
	if (map->hasWalkPosition(positionCount+2)) {
	  float nextToX = map->getXPosition(positionCount+2);
	  float nextToY = map->getYPosition(positionCount+2);
	  float resultToX = toX + (turningCount / 100.0) * (nextToX - toX);
	  float resultToY = toY + (turningCount / 100.0) * (nextToY - toY);
	  gridConfigs->setWalkModeLookAt(fromX + ((toX-fromX) * intervalCount / 200), fromY + ((toY-fromY) * intervalCount / 200), resultToX, resultToY);
	} else {
	  gridConfigs->setWalkModeLookAt(fromX + ((toX-fromX) * intervalCount / 200), fromY + ((toY-fromY) * intervalCount / 200), toX, toY);
	}
      } else {
	intervalCount++;
	gridConfigs->setWalkModeLookAt(fromX + ((toX-fromX) * intervalCount / 200), fromY + ((toY-fromY) * intervalCount / 200), toX, toY);
      }
    } else {
      gridConfigs->setWalkMode();
    }
  }
  glutPostRedisplay();
}

void mouseRoutine(int x, int y) {
  gridConfigs->setCursorPosition(x, y);
}

void mouseMotion(int x, int y) {
  gridConfigs->setCursorPosition(x, y);
  if (drag && gridConfigs->getDimension() == 2) map->addWallWithoutToggle();
}



void mouseButton(int button, int state, int x, int y) {
  if (button == GLUT_LEFT_BUTTON) {
    switch(state) {
    case GLUT_DOWN:
      drag = true;
      break;
    case GLUT_UP:
      // if (gridConfigs->getDimension() == 2) map->addWall();
      drag = false;
      break;
    }
  }
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  gridConfigs = new GridConfigs();
  glutInitWindowSize(gridConfigs->getScreenWidth(), gridConfigs->getScreenHeight());
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMotionFunc(mouseMotion);
  glutMouseFunc(mouseButton);
  glutPassiveMotionFunc(mouseRoutine);
  glutMainLoop();
  return 0;
}
