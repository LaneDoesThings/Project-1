#include <GL/glew.h>
#include <GL/freeglut.h>
#include "Project1.h"

void display_func()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    //draw a short green line
    glColor3f(0.0, 1.0, 0.1);
    glBegin(GL_LINES);
    glVertex2i(25,25);
    glVertex2i(50, 75);
    glEnd();
    glFlush();
}

#define canvas_Width 100
#define canvas_Height 100
char canvas_Name[] = "Project 1 Lane Wright";


int main(int argc, char * argv[])
{
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);

    glutDisplayFunc(display_func);

    glutMainLoop();
    return 0;
}