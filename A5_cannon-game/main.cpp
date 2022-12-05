// Andrew Broderick
// IGME309-02: DSA2
// Assignment 5: Cannon
// RIT Fall 2022

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif

#include <math.h>
#include <iostream>
#include <vector>
#include "main.h"
#include "Bullet.h"

using namespace std;

// Window's width and height
int width, height;

// num of verts in circles
int vertNum = 100;

// floor
float floor_y = -3.0f;

// cannon body
float cannon_r = 0.4f;
float cannon_x = 0.0f;
float cannon_y = floor_y;

// cannon launcher
float cannon_l = 1.0f;
float rotationSpeed = 1.57f; // rad/sec = 90 deg/sec
float cannonRotation = 0.0f;

// target circle generation region
float target_xMin = -3.5f;
float target_xMax = 3.5f;
float target_yMin = 0.0f;
float target_yMax = 4.0f;

// target circle
float targetInitialRadius = 0.2f;
float target_r = targetInitialRadius;
float target_xPos = 0.0f;
float target_yPos = 0.0f;
float targetColorIntensity = 0.5f;

// bullets
float bullet_r = 0.1f;
vector<Bullet> bullets = {};

// tracking the game time - millisecond 
unsigned int curTime = 0;
unsigned int preTime = 0;


void init(void)
{
	// initialize the size of the window
	width = 600;
	height = 600;
	
	// initialize the first target
	srand(static_cast <unsigned> (time(0)));
	resetTarget();
}


void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// floor
	glLineWidth(1);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-2.0, -3.0);
	glVertex2f(2.0, -3.0);
	glEnd();

	// target generation range
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(target_xMax, target_yMax);
	glVertex2f(target_xMin, target_yMax);
	glVertex2f(target_xMin, target_yMin);
	glVertex2f(target_xMax, target_yMin);
	glVertex2f(target_xMax, target_yMax);
	glEnd();

	// cannon body
	glColor3f(0.5, 0.5, 0.0);
	drawCircle(cannon_r, cannon_x, cannon_y, false);

	// cannon launcher
	glBegin(GL_LINES);
	glMatrixMode(GL_MODELVIEW);
	glVertex2f(cannon_x, cannon_y);
	glRotatef(cannonRotation, cannon_x, cannon_y, 0.0);
	glVertex2f(cannon_x, cannon_y + cannon_l);
	glEnd();

	// target circle
	glColor3f(targetColorIntensity, 0.0, 0.0);
	drawCircle(target_r, target_xPos, target_yPos, true);
	
	// TODO: bullets
	for (int i = 0; i < bullets.size(); i++) {
		//bullets[i].updatePosition();
	}

	glutSwapBuffers();
}


void update() // GAME LOOP
{
	// update elapsed time
	curTime = glutGet(GLUT_ELAPSED_TIME); // returns the number of milliseconds since glutInit() was called.
	float deltaTime = (float)(curTime - preTime) / 1000.0f; // frame-different time in seconds 

	// update bullet positions using their individual velocities
	//y += vel * deltaTime;
	
	// check for collisions. If target collided with any bullet, reset target
	// update bullet lifespan timers
	// check if any bullets' lifespans have elapsed, and if so, remove them

	for (int i = 0; i < bullets.size(); i++) {
		bullets[i].updatePosition(deltaTime);
	}

	preTime = curTime; // make the curTime become the preTime for the next frame
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	width = w;
	height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0);

	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {// esc
		exit(0);
	}
	if (key == 'a') {
		cannon_x -= 0.2f;
	}
	if (key == 'd') {
		cannon_x += 0.2f;
	}
	if (key == 'k') {
		cannonRotation -= rotationSpeed;
	}
	if (key == 'l') {
		cannonRotation += rotationSpeed;
	}
	if (key == 32) {// space bar
		shootBullet(cannonRotation);
	}
}


int main(int argc, char* argv[])
{
	init();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize((int)width, (int)height);

	// create the window with a title
	glutCreateWindow("Cannon");

	/* --- register callbacks with GLUT --- */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);

	//start the glut main loop
	glutMainLoop();

	return 0;
}

void drawCircle(float radius, float x_pos, float y_pos, bool filled) {
	if (filled) {
		glBegin(GL_POLYGON);
	}
	else {
		glBegin(GL_LINE_LOOP);
	}
	for (int i = 0; i < vertNum; i++) {
		float degree = (float)i / vertNum * 2.0f * 3.14f;
		float x = radius * cos(degree) + x_pos;
		float y = radius * sin(degree) + y_pos;
		glVertex2f(x, y);
	}
	glEnd();
}


void resetTarget() {
	target_xPos = (rand() % int((target_xMax - target_xMin) * 100)) / 100.0f + target_xMin;
	target_yPos = (rand() % int((target_yMax - target_yMin) * 100)) / 100.0f + target_yMin;
}


void shootBullet(float cannonRotation) {

}