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

using namespace std;

// Window's width and height
int width, height;

// global parameters defining the circle
int vertNum = 100; // total number of vertices for the circle
float x = 0.0f, y = 1.5f; // center postion of the circle
float r = 0.2f; // circle's radius
float vel = -2.2f; // velocity of the ball 

// define the y value of the floor
float floor_y = -3.0f;
// define they y value of the ceiling
float ceiling_y = 3.0f;

// tracking the game time - millisecond 
unsigned int curTime = 0;
unsigned int preTime = 0;


void init(void)
{
	// initialize the size of the window
	width = 600;
	height = 600;
}

void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



	// draw a circle as the ball
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < vertNum; ++i) {
		float t = (float)i / vertNum * 2.0f * 3.14f;
		glVertex2f(x + r * cos(t), y + r * sin(t));
	}
	glEnd();

	// use GL_LINES to draw the floor 
	glLineWidth(3);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex2f(-2.0f, floor_y);
	glVertex2f(2.0f, floor_y);
	glEnd();
	glLineWidth(1);

	// use GL_LINES to draw the ceiling
	glLineWidth(3);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-2.0f, ceiling_y);
	glVertex2f(2.0f, ceiling_y);
	glEnd();
	glLineWidth(1);


	glutSwapBuffers();
}


void update()
{
	curTime = glutGet(GLUT_ELAPSED_TIME); // returns the number of milliseconds since glutInit() was called.
	float deltaTime = (float)(curTime - preTime) / 1000.0f; // frame-different time in seconds 

	// check if the ball hits the floor 
	if (y - r < floor_y) {
		vel = abs(vel);
	}

	//check if the ball hits the ceiling
	else if (y + r > ceiling_y) {
		vel = -abs(vel);
	}

	y += vel * deltaTime;

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
	if (key == 27)
		exit(0);
}


int main(int argc, char* argv[])
{
	init();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowSize((int)width, (int)height);

	// create the window with a title
	glutCreateWindow("Ball Bounces at Constant Speed");

	/* --- register callbacks with GLUT --- */
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(update);

	//start the glut main loop
	glutMainLoop();

	return 0;
}