#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif


// the window's width and height
int width, height;

void init(void)
{
    // initialize the size of the window
    width = 1200;
    height = 600;
}

// called when the GL context need to be rendered
void display(void)
{
    // clear the screen
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

    // prepare for drawing
    glColor3f(0.7, 0.7, 0.7);
    glPointSize(20.0f);
    glBegin(GL_LINES);

    // draw the lines parallel to the x-axis
    for (int i = -12; i < 13; i++) {
        glVertex3f(-12.0f, 0.0f, float(i));
        glVertex3f(12.0f, 0.0f, float(i));
    }

    // draw the lines parallel to the z-axis
    for (int i = -12; i < 13; i++) {
        glVertex3f(float(i), 0.0f, -12.0f);
        glVertex3f(float(i), 0.0f, 12.0f);
    }

    glEnd();

    // draw the lines that intersect with the origin
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);

    glVertex3f(-12.0f, 0.0f, 0.0f);
    glVertex3f(12.0f, 0.0f, 0.0f);

    glVertex3f(0.0f, 0.0f, -12.0f);
    glVertex3f(0.0f, 0.0f, 12.0f);

    glEnd();

    glPopMatrix();

    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // update thescreen dimensions
    width = w;
    height = h;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(20, 20, -20, 0, 0, 0, 0, 1, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 2.0f , 0.1, 1000);

    glViewport(0, 0, w, h);
    glViewport(0, 0, w, h);

    glutPostRedisplay();
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
    glutCreateWindow("Camera");

    /* --- register callbacks with GLUT --- */

    //register function to handle window resizes
    glutReshapeFunc(reshape);

    //register function that draws in the window
    glutDisplayFunc(display);

    //start the glut main loop
    glutMainLoop();

    return 0;
}