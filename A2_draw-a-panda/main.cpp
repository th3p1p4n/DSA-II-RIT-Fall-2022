#ifdef __APPLE__
#include <GLUT/glut.h> // include glut for Mac
#else
#include <GL/freeglut.h> //include glut for Windows
#endif
#include <math.h>


// the window's width and height
int width, height;

// a circle
int vertNum = 10;
float xo = 5.0f, yo = 5.0f;
float r = 4.0f;

void init(void)
{
    // initialize the size of the window
    width = 600;
    height = 600;
}

// called when the GL context need to be rendered
void display(void)
{
    // clear the screen to white, which is the background color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // clear the buffer stored for drawing
    glClear(GL_COLOR_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // specify the color and line width for drawing
    glColor3f(0.0, 1.0, 1.0);
    glLineWidth(5.0);

    // draw a circle
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < vertNum; i++) {
        float degree = (float)i / vertNum * 2.0f * 3.14f;
        float x = r * cos(degree) + xo;
        float y = r * sin(degree) + yo;
        glVertex2f(x, y);
    }
    glEnd();

    glutPostRedisplay();
    glutSwapBuffers();
}

// called when window is first created or when window is resized
void reshape(int w, int h)
{
    // update thescreen dimensions
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