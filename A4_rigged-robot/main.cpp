// Andrew Broderick
// DSA2 RIT Fall 2022
// Assignment 4

//Usage:
// Press 'W' to select the parent part.
// Press 'S' to select a child part.
// Press the left and right arrow keys to cycle the neighbor parts.
// Press 'A' and 'D' to rotate the current selected part.

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>
using namespace std;

int win_width = 600, win_height = 600;
float canvas_width = 20.0f; float canvas_height = 20.0f;

const float PI = 3.1415926;

bool keyStates[256];
int buttonState;

float curMouse[2];
float preMouse[2];

int id = -1;
float rotations[16] = { PI / 2, -PI / 2, -PI / 2, -PI / 2, -PI / 2, -PI / 2, -PI / 2, PI / 2, PI / 2, PI / 2, PI, PI, PI, 0.0, 0.0, 0.0 };

void init(void)
{
    for (int i = 0; i < 256; i++) {
        keyStates[i] = false;
    }

    buttonState = -1;
}

void drawBox(float boxWidth, float boxHeight, float rotation)
{
    // vertices used for drawing
    float a[2] = { 0, 0 };
    float b[2] = { 0, boxHeight / 2.0 };
    float c[2] = { boxWidth, boxHeight / 2.0 };
    float d[2] = { boxWidth, -1 * (boxHeight / 2.0) };
    float e[2] = { 0, -1 * (boxHeight / 2.0) };

    // lines
    glColor3f(0.4, 0.8, 0.8);
    glLineWidth(3.0f);
    glBegin(GL_POLYGON);
    glVertex2f(a[0] * cos(rotation) - a[1] * sin(rotation), a[0]*sin(rotation)+a[1]*cos(rotation));
    glVertex2f(b[0] * cos(rotation) - b[1] * sin(rotation), b[0] * sin(rotation) + b[1] * cos(rotation));
    glVertex2f(c[0] * cos(rotation) - c[1] * sin(rotation), c[0] * sin(rotation) + c[1] * cos(rotation));
    glVertex2f(d[0] * cos(rotation) - d[1] * sin(rotation), d[0] * sin(rotation) + d[1] * cos(rotation));
    glVertex2f(e[0] * cos(rotation) - e[1] * sin(rotation), e[0] * sin(rotation) + e[1] * cos(rotation));
    glEnd();

    // fill
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(3.0f);
    glBegin(GL_LINE_STRIP);
    glVertex2f(a[0] * cos(rotation) - a[1] * sin(rotation), a[0] * sin(rotation) + a[1] * cos(rotation));
    glVertex2f(b[0] * cos(rotation) - b[1] * sin(rotation), b[0] * sin(rotation) + b[1] * cos(rotation));
    glVertex2f(c[0] * cos(rotation) - c[1] * sin(rotation), c[0] * sin(rotation) + c[1] * cos(rotation));
    glVertex2f(d[0] * cos(rotation) - d[1] * sin(rotation), d[0] * sin(rotation) + d[1] * cos(rotation));
    glVertex2f(e[0] * cos(rotation) - e[1] * sin(rotation), e[0] * sin(rotation) + e[1] * cos(rotation));
    glVertex2f(a[0] * cos(rotation) - a[1] * sin(rotation), a[0] * sin(rotation) + a[1] * cos(rotation));
    glEnd();

    // origin
    glColor3f(0.8, 0.0, 0.1);
    glPointSize(8.0f);
    glBegin(GL_POINTS);
    glVertex2f(a[0], a[1]);
    glEnd();
}

void display(void)
{
    glClearColor(0.5, 0.5, 0.5, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

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

    //pelvis
    id = 0;
    drawBox(2.5, 3.0, rotations[id]);
    glPushMatrix();
    // left thigh
    id++;
    glTranslatef(-1.0, 0.0, 0.0);
    drawBox(3.0, 1.0, rotations[id]);
    // left calf
    id++;
    glTranslatef(0.0, -3.0, 0.0);
    drawBox(2.0, 1.0, rotations[id]);
    // left foot
    id++;
    glTranslatef(0.0, -2.0, 0.0);
    drawBox(1.5, 1.5, rotations[id]);
    // right thigh
    id++;
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0, 0.0, 0.0);
    drawBox(3.0, 1.0, rotations[id]);
    // right calf
    id++;
    glTranslatef(0.0, -3.0, 0.0);
    drawBox(2.0, 1.0, rotations[id]);
    // right foot
    id++;
    glTranslatef(0.0, -2.0, 0.0);
    drawBox(1.5, 1.5, rotations[id]);
    // chest 
    id++;
    glPopMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    drawBox(2.7, 3.5, rotations[id]);
    glPushMatrix();
    // neck
    id++;
    glTranslatef(0.0, 2.7, 0.0);
    drawBox(1.0, 1.0, rotations[id]);
    // head
    id++;
    glTranslatef(0.0, 1.0, 0.0);
    drawBox(2.0, 2.0, rotations[id]);
    // left upper arm
    id++;
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.75, 2.0, 0.0);
    drawBox(2.0, 1.0, rotations[id]);
    // left lower arm
    id++;
    glTranslatef(-2.0, 0.0, 0.0);
    drawBox(1.5, 1.0, rotations[id]);
    // left hand
    id++;
    glTranslatef(-1.5, 0.0, 0.0);
    drawBox(1.5, 1.5, rotations[id]);
    // right upper arm
    id++;
    glPopMatrix();
    glTranslatef(1.75, 2.0, 0.0);
    drawBox(2.0, 1.0, rotations[id]);
    // right lower arm
    id++;
    glTranslatef(2.0, 0.0, 0.0);
    drawBox(1.5, 1.0, rotations[id]);
    // right hand
    id++;
    glTranslatef(1.5, 0.0, 0.0);
    drawBox(1.5, 1.5, rotations[id]);

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

    //else if (buttonState == GLUT_RIGHT_BUTTON) {
    //    for (unsigned char i = '1'; i < '7'; i++) {
    //        if (keyStates[i]) {
    //            rotations[i - asciiOffset] += curMouse[0] - preMouse[0];
    //        }
    //    }
    //    glutPostRedisplay();
    //}

    preMouse[0] = curMouse[0];
    preMouse[1] = curMouse[1];

}

int main(int argc, char* argv[])
{
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("Robot Rig");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutMainLoop();
    return 0;

}