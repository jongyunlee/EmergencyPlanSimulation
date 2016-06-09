#include <iostream>
#include <assert.h>
#include "../../core/bitmap/bmploader.h"
#include "../../core/renderobj/RenderObject.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#define	imageSize 512

typedef void (*DisplayObjects)(bool);

class DMirrorSphere: public RenderObject {
private:
  GLuint cube_tex;
  GLfloat size;
  GLuint fb, depth_rb;
  DisplayObjects displayObjects;
  float *lpos;
public:
  DMirrorSphere(GLfloat size) {
    this->size = size;
    glGenTextures(1, &cube_tex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA8, imageSize, imageSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA8, imageSize, imageSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA8, imageSize, imageSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA8, imageSize, imageSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA8, imageSize, imageSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA8, imageSize, imageSize, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

    //
    // creating FBO and attach cube map texture
    //
    //-------------------------
    glGenFramebuffersEXT(1, &fb);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
    //Attach one of the faces of the Cubemap texture to this FBO
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_X, cube_tex, 0);
    //-------------------------
    glGenRenderbuffersEXT(1, &depth_rb);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, depth_rb);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT24, imageSize, imageSize);
    //-------------------------
    //Attach depth buffer to FBO
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, depth_rb);
    //-------------------------
    //Does the GPU support current FBO configuration?
    GLenum status;
    status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
    switch(status)
      {
      case GL_FRAMEBUFFER_COMPLETE_EXT:
	std::cout<<"good"<<std::endl; break;
      default:
	assert(false); break;
      }
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  }

  void renderToFBO(float d1, float d2, float d3,
		   float h1, float h2, float h3) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // test

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1, 0.6, 300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // glTranslatef(0.0, 0.0, -20.0);
    glLightfv(GL_LIGHT0, GL_POSITION, lpos); // test
    gluLookAt(0.0,0.0,0.0,
	      d1, d2, d3,
	      h1, h2, h3);

    displayObjects(true);
    glutSwapBuffers();
  }

  // dynamically update cubemap
  void update_cubemap()
  {
    // bind FBO to render to texture
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fb);
    glClearColor (0.8, 0.8, 0.8, 1.0);
    // render to +x face
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_X, cube_tex, 0);
    renderToFBO(1.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

    // render to -x face
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, cube_tex, 0);
    renderToFBO(-1.0, 0.0, 0.0,
		0.0, 1.0, 0.0);

    // render to +y face
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_Y, cube_tex, 0);
    renderToFBO(0.0, 1.0, 0.0,
		0.0, 0.0, 1.0);

    // render to -y face
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, cube_tex, 0);
    renderToFBO(0.0, -1.0, 0.0,
		0.0, 0.0, 1.0);

    // render to +z face
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, cube_tex, 0);
    renderToFBO(0.0, 0.0, 1.0,
		0.0, 1.0, 0.0);

    // render to -z face
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, cube_tex, 0);
    renderToFBO(0.0, 0.0, -1.0,
		0.0, 1.0, 0.0);

    // unbind FBO
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
  }

  void drawObject() {
    // cout << "DMirrorSphere drawObject()" << endl;

    glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);
    glEnable(GL_TEXTURE_CUBE_MAP);
    glTexGeni( GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
    glTexGeni( GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
    glTexGeni( GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP );
    glEnable( GL_TEXTURE_GEN_S );
    glEnable( GL_TEXTURE_GEN_T );
    glEnable( GL_TEXTURE_GEN_R );

    glutSolidSphere(0.6*size, 50, 50);

    glDisable( GL_TEXTURE_GEN_S );
    glDisable( GL_TEXTURE_GEN_T );
    glDisable( GL_TEXTURE_GEN_R );
    glDisable(GL_TEXTURE_CUBE_MAP);
  }

  GLuint getCubeTex() {
    return cube_tex;
  }

  void setDisplayObjects(float lpos[], DisplayObjects displayObjects) {
    this->lpos = lpos;
    this->displayObjects = displayObjects;
  }
};
