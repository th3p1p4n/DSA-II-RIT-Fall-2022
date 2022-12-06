#pragma once
#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif
#include <math.h>

class Bullet {
	float angle;
	float speed;
	float xPos;
	float yPos;

public:
	float life;

	Bullet(float _angle, float _xPos, float _yPos) {
		angle = _angle;
		xPos = _xPos;
		yPos = _yPos;
		speed = 3.0;
		life = 0.0;
	}

	void updatePositionAndLifespan(float deltaTime) {
		xPos += speed * cos(angle) * deltaTime;
		yPos += speed * sin(angle) * deltaTime;

		life += deltaTime;
	}

	void draw(float radius, int vertNum) {
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		for (int i = 0; i < vertNum; i++) {
			float degree = (float)i / vertNum * 2.0f * 3.14f;
			float x = radius * cos(degree) + xPos;
			float y = radius * sin(degree) + yPos;
			glVertex2f(x, y);
		}
		glEnd();
	}
};

