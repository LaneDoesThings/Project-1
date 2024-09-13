#include <GL/glew.h>
#include <GL/freeglut.h>
#include <iostream>
#include "Project1.h"

#define canvas_Width 600
#define canvas_Height 600
#define framerate 60.0
#define z_Plane -1
#define box_Center 310
#define bottom_Box_Size 180
#define middle_Box_Size 120
#define top_Box_Size 60
#define snowflake_Size 50

int snowflake1X = ((snowflake_Size / 2) + 75);
int snowflake2X = ((canvas_Width - 75) - (snowflake_Size / 2));
int snowflakeY = (canvas_Height - 1) - (snowflake_Size / 2);
float msec = 0;
bool move = false;

void snowflake()
{
    glBegin(GL_LINES);

    //Horizontal Line
    glVertex3i(snowflake1X - (snowflake_Size / 2), snowflakeY, z_Plane);
    glVertex3i(snowflake1X + (snowflake_Size / 2), snowflakeY, z_Plane);

    //Diagonal Line 1
    glVertex3i(snowflake1X - 12.5, snowflakeY + 21.65063509, z_Plane);
    glVertex3i(snowflake1X + 12.5, snowflakeY - 21.65063509, z_Plane);

    //Diagonal Line 1
    glVertex3i(snowflake1X + 12.5, snowflakeY + 21.65063509, z_Plane);
    glVertex3i(snowflake1X - 12.5, snowflakeY - 21.65063509, z_Plane);

    //Horizontal Line
    glVertex3i(snowflake2X - (snowflake_Size / 2), snowflakeY, z_Plane);
    glVertex3i(snowflake2X + (snowflake_Size / 2), snowflakeY, z_Plane);

    //Diagonal Line 1
    glVertex3i(snowflake2X - 12.5, snowflakeY + 21.65063509, z_Plane);
    glVertex3i(snowflake2X + 12.5, snowflakeY - 21.65063509, z_Plane);

    //Diagonal Line 1
    glVertex3i(snowflake2X + 12.5, snowflakeY + 21.65063509, z_Plane);
    glVertex3i(snowflake2X - 12.5, snowflakeY - 21.65063509, z_Plane);


    glEnd();
}

void display_CB()
{
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);

    //Bottom Box
    int bottomBoxMid = bottom_Box_Size / 2;
    int bottomboxLeft = box_Center - bottomBoxMid;
    int bottomBoxRight = box_Center + bottomBoxMid;
    glVertex3i(bottomboxLeft, 1, z_Plane);
    glVertex3i(bottomBoxRight, 1, z_Plane);
    glVertex3i(bottomBoxRight, 1, z_Plane);
    glVertex3i(bottomBoxRight, bottom_Box_Size, z_Plane);
    glVertex3i(bottomBoxRight, bottom_Box_Size, z_Plane);
    glVertex3i(bottomboxLeft, bottom_Box_Size, z_Plane);
    glVertex3i(bottomboxLeft, bottom_Box_Size, z_Plane);
    glVertex3i(bottomboxLeft, 1, z_Plane);

    //Middle Box
    int middleBoxMid = middle_Box_Size / 2;
    int middleBoxleft = box_Center - middleBoxMid;
    int middleBoxRight = box_Center + middleBoxMid;
    int middleBoxBottom = bottom_Box_Size + 1;
    int middleBoxTop = bottom_Box_Size + middle_Box_Size;
    glColor3f(1.0, 1.0, 1.0);
    glVertex3i(middleBoxleft, middleBoxBottom, z_Plane);
    glVertex3i(middleBoxRight, middleBoxBottom, z_Plane);
    glVertex3i(middleBoxRight, middleBoxBottom, z_Plane);
    glVertex3i(middleBoxRight, middleBoxTop, z_Plane);
    glVertex3i(middleBoxRight, middleBoxTop, z_Plane);
    glVertex3i(middleBoxleft, middleBoxTop, z_Plane);
    glVertex3i(middleBoxleft, middleBoxTop, z_Plane);
    glVertex3i(middleBoxleft, middleBoxBottom, z_Plane);

    //Top Box
    int topBoxMid = top_Box_Size / 2;
    int topBoxLeft = box_Center - topBoxMid;
    int topBoxRight = box_Center + topBoxMid;
    int topBoxBottom = bottom_Box_Size + middle_Box_Size + 1;
    int topBoxTop = bottom_Box_Size + middle_Box_Size + top_Box_Size;
    glColor3f(1.0, 1.0, 1.0);
    glVertex3i(topBoxLeft, topBoxBottom, z_Plane);
    glVertex3i(topBoxRight, topBoxBottom, z_Plane);
    glVertex3i(topBoxRight, topBoxBottom, z_Plane);
    glVertex3i(topBoxRight, topBoxTop, z_Plane);
    glVertex3i(topBoxRight, topBoxTop, z_Plane);
    glVertex3i(topBoxLeft, topBoxTop, z_Plane);
    glVertex3i(topBoxLeft, topBoxTop, z_Plane);
    glVertex3i(topBoxLeft, topBoxBottom, z_Plane);

    glEnd();


    snowflake();
    glFlush();
}

void keyboard_CB(unsigned char key, int x, int y)
{
    move = true;
}

void timer_CB(int id)
{
    msec += 1000.0/framerate;

    if(msec >= 20 && move)
    {
        if((snowflakeY - 21.65063509) + 1 < 0)
        {
            snowflakeY = (snowflakeY - 21.65063509) + 1;
            return;
        }
        msec = 0;
        snowflakeY -= 4;
    }

    glutTimerFunc(1000/framerate, timer_CB, 0);
    glutPostRedisplay();
}

int main(int argc, char * argv[])
{
    std::cout << "Any key click will start" << std::endl;

    char canvas_Name[] = "Project 1 - Lane Wright";
    glutInit(&argc, argv);
    my_setup(canvas_Width, canvas_Height, canvas_Name);

    glutDisplayFunc(display_CB);
    glutTimerFunc(1000/framerate, timer_CB, 0);
    glutKeyboardFunc(keyboard_CB);

    glutMainLoop();
    return 0;
}