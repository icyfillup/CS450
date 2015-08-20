/*
Benjamin Isani Evans
302396593 :)

*/
#ifndef LAB_SOLAR_H
#define LAB_SOLAR_H
#define ROTATE_RATE .5
#define PI 3.1415

float rotateEarth, rotateMoon, rotateSun, rotateMars;
//Global Variables
const int screenWidth = 500;	   // width of screen window in pixels
const int screenHeight = 500;	   // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0;
// global values for camera
GLdouble eyex=25.0, eyey=25.0, eyez=25.0;
GLdouble lookx=0.0, looky=0.0, lookz=0.0;
int view=0;

// global values for shading
GLfloat ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat diffuse[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat shininess[] = {50.0f};

GLfloat position[] = {2.0f, 6.0f, 3.0f, 0.0f};
GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};



#endif