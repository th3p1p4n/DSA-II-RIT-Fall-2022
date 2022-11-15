// Andrew Broderick
// DSA2 RIT Fall 2022
// Assignment 4

//Usage:
// Press 'W' and 'S' to cycle through body parts
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

// ids for each body part
int id = -1;

// which body part is currently selected. starts with pelvis as default.
int selectedId = 0;

// the initial orientations of the shapes, used for drawing
float orientations[16] = { PI / 2, -PI / 2, -PI / 2, -PI / 2, -PI / 2, -PI / 2, -PI / 2, PI / 2, PI / 2, PI / 2, PI, PI, PI, 0.0, 0.0, 0.0 };

// the modifiable rotations
float rotations[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };

void init(void)
{
    for (int i = 0; i < 256; i++) {
        keyStates[i] = false;
    }

    buttonState = -1;
}

void drawBox(float boxWidth, float boxHeight, float rotation, bool selected)
{
    // vertices used for drawing
    float a[2] = { 0, 0 };
    float b[2] = { 0, boxHeight / 2.0 };
    float c[2] = { boxWidth, boxHeight / 2.0 };
    float d[2] = { boxWidth, -1 * (boxHeight / 2.0) };
    float e[2] = { 0, -1 * (boxHeight / 2.0) };

    // fill
    glColor3f(0.4, 0.8, 0.8);
    glLineWidth(3.0f);
    glBegin(GL_POLYGON);
    if (selected) { // use a different fill color if the box is selected
        glColor3f(0.2, 0.0, 0.8);
    }
    glVertex2f(a[0] * cos(rotation) - a[1] * sin(rotation), a[0] * sin(rotation) + a[1] * cos(rotation));
    glVertex2f(b[0] * cos(rotation) - b[1] * sin(rotation), b[0] * sin(rotation) + b[1] * cos(rotation));
    glVertex2f(c[0] * cos(rotation) - c[1] * sin(rotation), c[0] * sin(rotation) + c[1] * cos(rotation));
    glVertex2f(d[0] * cos(rotation) - d[1] * sin(rotation), d[0] * sin(rotation) + d[1] * cos(rotation));
    glVertex2f(e[0] * cos(rotation) - e[1] * sin(rotation), e[0] * sin(rotation) + e[1] * cos(rotation));
    glEnd();

    // lines
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

    //pelvis
    id = 0;
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(2.5, 3.0, orientations[id], id == selectedId);
    glPushMatrix();
    // left thigh
    id++;
    glTranslatef(-1.0, 0.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(3.0, 1.0, orientations[id], id == selectedId);
    // left calf
    id++;
    glTranslatef(0.0, -3.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(2.0, 1.0, orientations[id], id == selectedId);
    // left foot
    id++;
    glTranslatef(0.0, -2.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(1.5, 1.5, orientations[id], id == selectedId);
    // right thigh
    id++;
    glPopMatrix();
    glPushMatrix();
    glTranslatef(1.0, 0.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(3.0, 1.0, orientations[id], id == selectedId);
    // right calf
    id++;
    glTranslatef(0.0, -3.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(2.0, 1.0, orientations[id], id == selectedId);
    // right foot
    id++;
    glTranslatef(0.0, -2.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(1.5, 1.5, orientations[id], id == selectedId);
    // chest 
    id++;
    glPopMatrix();
    glTranslatef(0.0, 2.5, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(2.7, 3.5, orientations[id], id == selectedId);
    glPushMatrix();
    // neck
    id++;
    glTranslatef(0.0, 2.7, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(1.0, 1.0, orientations[id], id == selectedId);
    // head
    id++;
    glTranslatef(0.0, 1.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(2.0, 2.0, orientations[id], id == selectedId);
    // left upper arm
    id++;
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-1.75, 2.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(2.0, 1.0, orientations[id], id == selectedId);
    // left lower arm
    id++;
    glTranslatef(-2.0, 0.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(1.5, 1.0, orientations[id], id == selectedId);
    // left hand
    id++;
    glTranslatef(-1.5, 0.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(1.5, 1.5, orientations[id], id == selectedId);
    // right upper arm
    id++;
    glPopMatrix();
    glTranslatef(1.75, 2.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(2.0, 1.0, orientations[id], id == selectedId);
    // right lower arm
    id++;
    glTranslatef(2.0, 0.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(1.5, 1.0, orientations[id], id == selectedId);
    // right hand
    id++;
    glTranslatef(1.5, 0.0, 0.0);
    glRotatef(rotations[id], 0.0, 0.0, 1.0);
    drawBox(1.5, 1.5, orientations[id], id == selectedId);

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

    if (key == 'W' || key == 'w') {
        if (selectedId < 15) {
            selectedId++;
        }
        else {
            selectedId = 0;
        }
    }

    if (key == 'S' || key == 's') {
        if (selectedId > 0) {
            selectedId--;
        }
        else {
            selectedId = 15;
        }
    }

    if (key == 'A' || key == 'a') {
        rotations[selectedId] = rotations[selectedId] + PI / 8;
    }

    if (key == 'D' || key == 'd') {
        rotations[selectedId] = rotations[selectedId] - PI / 8;
    }

    glutPostRedisplay();
}

void keyboardUp(unsigned char key, int x, int y)
{
    glutPostRedisplay();
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
    glutMainLoop();
    return 0;

}