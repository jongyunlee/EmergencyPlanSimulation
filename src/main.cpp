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

#include "../core/bitmap/bmploader.h"
// #include "../core/trackball/TrackBallController.h"
#include "objs/Grid.cpp"
#include "objs/CursorOver.cpp"
#include "objs/Map.cpp"
#include "utils/GridConfigs.cpp"

#include <stdlib.h>
#include <stdio.h>

int width, height;
float lpos[4] = {2,-4,3,0};
GridConfigs *gridConfigs;
CursorOver *cursorOver;
Map *map;
Grid *grid;

bool drag = false;

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
  // grid->enableTrackball(true);
}

void displayObjects() {
  grid->render();
  if (gridConfigs->getDimension() == 2) cursorOver->render();
  map->render();
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
  }
}

void idle()
{
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
