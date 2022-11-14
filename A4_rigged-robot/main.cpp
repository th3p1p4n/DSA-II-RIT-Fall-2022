// Andrew Broderick
// DSA2 RIT Fall 2022
// Assignment 4

//Usage:
//Hold down the number keys , 1-7, to select one or multiple circles.
//While circle(s) are selected, use the left mouse button to translate and use the right mouse button to rotate.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;

#define MAX_NUM_CIRCLE 7
#define CIRCLE_RADIUM 2.0

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;


bool keyStates[256];
int buttonState;
float translations[2 * MAX_NUM_CIRCLE];
float rotations[MAX_NUM_CIRCLE];

float curMouse[2];
float preMouse[2];

void init(void)
{
    for (int i = 0; i < 256; i++) {
        keyStates[i] = false;
    }
    for (int i = 0; i < MAX_NUM_CIRCLE; i++) {

        translations[i * 2 + 0] = 0.0f; // x
        translations[i * 2 + 1] = 0.0f; // y

        rotations[i] = 0.0f;
    }

    buttonState = -1;
}

void drawBox(float boxWidth, float boxHeight)
{
    glColor3f(0.4, 0.8, 0.8);
    glLineWidth(3.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0 - (boxWidth / 2.0), 0 - (boxHeight / 2.0));
    glVertex2f(boxWidth / 2.0, 0 - (boxHeight / 2.0));
    glVertex2f(boxWidth / 2.0, boxHeight / 2.0);
    glVertex2f(0 - (boxWidth / 2.0), boxHeight / 2.0);
    glEnd();

    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(0-(boxWidth /2.0), 0-(boxHeight /2.0));
    glVertex2f(boxWidth /2.0, 0-(boxHeight /2.0));
    glVertex2f(boxWidth / 2.0, boxHeight / 2.0);
    glVertex2f(0 - (boxWidth / 2.0), boxHeight /2.0);
    glVertex2f(0 - (boxWidth / 2.0), 0 - (boxHeight / 2.0));
    glEnd();
}

void display(void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    drawBox(10, 10);
    //int cid = -1; // the index of current circle
    //// circle 0
    //cid = 0;
    //glTranslatef(translations[cid * 2 + 0], translations[cid * 2 + 1], 0.0f);
    //glRotatef(rotations[cid], 0.0f, 0.0f, 1.0f);
    //drawCircle(CIRCLE_RADIUM * (MAX_NUM_CIRCLE - cid) / MAX_NUM_CIRCLE, colors + cid * 3);

    //// circle 1
    //cid = 1;
    //glTranslatef(translations[cid * 2 + 0], translations[cid * 2 + 1], 0.0f);
    //glRotatef(rotations[cid], 0.0f, 0.0f, 1.0f);
    //glPushMatrix(); // push the circle 1's CS to the modelview stack
    //drawCircle(CIRCLE_RADIUM * (MAX_NUM_CIRCLE - cid) / MAX_NUM_CIRCLE, colors + cid * 3);


    //draw chest
    //push matrix(so you can go back to chest)
    //translate, draw neck
    //translate, draw head
    //pop matrix(return to the chest)
    //push matrix
    //translate, draw left arm
    //translate, draw left hand
    //pop matrix
    //push matrix
    //translate, draw right arm
    //translate, draw right hand
    //pop matrix
    //translate, draw pelvis
    //push matrix
    //translate, draw left thigh
    //translate, draw left lower leg
    //translate, draw left foot
    //pop matrix
    //translate, draw right thigh
    //translate, draw right lower leg
    //translate, draw right foot

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    win_width = w;
    win_height = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
    glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

    glutPostRedisplay();
}


void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) // 'esc' key
        exit(0);

    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    unsigned char asciiOffset = 49; // see an ascii table

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        buttonState = button;
        curMouse[0] = ((float)x / win_width - 0.5f) * canvas_width;
        curMouse[1] = ((float)(win_height - y) - 0.5f) / win_height * canvas_height;
        preMouse[0] = ((float)x / win_width - 0.5f) * canvas_width;
        preMouse[1] = ((float)(win_height - y) - 0.5f) / win_height * canvas_height;
    }
    else if (state == GLUT_UP)
        button = -1;
}

void motion(int x, int y)
{
    unsigned char asciiOffset = 49; // see an ascii table

    curMouse[0] = ((float)x / win_width - 0.5f) * canvas_width;
    curMouse[1] = ((float)(win_height - y) - 0.5f) / win_height * canvas_height;

    if (buttonState == GLUT_LEFT_BUTTON) {
        for (unsigned char i = '1'; i < '7'; i++) {
            if (keyStates[i]) {
                translations[(i - asciiOffset) * 2 + 0] += curMouse[0] - preMouse[0];
                translations[(i - asciiOffset) * 2 + 1] += curMouse[1] - preMouse[1];
            }
        }
        glutPostRedisplay();
    }

    else if (buttonState == GLUT_RIGHT_BUTTON) {
        for (unsigned char i = '1'; i < '7'; i++) {
            if (keyStates[i]) {
                rotations[i - asciiOffset] += curMouse[0] - preMouse[0];
            }
        }
        glutPostRedisplay();
    }

    preMouse[0] = curMouse[0];
    preMouse[1] = curMouse[1];

}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("2D Transformation Tree");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;

}