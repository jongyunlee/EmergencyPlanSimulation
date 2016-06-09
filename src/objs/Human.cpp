#include <iostream>
#include "../../core/bitmap/bmploader.h"
#include "../../core/renderobj/Cube.h"
#include "Head.cpp"
#include "Body.cpp"
#include "Arm.cpp"
#include "Leg.cpp"
using namespace std;

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class Human {
private:
  int imageWidth;
  int imageHeight;
  uchar4 *dst;
  Head *head;
  Body *body;
  Arm *larm;
  Arm *rarm;
  Leg *lleg;
  Leg *rleg;
public:
  Human(GLfloat size, string skin) {
    LoadBMPFile(&dst, &imageWidth, &imageHeight, skin.c_str()); // this is how to load image
      head = new Head(size, imageWidth, imageHeight, dst);
      head->zoom(-0.8);
      head->translate(0.0, 0.5, 0.0);

      body = new Body(size, imageWidth, imageHeight, dst);
      body->zoom(-0.8);

      larm = new Arm(size, imageWidth, imageHeight, dst, true);
      larm->zoom(-0.8);
      larm->translate(-0.3, 0.0, 0.0);

      rarm = new Arm(size, imageWidth, imageHeight, dst, false);
      rarm->zoom(-0.8);
      rarm->translate(0.3, 0.0, 0.0);
      // rarm->enableTrackball(true);

      lleg = new Leg(size, imageWidth, imageHeight, dst, true);
      lleg->zoom(-0.8);
      lleg->translate(-0.1, -0.6, 0.0);

      rleg = new Leg(size, imageWidth, imageHeight, dst, false);
      rleg->zoom(-0.8);
      rleg->translate(0.1, -0.6, 0.0);
  }

  void render(GLfloat angle, float axis[3], vec3 panning, float zooming) {
    head->render(angle, axis, panning, zooming);
    body->render(angle, axis, panning, zooming);
    larm->render(angle, axis, panning, zooming);
    rarm->render(angle, axis, panning, zooming);
    lleg->render(angle, axis, panning, zooming);
    rleg->render(angle, axis, panning, zooming);
  }

  void translate(float x, float y, float z) {
    head->translate(x, y, z);
    body->translate(x, y, z);
    larm->translate(x, y, z);
    rarm->translate(x, y, z);
    lleg->translate(x, y, z);
    rleg->translate(x, y, z);
  }

  void zoom(float zooming) {
    head->zoom(zooming);
    body->zoom(zooming);
    larm->zoom(zooming);
    rarm->zoom(zooming);
    lleg->zoom(zooming);
    rleg->zoom(zooming);
  }

  void rotateByAxis(GLfloat angle, float axis[3]) {
    head->rotateByAxis(angle, axis);
    body->rotateByAxis(angle, axis);
    larm->rotateByAxis(angle, axis);
    rarm->rotateByAxis(angle, axis);
    lleg->rotateByAxis(angle, axis);
    rleg->rotateByAxis(angle, axis);
  }
};
