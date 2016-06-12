#include <iostream>
#include "../../core/bitmap/bmploader.h"
#include "../../core/renderobj/Cube.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class BgBox: public Cube {
private:
  int imageWidth;
  int imageHeight;
  GLuint mirror_texs[6];

  // array to store synthetic cubemap raw image
  GLubyte image1[4][4][4];
  GLubyte image2[4][4][4];
  GLubyte image3[4][4][4];
  GLubyte image4[4][4][4];
  GLubyte image5[4][4][4];
  GLubyte image6[4][4][4];

public:
  // create synthetic data for static cubemap
  void makeSyntheticImages(void)
  {
    int i, j, c;

    for (i = 0; i < 4; i++) {
      for (j = 0; j < 4; j++) {
	c = ((((i&0x1)==0)^((j&0x1))==0))*255;
	image1[i][j][0] = (GLubyte) c;
	image1[i][j][1] = (GLubyte) c;
	image1[i][j][2] = (GLubyte) c;
	image1[i][j][3] = (GLubyte) 255;

	image2[i][j][0] = (GLubyte) c;
	image2[i][j][1] = (GLubyte) c;
	image2[i][j][2] = (GLubyte) 0;
	image2[i][j][3] = (GLubyte) 255;

	image3[i][j][0] = (GLubyte) c;
	image3[i][j][1] = (GLubyte) 0;
	image3[i][j][2] = (GLubyte) c;
	image3[i][j][3] = (GLubyte) 255;

	image4[i][j][0] = (GLubyte) 0;
	image4[i][j][1] = (GLubyte) c;
	image4[i][j][2] = (GLubyte) c;
	image4[i][j][3] = (GLubyte) 255;

	image5[i][j][0] = (GLubyte) 255;
	image5[i][j][1] = (GLubyte) c;
	image5[i][j][2] = (GLubyte) c;
	image5[i][j][3] = (GLubyte) 255;

	image6[i][j][0] = (GLubyte) c;
	image6[i][j][1] = (GLubyte) c;
	image6[i][j][2] = (GLubyte) 255;
	image6[i][j][3] = (GLubyte) 255;
      }
    }
  }

  uchar4 *d;
  BgBox(GLfloat size) : Cube(size) {
    makeSyntheticImages();
    // translate(0.0, 0.0, 2.0);
    this->imageWidth = 4;
    this->imageHeight = 4;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(6, mirror_texs);
    glBindTexture(GL_TEXTURE_2D, mirror_texs[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, mirror_texs[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, mirror_texs[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, mirror_texs[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, mirror_texs[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, mirror_texs[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  // BgBox(GLfloat size, GLuint []) : Cube(size) {
  //   translate(0.0, 0.0, -2);
  //   glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //   glGenTextures(6, mirror_texs);
  //   for (int i=0; i<6; i++) {
  //     glBindTexture(GL_TEXTURE_2D, mirror_texs[0]);
  //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  //     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  //     // uchar4 *d;
  //     LoadBMPFile(&d, &imageWidth, &imageHeight, images[i].c_str()); // this is how to load image
  //     glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
  //     dst[i] = d;
  //   }
  // }

  void drawObject() {
    glEnable(GL_TEXTURE_2D);
    drawBox(size);
    glDisable(GL_TEXTURE_2D);
  }

  void drawBox(GLfloat s) {
    GLfloat p = s/2;
    // Front Face
    glBindTexture(GL_TEXTURE_2D, mirror_texs[0]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-p, -p,  2*p);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( p, -p,  2*p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( p,  p,  2*p);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-p,  p,  2*p);  // Top Left Of The Texture and Quad
    glEnd();
    // Back Face
    glBindTexture(GL_TEXTURE_2D, mirror_texs[1]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image6);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-p, -p, -2*p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-p,  p, -2*p);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( p,  p, -2*p);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( p, -p, -2*p);  // Bottom Left Of The Texture and Quad
    glEnd();
    // Top Face
    glBindTexture(GL_TEXTURE_2D, mirror_texs[2]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-p,  p, -2*p);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-p,  p,  2*p);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( p,  p,  2*p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( p,  p, -2*p);  // Top Right Of The Texture and Quad
    glEnd();
    // Bottom Face
    glBindTexture(GL_TEXTURE_2D, mirror_texs[3]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image5);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-p, -p, -2*p);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( p, -p, -2*p);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( p, -p,  2*p);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-p, -p,  2*p);  // Bottom Right Of The Texture and Quad
    glEnd();
    // Right face
    glBindTexture(GL_TEXTURE_2D, mirror_texs[4]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f( p, -p, -2*p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( p,  p, -2*p);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( p,  p,  2*p);  // Top Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( p, -p,  2*p);  // Bottom Left Of The Texture and Quad
    glEnd();
    // Left Face
    glBindTexture(GL_TEXTURE_2D, mirror_texs[5]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, image4);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-p, -p, -2*p);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-p, -p,  2*p);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-p,  p,  2*p);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-p,  p, -2*p);  // Top Left Of The Texture and Quad
    glEnd();
  }
};
