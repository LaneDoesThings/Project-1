/*
Graphics Pgm 1 for Lane Wright

This Program will draw a "snowman" made from 3 boxes and 2 "snowflakes" drawn
from intersecting lines.

Events with callbacks are used to drive the program where an event handler is
set up in main and the callback specified elsewhere. This allows for a modular
design where only the events needed are set up which leads to better
performance.

The scene is also formed programatically meaning that the output can change by
just changing the #defines
*/

#include "Project1.h"
#include <GL/freeglut.h>
#include <GL/glew.h>
#include <iostream>

#define canvas_Width 600
#define canvas_Height 600
#define framerate 60.0
#define z_Plane -1 // Specified in assignment documentation
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

// Draws snowflakes where the center point is at snowflakeX, snowflakeY
void snowflake() {

  /*
  A note on the magic numbers 21.65063509 and 12.5.
  These are the X and Y coords needed for a line of length 50
  with a 60° angle. I would do this programmatically i.e (snowflake_Size / 2 *
  sin\cos(60°)) but the program assignment disallowed libraries and I don't know
  if math is allowed.
  */

  glBegin(GL_LINES);

  // Snowflake 1
  // Horizontal Line
  glVertex3i(snowflake1X - (snowflake_Size / 2), snowflakeY, z_Plane);
  glVertex3i(snowflake1X + (snowflake_Size / 2), snowflakeY, z_Plane);

  // Diagonal Line 1
  glVertex3i(snowflake1X - 12.5, snowflakeY + 21.65063509, z_Plane);
  glVertex3i(snowflake1X + 12.5, snowflakeY - 21.65063509, z_Plane);

  // Diagonal Line 2
  glVertex3i(snowflake1X + 12.5, snowflakeY + 21.65063509, z_Plane);
  glVertex3i(snowflake1X - 12.5, snowflakeY - 21.65063509, z_Plane);

  // Snowflake 2
  // Horizontal Line
  glVertex3i(snowflake2X - (snowflake_Size / 2), snowflakeY, z_Plane);
  glVertex3i(snowflake2X + (snowflake_Size / 2), snowflakeY, z_Plane);

  // Diagonal Line 1
  glVertex3i(snowflake2X - 12.5, snowflakeY + 21.65063509, z_Plane);
  glVertex3i(snowflake2X + 12.5, snowflakeY - 21.65063509, z_Plane);

  // Diagonal Line 2
  glVertex3i(snowflake2X + 12.5, snowflakeY + 21.65063509, z_Plane);
  glVertex3i(snowflake2X - 12.5, snowflakeY - 21.65063509, z_Plane);

  glEnd();
}

// Callback for the display event
// Handles drawing things to screen and refreshing screen
void display_CB() {
  glClearColor(0, 0, 0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_LINES);

  // Bottom Box
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

  // Middle Box
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

  // Top Box
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

  snowflake(); // Draw the snowflake
  glFlush();
}

// Callback that fires whenever an ascii key is pressed
void keyboard_CB(unsigned char key, int x, int y) { move = true; }

// Callback that fires after set time
void timer_CB(int id) {
  msec += 1000.0 / framerate;

  // If it has been 20 miliseconds and the keyboard has been pressed
  // Move the snowflake
  if (msec >= 20 && move) {
    // We have hit the bottom of the screen
    if ((snowflakeY - 21.65063509) + 1 < 0) {
      snowflakeY = (snowflakeY - 21.65063509) + 1;
      return;
    }
    msec = 0;
    snowflakeY -= 4;
  }

  // Run the timer again
  glutTimerFunc(1000 / framerate, timer_CB, 0);
  glutPostRedisplay();
}

int main(int argc, char *argv[]) {
  std::cout << "Any key click will start" << std::endl;

  char canvas_Name[] = "Project 1 - Lane Wright";
  glutInit(&argc, argv);
  my_setup(canvas_Width, canvas_Height, canvas_Name);

  // Set up event handlers
  glutDisplayFunc(display_CB);
  glutTimerFunc(1000 / framerate, timer_CB, 0);
  glutKeyboardFunc(keyboard_CB);

  glutMainLoop();
  return 0;
}