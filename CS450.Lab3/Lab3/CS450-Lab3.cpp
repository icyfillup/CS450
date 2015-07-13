//Computer Graphics Lab - Animation
#include <windows.h>
#include <iostream>
#include <cmath>
#include <gl/Gl.h>
#include <gl/glut.h>

#include "CS450-Lab3.h"

using namespace std;

void myInit(void)
 {
    glClearColor(1.0,1.0,1.0,0.0);      // background color is white
    glColor3f(0.0f, 0.0f, 1.0f);        // drawing color is blue
    setWindow(-worldWidth/2, worldWidth/2, -worldHeight/2, worldHeight/2); // replaces the following three lines

    //glMatrixMode(GL_PROJECTION);      // set "camera shape"
    //glLoadIdentity();
    //gluOrtho2D(-worldWidth,worldWidth,-worldHeight, worldHeight);

    lineLength = 200;


    //n_Rotate and some_Rotate rotate the n-gon and some_gon from 0
    //degree. The purpose for this is to align one some_gon point to
    //two hexagon points, i.e. some_gon[0] matches up with hex[0] and
    //[1]. The point of this is to make the geometry easier to
    //understand in code.
    float n_Rotate = ((PI * 2) / n_Points);
    for(int i = 0; i < n_Points; i++)
    {
        float currAngle = (i * ((PI * 2) / n_Points)) + n_Rotate;
        n_gon[i].x = lineLength * cos(currAngle);
        n_gon[i].y = lineLength * sin(currAngle);
    }

    float some_Rotate = PI / 2;
    for(int i = 0; i < some_points; i++)
    {
        float currAngle = (i * ((PI * 2) / some_points) + some_Rotate);
        some_gon[i].x = (lineLength * 0.6) * cos(currAngle);
        some_gon[i].y = (lineLength * 0.6) * sin(currAngle);
    }

    for(int i = 0; i < some_points; i++)
    {
        // int sum = 2 * i;
        
        // currShape[sum].x = some_gon[i].x;
        // currShape[sum].y = some_gon[i].y;
        
        // currShape[sum + 1].x = some_gon[i].x;
        // currShape[sum + 1].y = some_gon[i].y;

        int shapeIncremeteor = i * ptsPerTriPt;
        for(int j = 0; j < ptsPerTriPt; j++)
        {
            currShape[shapeIncremeteor + j].x = some_gon[i].x;
            currShape[shapeIncremeteor + j].y = some_gon[i].y;
        }
     }
    
    glLineWidth(3);
}

void myIdle()
{
    //this function will be invoked when idle

    if(t < 1)
    {
        for(int i = 0; i < some_points; i++)
        {
            // int sum = 2 * i;
        
            // currShape[sum].x = ((1 - t) * some_gon[i].x) + (t * n_gon[sum].x);
            // currShape[sum].y = ((1 - t) * some_gon[i].y) + (t * n_gon[sum].y);
        
            // currShape[sum + 1].x = ((1 - t) * some_gon[i].x) + (t * n_gon[sum + 1].x);
            // currShape[sum + 1].y = ((1 - t) * some_gon[i].y) + (t * n_gon[sum + 1].y);

            int shapeIncremeteor = i * ptsPerTriPt;
            for(int j = 0; j < ptsPerTriPt; j++)
            {
                currShape[shapeIncremeteor + j].x = ((1 - t) * some_gon[i].x) + (t * n_gon[shapeIncremeteor + j].x);
                currShape[shapeIncremeteor + j].y = ((1 - t) * some_gon[i].y) + (t * n_gon[shapeIncremeteor + j].y);
            }

        }

        t += 0.01;
    }
    
    
    glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    Sleep(1);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
    glBegin(GL_LINES);
    {//draw shape here
        /*for(int i = 0; i < n_Points; i++)
        {
            int num = (i + 1) % n_Points;
            
            glVertex2f(n_gon[i].x, n_gon[i].y);
            glVertex2f(n_gon[num].x, n_gon[num].y);
        }

        for(int i = 0; i < some_points; i++)
        {

            int num = (i + 1) % some_points;
            
            glVertex2f(some_gon[i].x, some_gon[i].y);
            glVertex2f(some_gon[num].x, some_gon[num].y);
        }

        glVertex2f(n_gon[2].x, n_gon[2].y);
        glVertex2f(n_gon[3].x, n_gon[3].y);
        
        glVertex2f(some_gon[1].x, some_gon[1].y);*/

        for(int i = 0; i < n_Points; i++)
        {
            int num = (i + 1) % n_Points;
            
            glVertex2f(currShape[i].x, currShape[i].y);
            glVertex2f(currShape[num].x, currShape[num].y);
        }
        
    }
    glEnd();

    glutSwapBuffers();  // send all output to display
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Computer Graphics Lab - Animation"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw callback function
    glutIdleFunc(myIdle);           // register idle callback function

    myInit();
    glutMainLoop();              // go into a perpetual loop
}


//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}

float computeLineLength(GLfloatPoint2D p1, GLfloatPoint2D p2)
{
    return sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}
