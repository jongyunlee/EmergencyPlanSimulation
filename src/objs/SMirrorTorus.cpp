#include <iostream>
#include "../../core/bitmap/bmploader.h"
#include "../../core/renderobj/RenderObject.h"


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

class SMirrorTorus: public RenderObject {
private:
  GLuint cube_tex;
  int imageWidth;
  int imageHeight;
  uchar4 *dst;
  int size;

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

  SMirrorTorus(GLfloat size, string images[]) {
    this->size = size;

    glGenTextures(1, &cube_tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    for (int i=0; i<6; i++) {
      LoadBMPFile(&dst, &imageWidth, &imageHeight, images[i].c_str()); // this is how to load image
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    }

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, imageWidth, imageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, imageWidth, imageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, imageWidth, imageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, imageWidth, imageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, imageWidth, imageWidth, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);
  }

  SMirrorTorus(GLfloat size) {
    this->size = size;
    makeSyntheticImages();
    imageWidth = 4;
    imageHeight = 4;
    glGenTextures(1, &cube_tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image1);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image2);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image3);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image4);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image5);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, 4, 4, 0, GL_RGBA, GL_UNSIGNED_BYTE, image6);
  }

  void drawObject() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
    glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
    glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
    glEnable( GL_TEXTURE_GEN_S );
    glEnable( GL_TEXTURE_GEN_T );
    glEnable( GL_TEXTURE_GEN_R );
    glutSolidTorus(0.2 * size, 0.5 * size, 50, 50);
    glDisable( GL_TEXTURE_GEN_S );
    glDisable( GL_TEXTURE_GEN_T );
    glDisable( GL_TEXTURE_GEN_R );
    glDisable(GL_TEXTURE_CUBE_MAP);
  }


  GLuint getCubeTex() {
    return cube_tex;
  }

  int getImageWidth() {
    return imageWidth;
  }

  int getImageHeight() {
    return imageHeight;
  }
};
