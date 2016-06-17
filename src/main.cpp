/*
 * Final Project for CSE471 Computer Graphics Course
 * Project : Emergency Plan Simulation
 * Author:
 * Jongyun Lee, jongyun@nspoons.com
 * Hyeongmin Kang, humn@unist.ac.kr
 */

#include <stdio.h>
#include <GL/glew.h>
#include "../core/shader/textfile.h"

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
#include "utils/GridConfigs.cpp"

#include "../core/bitmap/bmploader.h"
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
Table *table;

char currentObject;

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
  chair->zoom(2.0f);
  chair->translate(0.8, 0.8, 1.0);
  table = new Table(0,-0.5,0,1.0,0.5,0.4,0.05);
  table->zoom(2.0f);
  table->translate(0.8, 0.8, 1.0);
  grid->enableTrackball(true);
  currentObject = 'w';
#ifdef __APPLE__
  p = createGLSLProgram( "./shader/apple/ex.vert", NULL, "./shader/apple/ex.frag" );
#else
  p = createGLSLProgram( "./shader/win/ex.vert", NULL, "./shader/win/ex.frag" );
#endif

}

void displayObjects() {
  glUseProgram(p);
  if(!gridConfigs->getWalkMode())grid->render();
  if(!gridConfigs->getWalkMode())cursorOver->render();
  map->render();
  glUseProgram(0);
  bg->render();
  map->renderWithoutShader();
  if (gridConfigs->getDimension() == 2 && !gridConfigs->getWalkMode()) { // Displaying Current Selected Object
    if(currentObject == 'c') chair->render();
    else if(currentObject == 't') table->render();
  }
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
  if (gridConfigs->getDimension() == 2) {
    if (key == 'p') {
      gridConfigs->setDimension(3);
    } else if (key == 'c') {
      currentObject = 'c';
    } else if (key == 't') {
      currentObject = 't';
    } else if (key == 'w') {
      currentObject = 'w';
    }
  } else if (gridConfigs->getDimension() == 3) {
    if (key == 'p') {
      gridConfigs->setDimension(2);
    } else if (key == 'w') {
      gridConfigs->move3dPositionY(1);
    } else if (key == 's') {
      gridConfigs->move3dPositionY(-1);
    } else if (key == 'a') {
      gridConfigs->move3dPositionX(-1);
    } else if (key == 'd') {
      gridConfigs->move3dPositionX(+1);
    } else if (key == ' ') {
      map->addPathPosition();
    }
  }

  if (key == 'o') {
    positionCount = 0;
    intervalCount = 0;
    turningCount = 0;
    gridConfigs->setWalkMode();
  }


}

float rotateAxis[3] = {1.0, 1.0, 0.0};

void idle()
{
  if (gridConfigs->getWalkMode()) {
    if (map->hasWalkPosition(positionCount) && map->hasWalkPosition(positionCount+1)) {

      float fromX = map->getXPosition(positionCount);
      float fromY = map->getYPosition(positionCount);
      float toX = map->getXPosition(positionCount+1);
      float toY = map->getYPosition(positionCount+1);
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
  } else {
    if (gridConfigs->getDimension() == 2) {
      if (currentObject == 'c') {
	chair->translate(-0.8, -0.8, -1.0);
	chair->rotateByAxis(0.7, rotateAxis);
	chair->translate(0.8, 0.8, 1.0);
      }
      if (currentObject == 't') {
	table->translate(-0.8, -0.8, -1.0);
	table->rotateByAxis(0.7, rotateAxis);
	table->translate(0.8, 0.8, 1.0);
      }
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
      drag = false;
      if (gridConfigs->getDimension() == 2) {
	if (currentObject == 'c') {
	  map->addChair();
	} else if (currentObject == 't') {
	  map->addTable();
	} else if (currentObject == 'w') {
	  map->addWall();
	}
      }
      break;
    }
  }
}

void menu(int value)
{
  switch(value) {
  case 1:
    if (gridConfigs->getDimension() == 2)gridConfigs->setDimension(3);
    else if (gridConfigs->getDimension() == 3)gridConfigs->setDimension(2);
    break;
  case 2:
    positionCount = 0;
    intervalCount = 0;
    gridConfigs->setWalkMode();
    break;
  case 3:
    currentObject = 'c';
    break;
  case 4:
    currentObject = 't';
    break;
  case 5:
    map->saveAsFile();
    break;
  case 6:
    map->readFile();
    break;
  }
  glutPostRedisplay();
}

void initMenu()
{
  // prepare Sub menu (it should be before glutCreateMenu(menu))
  GLint SubMenu = glutCreateMenu(menu);
  glutAddMenuEntry("Chair",3);
  glutAddMenuEntry("Table",4);

  // Create Main menu
  glutCreateMenu(menu);
  glutAddMenuEntry("Switch perspective",1);
  glutAddMenuEntry("Go!",2);
  glutAddMenuEntry("Save",5);
  glutAddMenuEntry("ReadFile",6);
  glutAddSubMenu("Draw Object",SubMenu);	// attach Sub menu
  glutAttachMenu(GLUT_RIGHT_BUTTON);

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
  initMenu();

  glutMainLoop();
  return 0;
}
