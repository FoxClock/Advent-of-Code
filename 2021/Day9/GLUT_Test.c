// AUTHOR:	Hayden Foxwell
// DATE:	05-05-2024
// PURPOSE:	Day 9 -
#include <stdlib.h>
#include "../Common/common.h"

float px, py;

void drawplayer() {
   glColor3f(1,1,0);
   glPointSize(8);
   glBegin(GL_POINTS);
   glVertex2i(px, py);
   glEnd();
}

void buttons(unsigned char key, int x, int y)
{
    // easily quit the application
    if (key == 'q') {exit(EXIT_SUCCESS);}
    
    if (key == 'a') {px -= 5;}
    if (key == 'd') {px += 5;}
    if (key == 'w') {py += 5;}
    if (key == 's') {py -= 5;}

    glutPostRedisplay();
    printf("key Pressed[%c]:\t[x:%f ,y:%f]\n", key, px, py);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    drawplayer();

    glutSwapBuffers();

    // Check for OpenGL errors
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        printf("OpenGL error: %s\n", gluErrorString(err));
    }
}

int main(int argc, char **argv) {
    // initialise glut
    px = 300;
    py = 300;
    
    initializeGLUT(argc, argv, display, buttons);

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}