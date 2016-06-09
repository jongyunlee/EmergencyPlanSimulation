#include <iostream>
#include "../utils/GridConfigs.cpp"
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef MAP_H
#define MAP_H

class Map {
private:
  GridConfigs *gridConfigs;
  int map[20][20];
public:

  Map(GridConfigs *gridConfigs) {
    this->gridConfigs = gridConfigs;
    for (int i=0; i<20; i++) {
      for (int j=0; j<20; j++) {
	map[i][j] = 0;
      }
    }

  }

  void render() {
    for (int i=0; i<20; i++) {
      for (int j=0; j<20; j++){
    	if (map[i][j] == 1) drawCube((i-10)*0.1 + 0.05, (j-10)*0.1 + 0.05);
      }
    }
    // drawCube((0-10)*0.1 + 0.05, (0-10)*0.1 + 0.05);
  }

  void addWall() {
    int p[2];
    gridConfigs->getMapBlockIndex(p);
    if (map[p[0]][p[1]] == 0) {
      map[p[0]][p[1]] = 1;
    } else {
      map[p[0]][p[1]] = 0;
    }
  }

  void printMap() {
    for (int i=0; i<20; i++) {
      for (int j=0; j<20; j++) {
	cout << map[j][i] << " ";
      }
      cout << endl;
    }
  }

  void drawCube(float offX, float offY) {
    glBegin(GL_QUADS);
    // top
    // glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glVertex3f(offX + -0.05f, offY + 0.05f, 0.05f);
    glVertex3f(offX + 0.05f, offY +0.05f, 0.05f);
    glVertex3f(offX + 0.05f, offY + 0.05f, -0.05f);
    glVertex3f(offX + -0.05f, offY + 0.05f, -0.05f);

    glEnd();

    glBegin(GL_QUADS);
    // front
    // glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(offX + 0.05f, offY + -0.05f, 0.05f);
    glVertex3f(offX + 0.05f, offY + 0.05f, 0.05f);
    glVertex3f(offX + -0.05f, offY + 0.05f, 0.05f);
    glVertex3f(offX + -0.05f, offY + -0.05f, 0.05f);

    glEnd();

    glBegin(GL_QUADS);
    // right
    // glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glVertex3f(offX + 0.05f, offY + 0.05f, -0.05f);
    glVertex3f(offX + 0.05f, offY + 0.05f, 0.05f);
    glVertex3f(offX + 0.05f, offY + -0.05f, 0.05f);
    glVertex3f(offX + 0.05f, offY + -0.05f, -0.05f);

    glEnd();

    glBegin(GL_QUADS);
    // left
    // glColor3f(0.0f, 0.0f, 0.05f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glVertex3f(offX + -0.05f, offY + -0.05f, 0.05f);
    glVertex3f(offX + -0.05f, offY + 0.05f, 0.05f);
    glVertex3f(offX + -0.05f, offY + 0.05f, -0.05f);
    glVertex3f(offX + -0.05f, offY + -0.05f, -0.05f);

    glEnd();

    glBegin(GL_QUADS);
    // bottom
    // glColor3f(0.05f, 0.0f, 0.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glVertex3f(offX + 0.05f, offY + -0.05f, 0.05f);
    glVertex3f(offX + -0.05f, offY + -0.05f, 0.05f);
    glVertex3f(offX + -0.05f, offY + -0.05f, -0.05f);
    glVertex3f(offX + 0.05f, offY + -0.05f, -0.05f);

    glEnd();

    glBegin(GL_QUADS);
    // back
    // glColor3f(0.0f, 0.05f, 0.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(offX + 0.05f, offY + 0.05f, -0.05f);
    glVertex3f(offX + 0.05f, offY + -0.05f, -0.05f);
    glVertex3f(offX + -0.05f, offY + -0.05f, -0.05f);
    glVertex3f(offX + -0.05f, offY + 0.05f, -0.05f);

    glEnd();
  }
};

#endif
