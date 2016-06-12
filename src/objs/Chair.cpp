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
		���ڰ� ���� ��� �߽� x,y,z��ǥ, ���� ���� ����, ���� ���� ����, ���� ����, �ٸ� ����, �β�
		x : x��ǥ
		y : y��ǥ
		z : z��ǥ
		xWidth : ���� ���α���
		zWidth : ���� ���α���
		back : ����� ����
		reg : ���� �ٸ� ����
		thick : ���� �β�
		*/

		glColor3f(1,1,1);  // ���� ����
	
		glBegin(GL_QUADS);	// �׸��� ����. �ٶ󺸴� ���� ���� �׷���. �Ʒ�->��->��->��->������->���� (���� �ٶ󺸴�) ������ �׷���.
		
			glNormal3f(0.0f, 1.0f, 0.0f);   // �Ʒ� ����
				// ���� �ٸ� �ٴ� * 4��
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

				// �ɴ� �κ� �Ʒ���
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);

			glNormal3f(0.0f, -1.0f, 0.0f);   // �� ����
				// �ɴ� �κ� ����
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);

				// ����� ����
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2);

			glNormal3f(0.0f, 0.0f, 1.0f);   // �� ����
				// ���� �ٸ� ���� * 4��
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

				// �ɴ� �κ� ����
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);

				// ����� ����
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2-thick);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2-thick);

			glNormal3f(0.0f, 0.0f, -1.0f);   // �� ����
				// ���� �ٸ� �޸� * 4��
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

				// ����� �޸�(�ɴ� �κ� �޸� ����)
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick+back, z+zWidth/2);

			glNormal3f(-1.0f, 0.0f, 0.0f);   // ������
				// ���� �ٸ� ������ �� * 4��
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

				// �ɴ� �κ� ������ ��(����� �Ʒ� ����)
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick, z-zWidth/2);

				// ����� ������ ��
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2-thick);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x+xWidth/2, y+reg+thick, z+zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x+xWidth/2, y+reg+thick+back, z+zWidth/2-thick);

			glNormal3f(1.0f, 0.0f, 0.0f);   // ����
				// ���� �ٸ� ���� �� * 4��
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

				// �ɴ� �κ� ���� ��(����� �Ʒ� ����)
				glTexCoord2f(0.0, 0.0);
				glVertex3f(x-xWidth/2, y+reg, z-zWidth/2);
				glTexCoord2f(0.5, 0.0);
				glVertex3f(x-xWidth/2, y+reg+thick, z-zWidth/2);
				glTexCoord2f(0.5, 0.5);
				glVertex3f(x-xWidth/2, y+reg+thick, z+zWidth/2);
				glTexCoord2f(0.0, 0.5);
				glVertex3f(x-xWidth/2, y+reg, z+zWidth/2);
			
				// ����� ���� ��
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