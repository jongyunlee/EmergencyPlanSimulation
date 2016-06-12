#include <stdio.h>
#include <GL\glew.h>
#include <GL/glut.h>

#include "../../core/bitmap/bmploader.h"

class Chair {
	private:
	GLfloat x; GLfloat y; GLfloat z; 
	GLfloat xWidth; GLfloat zWidth; GLfloat back; GLfloat reg; GLfloat thick;
	uchar4 *dst;
	GLuint color_tex;
	GLuint cube_tex;
	int imageWidth;
	int imageHeight;

public:
	Chair(GLfloat x, GLfloat y, GLfloat z, 
               GLfloat xWidth, GLfloat zWidth, GLfloat back, GLfloat reg, GLfloat thick) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->xWidth = xWidth;
		this->zWidth = zWidth;
		this->back = back;
		this->reg = reg;
		this->thick = thick;

		LoadBMPFile(&dst, &imageWidth, &imageHeight, "images/woodtexture.bmp"); // this is how to load image
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glGenTextures(1, &color_tex);
		glBindTexture(GL_TEXTURE_2D, color_tex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, dst);

		glGenTextures(1, &cube_tex);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cube_tex);
	}

//GLfloat x, GLfloat y, GLfloat z, 
//               GLfloat xWidth, GLfloat zWidth, GLfloat back, GLfloat reg, GLfloat thick

	void render()
	{
		/* function createChair()
		의자가 놓일 평면 중심 x,y,z좌표, 의자 가로 길이, 의자 세로 길이, 의자 높이, 다리 길이, 두께
		x : x좌표
		y : y좌표
		z : z좌표
		xWidth : 의자 가로길이
		zWidth : 의자 세로길이
		back : 등받이 높이
		reg : 의자 다리 길이
		thick : 의자 두께
		*/

		glColor3f(1,1,1);  // 색깔 지정
	
		glBegin(GL_QUADS);	// 그리기 시작. 바라보는 면을 따라 그렸음. 아래->위->앞->뒤->오른쪽->왼쪽 (에서 바라보는) 순으로 그렸음.
		
			glNormal3f(0.0f, 1.0f, 0.0f);   // 아래 방향
				// 의자 다리 바닥 * 4개
				glVertex3f(x-xWidth/2, y, z-zWidth/2);
				glVertex3f(x-xWidth/2, y, z-zWidth/2+thick);
				glVertex3f(x-xWidth/2+thick, y, z-zWidth/2+thick);
				glVertex3f(x-xWidth/2+thick, y, z-zWidth/2);

				glVertex3f(x-xWidth/2, y, z+zWidth/2);
				glVertex3f(x-xWidth/2, y, z+zWidth/2-thick);
				glVertex3f(x-xWidth/2+thick, y, z+zWidth/2-thick);
				glVertex3f(x-xWidth/2+thick, y, z+zWidth/2);

				glVertex3f(x+xWidth/2, y, z+zWidth/2);
				glVertex3f(x+xWidth/2, y, z+zWidth/2-thick);
				glVertex3f(x+xWidth/2-thick, y, z+zWidth/2-thick);
				glVertex3f(x+xWidth/2-thick, y, z+zWidth/2);

				glVertex3f(x+xWidth/2, y, z-zWidth/2);
				glVertex3f(x+xWidth/2, y, z-zWidth/2+thick);
				glVertex3f(x+xWidth/2-thick, y, z-zWidth/2+thick);
				glVertex3f(x+xWidth/2-thick, y, z-zWidth/2);

				// 앉는 부분 아랫쪽
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);

			glNormal3f(0.0f, -1.0f, 0.0f);   // 위 방향
				// 앉는 부분 위쪽
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);

				// 등받이 위쪽
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2);

			glNormal3f(0.0f, 0.0f, 1.0f);   // 앞 방향
				// 의자 다리 정면 * 4개
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2+thick, y, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2+thick, y+reg, z-zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2-thick, y, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2-thick, y+reg, z-zWidth/2);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2-thick, y, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2-thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2-thick, y+reg, z+zWidth/2-thick);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2+thick, y, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2+thick, y+reg, z+zWidth/2-thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2-thick);

				// 앉는 부분 정면
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);

				// 등받이 정면
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2-thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2-thick);

			glNormal3f(0.0f, 0.0f, -1.0f);   // 뒷 방향
				// 의자 다리 뒷면 * 4개
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y, z-zWidth/2+thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2+thick, y, z-zWidth/2+thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2+thick, y+reg, z-zWidth/2+thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2+thick);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2-thick, y, z-zWidth/2+thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y, z-zWidth/2+thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2+thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2-thick, y+reg, z-zWidth/2+thick);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2-thick, y, z+zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2-thick, y+reg, z+zWidth/2);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y, z+zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2+thick, y, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2+thick, y+reg, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);

				// 등받이 뒷면(앉는 부분 뒷면 포함)
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2);

			glNormal3f(-1.0f, 0.0f, 0.0f);   // 오른쪽
				// 의자 다리 오른쪽 면 * 4개
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2+thick, y, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2+thick, y, z-zWidth/2+thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2+thick, y+reg, z-zWidth/2+thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2+thick, y+reg, z-zWidth/2);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2, y, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y, z-zWidth/2+thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2+thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2, y, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2-thick);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2+thick, y, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2+thick, y, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2+thick, y+reg, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2+thick, y+reg, z+zWidth/2-thick);

				// 앉는 부분 오른쪽 면(등받이 아래 포함)
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);

				// 등받이 오른쪽 면
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2-thick);

			glNormal3f(1.0f, 0.0f, 0.0f);   // 왼쪽
				// 의자 다리 왼쪽 면 * 4개
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y, z-zWidth/2+thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2, y, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2+thick);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2-thick, y, z-zWidth/2+thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2-thick, y, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2-thick, y+reg, z-zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2-thick, y+reg, z-zWidth/2+thick);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2-thick, y, z+zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2-thick, y, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2-thick, y+reg, z+zWidth/2-thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2-thick, y+reg, z+zWidth/2);

				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y, z+zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2, y, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2-thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);

				// 앉는 부분 왼쪽 면(등받이 아래 포함)
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);
			
				// 등받이 왼쪽 면
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2);
			
		glEnd();
	}
};