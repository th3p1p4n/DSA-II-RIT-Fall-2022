// Course: IGME 309-02
// Student Name: Andrew Broderick
// Assignment Number: 03

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "PolyObject.h"


PolyObject::PolyObject()
{

}

PolyObject::~PolyObject()
{
}

void PolyObject::addVertex(vec2 p_vert)
{
	vertices.push_back(p_vert);
}

void PolyObject::setColor(vec3 p_color)
{
	color = p_color;
}

unsigned int PolyObject::getVertNum()
{
	return vertices.size();
}

void PolyObject::draw()
{
	glColor3f(color[0],color[1],color[2]);

	if (getVertNum() == 1) {
		glBegin(GL_POINT);
		glVertex2f(vertices[0][0], vertices[0][1]);
	}
	else if (getVertNum() == 2) {
		glBegin(GL_LINE);
		glVertex2f(vertices[0][0], vertices[0][1]);
		glVertex2f(vertices[1][0], vertices[1][1]);
	}
	else {
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < getVertNum(); i++) {
			glVertex2f(vertices[i][0], vertices[i][1]);
		}
	}
	glEnd();
}

void PolyObject::draw(vec2 p_mousePos)
{

}
