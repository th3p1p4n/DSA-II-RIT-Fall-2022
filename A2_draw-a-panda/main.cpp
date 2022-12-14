// Course: IGME 309-02
// Student Name: Andrew Broderick
// Assignment Number: 02

#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif
#include <math.h>
#include "main.h"


int width, height; // the window's width and height
int vertNum; // the number of vertices that the circles all currently have

void init(void)
{
    // initialize global variables
    width = 600;
    height = 600;
    vertNum = 10;
}

// called when the GL context need to be rendered
void display(void)
{
    // clear the screen to black, which is the background color
    glClearColor(0.10, 0.68, 0.33, 0.0);

    // clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // draw the circles that make up the panda
    // body
    drawFilledCircle(0.0, 0.0, 0.0, 5.0, 0.0, 4.0);
    drawFilledCircle(1.0, 1.0, 1.0, 5.0, 0.0, 2.0);
    drawFilledCircle(0.0, 0.0, 0.0, 1.5, 0.5, 1.2);
    drawFilledCircle(0.0, 0.0, 0.0, 8.5, 0.5, 1.2);
    // ears
    drawFilledCircle(0.0, 0.0, 0.0, 3.0, 7.5, 1.0);
    drawFilledCircle(0.0, 0.0, 0.0, 7.0, 7.5, 1.0);
    // head
    drawFilledCircle(1.0, 1.0, 1.0, 5.0, 5.0, 3.0);
    drawWireframeCircle(0.0, 0.0, 0.0, 5.0, 5.0, 3.0, 5.0);
    // mouth
    drawWireframeCircle(0.0, 0.0, 0.0, 4.4, 4.0, 0.6, 5.0);
    drawWireframeCircle(0.0, 0.0, 0.0, 5.6, 4.0, 0.6, 5.0);
    drawFilledCircle(1.0, 1.0, 1.0, 5.0, 4.9, 1.0);
    // nose
    drawFilledCircle(0.0, 0.0, 0.0, 5.0, 4.7, 0.5);
    // eyes
    drawFilledCircle(0.0, 0.0, 0.0, 3.8, 6.0, 0.8);
    drawFilledCircle(0.0, 0.0, 0.0, 6.2, 6.0, 0.8);
    drawFilledCircle(1.0, 1.0, 1.0, 3.8, 6.0, 0.3);
    drawFilledCircle(1.0, 1.0, 1.0, 6.2, 6.0, 0.3);

    glutPostRedisplay();
    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // update the screen dimensions
    width = w;
    height = h;

    //do an orthographic parallel projection, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 10.0, 0.0, 10.0);

    /* tell OpenGL to use the whole window for drawing */
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) {
        exit(0);
    }

    if (key == '-' && vertNum > 3) {
        vertNum--;
    }

    else if (key == '+' && vertNum < 100) {
        vertNum++;
    }

    glutPostRedisplay();
}

void drawFilledCircle(float red, float green, float blue, float center_x, float
    center_y, float radius)
{
    glColor3f(red, green, blue);

    glBegin(GL_POLYGON);

    for (int i = 0; i < vertNum; i++) {
        float degree = (float)i / vertNum * 2.0f * 3.14f;
        float x = radius * cos(degree) + center_x;
        float y = radius * sin(degree) + center_y;
        glVertex2f(x, y);
    }

    glEnd();
}

void drawWireframeCircle(float red, float green, float blue, float center_x, float
    center_y, float radius, float lineWidth)
{
    glColor3f(red, green, blue);
    glLineWidth(lineWidth);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < vertNum; i++) {
        float degree = (float)i / vertNum * 2.0f * 3.14f;
        float x = radius * cos(degree) + center_x;
        float y = radius * sin(degree) + center_y;
        glVertex2f(x, y);
    }

    glEnd();
}

int main(int argc, char* argv[])
{
    // before create a glut window,
    // initialize stuff not opengl/glut dependent
    init();

    //initialize GLUT, let it extract command-line GLUT options that you may provide
    //NOTE that the '&' before argc
    glutInit(&argc, argv);

    // specify as double bufferred can make the display faster
    // Color is speicfied to RGBA, four color channels with Red, Green, Blue and Alpha(depth)
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);

    //set the initial window size */
    glutInitWindowSize((int)width, (int)height);

    // create the window with a title
    glutCreateWindow("Adjustable Circle");

    /* --- register callbacks with GLUT --- */

    //register function to handle window resizes
    glutReshapeFunc(reshape);

    //register function to handle keyboard input
    glutKeyboardFunc(keyboard);

    //register function that draws in the window
    glutDisplayFunc(display);

    //start the glut main loop
    glutMainLoop();

    return 0;
}