#include <GL/glew.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

// include the gl mathematic library 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/constants.hpp>


#include "Camera.h"
#include "Text.h"
#include "MyMesh.h"

#include <iostream>
using namespace std;
using namespace glm;

int g_winWidth = 1024;
int g_winHeight = 512;

// global parameters for defining the light and shading effects
GLfloat light0_pos[] = { 0.0f, 5.0f, 5.0f, 0.0f };
GLfloat light0_Amb[] = { 0.4f, 0.3f, 0.3f, 1.0f };
GLfloat light0_Diff[] = { 0.8f, 0.8f, 0.7f, 1.0f };
GLfloat light0_Spec[] = { 0.9f, 0.9f, 0.9f, 1.0f };


Camera g_cam;
Text g_text;
unsigned char g_keyStates[256];
MyMesh g_mesh = MyMesh();

// an object file path - a bunny model with 2K vertices
const char meshFile[128] = "Mesh/bunny2k.obj";


void init(void)
{

	// init the camera
	g_cam.set(3.0f, 4.0f, 3.0f, 0.0f, 0.0f, 0.0f, g_winWidth, g_winHeight);
	// set the color of on-screen texts
	g_text.setColor(0.0f, 0.0f, 0.0f);

	// loading the input mesh
	g_mesh.loadFromOBJ(meshFile);
}

void initialGL()
{
	// init GL light settings
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_Amb);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_Diff);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_Spec);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// specify polygon mode for rendering
	glPolygonMode(GL_FRONT, GL_FILL);


	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glShadeModel(GL_SMOOTH);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	// add any stuff to upate at runtime...
	g_cam.keyOperation(g_keyStates, g_winWidth, g_winHeight);
}

void display()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// use the specified lighting and shading properties to render the scene
	// this will bypass the default flat shading mode
	glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos); 

	// add things you'd like to draw ....
	
	g_mesh.draw();
	g_cam.drawCoordinateOnScreen(g_winWidth, g_winHeight);
	g_cam.drawCoordinate();

	// display the text
	if (g_cam.isFocusMode()) {
		string str = "Cam mode: Focus";
		g_text.draw(10, 30, const_cast<char*>(str.c_str()), g_winWidth, g_winHeight);
	}
	else if (g_cam.isFPMode()) {
		string str = "Cam mode: FP";
		g_text.draw(10, 30, const_cast<char*>(str.c_str()), g_winWidth, g_winHeight);
	}

	char s[128];
	sprintf_s(s, "vNum:%d, tNum:%d", g_mesh.getVertNum(), g_mesh.getTriNum());
	g_text.draw(10, 50, s, g_winWidth, g_winHeight);


	glutSwapBuffers();
}

void reshape(int w, int h)
{
	g_winWidth = w;
	g_winHeight = h;
	if (h == 0) {
		h = 1;
	}
	g_cam.setProj(g_winWidth, g_winHeight);
	g_cam.setModelView();
	glViewport(0, 0, w, h);
}

void mouse(int button, int state, int x, int y)
{
	g_cam.mouseClick(button, state, x, y, g_winWidth, g_winHeight);

}

void motion(int x, int y)
{
	g_cam.mouseMotion(x, y, g_winWidth, g_winHeight);
}

void keyup(unsigned char key, int x, int y)
{
	g_keyStates[key] = false;
}

void keyboard(unsigned char key, int x, int y)
{
	g_keyStates[key] = true;
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'c': // switch cam control mode
		g_cam.switchCamMode();
		glutPostRedisplay();
		break;
	case ' ':
		g_cam.PrintProperty();
		break;

	case 'v': // change view mode of mesh

		if (g_mesh.viewMode == SHADED_WITH_WIREFRAME)
			g_mesh.viewMode = SHADED;
		else if (g_mesh.viewMode == SHADED)
			g_mesh.viewMode = SHADED_WITH_WIREFRAME;
		glutPostRedisplay();
		break;

	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(g_winWidth, g_winHeight);
	glutCreateWindow("3D Mesh Rendering");

	glewInit();
	initialGL();
	init();

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardUpFunc(keyup);
	glutKeyboardFunc(keyboard);
	
	glutMainLoop();
	return 0;


}