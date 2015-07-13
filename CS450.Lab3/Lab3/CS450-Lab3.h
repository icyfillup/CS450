#ifndef LAB_ANIM_H
#define LAB_ANIM_H

#define PI 3.1415

struct GLintPoint2D {
    GLint x, y;
};

struct GLfloatPoint2D {
    GLfloat x,y;
};


//Global Variables
const int screenWidth = 500;       // width of screen window in pixels
const int screenHeight = 500;      // height of screen window in pixels

const float worldWidth = 500.0;
const float worldHeight = 500.0; 

//n_Points HAS TO BE DIVIDABLE BY TRIPOINTS OR 3
const int n_Points = 48;
GLfloatPoint2D n_gon[n_Points];
GLfloatPoint2D currShape[n_Points];

const int some_points = 24;
GLfloatPoint2D some_gon[some_points];

int ptsPerTriPt = n_Points / some_points;

GLdouble lineLength;

// Initial values
GLdouble t = 0.0;



void setWindow(float left, float right, float bottom, float top);
float computeLineLength(GLfloatPoint2D p1, GLfloatPoint2D p2);

#endif
