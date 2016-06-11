#include <iostream>
#include <list>
#include "../utils/GridConfigs.cpp"
#include "../../core/bitmap/bmploader.h"
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifndef MAP_H
#define MAP_H

struct Position {
  float x;
  float y;
};

class Map {
private:
  GridConfigs *gridConfigs;
  int map[20][20];
  int imageWidth;
  int imageHeight;
  uchar4 *dst;
  GLuint color_tex;
  Position paths[10];
  int pathCount;
public:

  Map(GridConfigs *gridConfigs) {
    this->gridConfigs = gridConfigs;

    LoadBMPFile(&dst, &imageWidth, &imageHeight, "images/wall.bmp"); // this is how to load image
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    for (int i=0; i<20; i++) {
      for (int j=0; j<20; j++) {
	map[i][j] = 0;
      }
    }
    pathCount = 0;
  }

  void render() {
    glPushMatrix();
    for (int i=0; i<20; i++) {
      for (int j=0; j<20; j++){
    	if (map[i][j] == 1) {
	  drawCube((i-10)*0.1 + 0.05, (j-10)*0.1 + 0.05, 0.1f);
	}
      }
    }
    for (int i=0; i< pathCount-1; i++) {
      glPushMatrix();
      glColor3f(1.0f,0.0f,0.0f);
      glLineWidth((GLfloat)5.0);
      glBegin(GL_LINES);
      glVertex3f(paths[i].x, paths[i].y, 0.02);
      glVertex3f(paths[i+1].x, paths[i+1].y, 0.02);
      glEnd();
      glPopMatrix();
    }
    drawFloor();
    glPopMatrix();
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

  void addWallWithoutToggle() {
    int p[2];
    gridConfigs->getMapBlockIndex(p);
    map[p[0]][p[1]] = 1;
  }

  void printMap() {
    for (int i=0; i<20; i++) {
      for (int j=0; j<20; j++) {
	cout << map[j][i] << " ";
      }
      cout << endl;
    }
    cout << endl;
  }

  void drawCube(float offX, float offY, float height) {
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    glColor3f(1.0f,1.0f,1.0f);

    glBindTexture(GL_TEXTURE_2D, color_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    glBegin(GL_QUADS);
    // top
    // glColor3f(1.0f, 0.0f, 0.0f);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(offX + -0.05f, offY + 0.05f, height);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(offX + 0.05f, offY +0.05f, height);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(offX + 0.05f, offY + 0.05f, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(offX + -0.05f, offY + 0.05f, 0);

    glEnd();

    glBegin(GL_QUADS);
    // front
    // glColor3f(0.0f, 1.0f, 0.0f);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(offX + 0.05f, offY + -0.05f, height);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(offX + 0.05f, offY + 0.05f, height);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(offX + -0.05f, offY + 0.05f, height);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(offX + -0.05f, offY + -0.05f, height);

    glEnd();

    glBegin(GL_QUADS);
    // right
    // glColor3f(0.0f, 0.0f, 1.0f);
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(offX + 0.05f, offY + 0.05f, 0);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(offX + 0.05f, offY + 0.05f, height);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(offX + 0.05f, offY + -0.05f, height);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(offX + 0.05f, offY + -0.05f, 0);

    glEnd();

    glBegin(GL_QUADS);
    // left
    // glColor3f(0.0f, 0.0f, 0.05f);
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(offX + -0.05f, offY + -0.05f, height);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(offX + -0.05f, offY + 0.05f, height);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(offX + -0.05f, offY + 0.05f, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(offX + -0.05f, offY + -0.05f, 0);

    glEnd();

    glBegin(GL_QUADS);
    // bottom
    // glColor3f(0.05f, 0.0f, 0.0f);
    glNormal3f(0.0f, -1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(offX + 0.05f, offY + -0.05f, height);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(offX + -0.05f, offY + -0.05f, height);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(offX + -0.05f, offY + -0.05f, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(offX + 0.05f, offY + -0.05f, 0);

    glEnd();

    glBegin(GL_QUADS);
    // back
    // glColor3f(0.0f, 0.05f, 0.0f);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(offX + 0.05f, offY + 0.05f, 0);
    glVertex3f(offX + 0.05f, offY + -0.05f, 0);
    glVertex3f(offX + -0.05f, offY + -0.05f, 0);
    glVertex3f(offX + -0.05f, offY + 0.05f, 0);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
  }

  void drawFloor() {
    glPushMatrix();
    glColor3f(0.2f,0.5f,0.8f);
    glBegin(GL_QUADS);
    glVertex3f(-1, -1, 0.0);
    glVertex3f(-1, 1, 0.0);
    glVertex3f(1, 1, 0.0);
    glVertex3f(1, -1, 0.0);
    glEnd();
    glPopMatrix();
  }

  void addPathPosition() {
    float p[2];
    gridConfigs->get3dCursorMovePosition(p);
    Position position;
    position.x = p[0];
    position.y = p[1];
    paths[pathCount] = position;
    pathCount++;
    pathCount %= 10;
    cout << "pc : " << pathCount << endl;
    // pathPositions.push_back(position);
  }

  bool hasWalkPosition(int i) {
    if (pathCount > i) return true;
    return false;
  }

  float getXPosition(int i) {
    return paths[i].x;
  }

  float getYPosition(int i) {
    return paths[i].y;
  }
};

#endif
