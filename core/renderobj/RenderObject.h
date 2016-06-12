#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include "../angel/mat.h"
#include "../angel/vec.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#include <GL/glew.h>
#endif

#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

using namespace std;

class RenderObject {
 private:
  int totalVerticesCount;
  int totalIndicesCount;

  float* coordinates;
  int* indices;
  float* normals;

  int scale;

  GLuint coordBuffer;
  GLuint indicesBuffer;
  GLuint normalBuffer;

  unsigned char renderingMode;
 protected:
  mat4 m;
  bool trackballEnable;

 public:
  RenderObject() {
    trackballEnable = false;
  }

  RenderObject(string meshPath) {
    ifstream in;
    string off;
    int dummy;
    scale = 20;

    in.open(meshPath);
    in >> off;
    if (off.compare("OFF") != 0)
      throw "The start of mesh file should be 'OFF'";

    in >> totalVerticesCount;
    in >> totalIndicesCount;
    in >> dummy;

    // init coordinates
    coordinates = new float[totalVerticesCount * 3];
    for (int i=0; i<totalVerticesCount*3; i++) {
      float coord = 0.0;
      in >> coord;
      coordinates[i] = coord * scale;
    }

    // init indices
    indices = new int[totalIndicesCount * 3];
    int count = 0;
    while (count < totalIndicesCount*3) {
      float angle;
      int v1, v2, v3;
      in >> angle;
      in >> v1;
      in >> v2;
      in >> v3;
      indices[count] = v1;
      count++;
      indices[count] = v2;
      count++;
      indices[count] = v3;
      count++;
    }
    normals = new float[totalVerticesCount*3];
    setRenderingMode('s');
  }

  void enableTrackball(bool enable) {
    trackballEnable = enable;
  }

  void createBuffers() {
    glGenBuffers(1, &coordBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &indicesBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
    glBufferData(GL_ARRAY_BUFFER,
    		 totalVerticesCount * 3 * sizeof(*coordinates),
    		 coordinates,
    		 GL_STATIC_DRAW);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
    		 totalIndicesCount * 3 * sizeof(*indices),
    		 indices,
    		 GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER,
    		 totalVerticesCount * 3 * sizeof(*normals),
    		 normals,
    		 GL_STATIC_DRAW);
  }

  vec3 getVectorByIndex(int index) {
    return vec3(coordinates[index*3], coordinates[index*3+1], coordinates[index*3+2]);
  }

  vec3 getNormalByIndex(int index) {
    return vec3(normals[index*3], normals[index*3+1], normals[index*3+2]);
  }

  void render(GLfloat angle, float axis[3], vec3 panning, float zooming) {
    if (renderingMode == 'w') {
      glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
    } else {
      glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    if (trackballEnable) {
      if (length(panning) != 0) {
	mat4 p = Translate(panning);
	m = m*p;
      }
      if (angle != 0) {
	mat4 r = RotateByAxis(angle, vec3(), vec3(axis[0], axis[1], axis[2]));
	m = m*r;
      }
      if (zooming != 0) {
	mat4 z = Scale(1 + zooming, 1 + zooming, 1 + zooming);
	m = m*z;
      }
    }
    glMultMatrixf(m);
    drawObject();
    glPopMatrix();
  }

  void render() {
    if (renderingMode == 'w') {
      glPolygonMode ( GL_FRONT_AND_BACK, GL_LINE );
    } else {
      glPolygonMode ( GL_FRONT_AND_BACK, GL_FILL );
    }

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMultMatrixf(m);
    drawObject();
    glPopMatrix();
  }

  void translate(float x, float y, float z) {
    mat4 p = Translate(vec3(x, y, z));
    m = m * p;
  }

  void zoom(float zooming) {
    mat4 z = Scale(1 + zooming, 1 + zooming, 1 + zooming);
    m = m*z;
  }

  void rotateByAxis(GLfloat angle, float axis[3]) {
    if (angle != 0) {
      mat4 r = RotateByAxis(angle, vec3(), vec3(axis[0], axis[1], axis[2]));
      m = m*r;
    }
  }

  virtual void drawObject() {
    /* glutSolidCube(1); */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
    glVertexPointer(3, GL_FLOAT, 0, 0);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glNormalPointer(GL_FLOAT, 0, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBuffer);
    glDrawElements(GL_TRIANGLES, totalIndicesCount * 3, GL_UNSIGNED_INT, 0);

    glDisableClientState(GL_VERTEX_ARRAY);
  }

  void showCoordAndIndices() {
    cout << coordinates[0] << " " << coordinates[1] << " " << coordinates[2] << endl;
    cout << indices[0] << " " << indices[1] << " " << indices[2] << endl;

    cout << coordinates[totalVerticesCount*3-3] << " " << coordinates[totalVerticesCount*3-2] << " " << coordinates[totalVerticesCount*3-1] << endl;

    cout << indices[totalIndicesCount*3-3] << " " << indices[totalIndicesCount*3-2] << " " << indices[totalIndicesCount*3-1] << endl;

    cout << normals[0] << " " << normals[1] << " " << normals[2] << endl;
    cout << normals[totalIndicesCount*3-3] << " " << normals[totalIndicesCount*3-2] << " " << normals[totalIndicesCount*3-1] << endl;
  }

  void setRenderingMode(char m) {
    renderingMode = m;
    if (renderingMode == 'f') {
      for (int i=0; i<totalIndicesCount*3; i+=3) {
	int index1 = indices[i];
	int index2 = indices[i+1];
	int index3 = indices[i+2];
	vec3 vector1 = getVectorByIndex(index1);
	vec3 vector2 = getVectorByIndex(index2);
	vec3 vector3 = getVectorByIndex(index3);
	vec3 edge1 = vector1 - vector3;
	vec3 edge2 = vector2 - vector3;
	vec3 normal = normalize(cross(edge1, edge2));
	normals[index1*3] = normal[0];
	normals[index1*3+1] = normal[1];
	normals[index1*3+2] = normal[2];
	normals[index2*3] = normal[0];
	normals[index2*3+1] = normal[1];
	normals[index2*3+2] = normal[2];
	normals[index3*3] = normal[0];
	normals[index3*3+1] = normal[1];
	normals[index3*3+2] = normal[2];
      }
    } else {
      for (int i=0; i<totalIndicesCount*3; i+=3) {
	int index1 = indices[i];
	int index2 = indices[i+1];
	int index3 = indices[i+2];
	vec3 vector1 = getVectorByIndex(index1);
	vec3 vector2 = getVectorByIndex(index2);
	vec3 vector3 = getVectorByIndex(index3);
	vec3 edge1 = vector1 - vector3;
	vec3 edge2 = vector2 - vector3;
	vec3 normal = normalize(cross(edge1, edge2));
	normals[index1*3] += normal[0];
	normals[index1*3+1] += normal[1];
	normals[index1*3+2] += normal[2];
	normals[index2*3] += normal[0];
	normals[index2*3+1] += normal[1];
	normals[index2*3+2] += normal[2];
	normals[index3*3] += normal[0];
	normals[index3*3+1] += normal[1];
	normals[index3*3+2] += normal[2];
      }
      for (int i=0; i<totalVerticesCount; i++) {
	vec3 normal = getNormalByIndex(i);
	vec3 finalNormal = normalize(normal);
	normals[i*3] = finalNormal[0];
	normals[i*3+1] = finalNormal[1];
	normals[i*3+2] = finalNormal[2];
      }
    }
    createBuffers();
  }
};

#endif
