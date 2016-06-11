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

#ifndef GRID_H
#define GRID_H

class Grid: public RenderObject {
private:
  GridConfigs *gridConfigs;
public:
  Grid(GridConfigs *gridConfigs) {
    this->gridConfigs = gridConfigs;
  }

  void drawObject() {
    float xmin=-1.0, xmax=1.0, dx=0.1, x;
    float ymin=-1.0, ymax=1.0, dy=0.1, y;
    glPushMatrix();
    glColor3f(1.0f,1.0f,1.0f);
    glLineWidth((GLfloat)0.1);
    glBegin(GL_LINES);

    for(x=xmin; x<=xmax+dx; x+=dx)
      {
	for(y=ymin; y<=ymax+dy; y+=dy)
	  {
	    glVertex3f(x, ymin, 0.01);
	    glVertex3f(x, ymax, 0.01);

	    glVertex3f(xmin, y, 0.01);
	    glVertex3f(xmax, y, 0.01);
	  }
      }

    glEnd();
    glPopMatrix();
  }
};

#endif
