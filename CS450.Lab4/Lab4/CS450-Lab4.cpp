#include <windows.h>
#include <cmath>
#include <gl/Gl.h>
#include <gl/glut.h>

#include "CS450-Lab4.h"

using namespace std;

void genOctahedron()
{
    GLfloat v[][3] =
    {{-1.0, 0.0, 1.0}, {1.0, 0.0, 1.0}, {1.0, 0.0, -1.0}, {-1.0, 0.0, -1.0}, {0.0, 1.5, 0.0}, {0.0, -1.5, 0.0}};

    for(int i = 0; i < 8; i++)
    {
        octahedron[i].vertices[0] = v[i][0];
        octahedron[i].vertices[1] = v[i][1];
        octahedron[i].vertices[2] = v[i][2];
    }
}

void drawTriangle(int a, int b, int c)
{
    glBegin(GL_LINE_LOOP);
    // glVertex3fv(octahedron[a].vertices) is same as
    // glVertex3f(octahedron[a].vertices[0],octahedron[a].vertices[1],octahedron[a].vertices[2])

    
    //point
    float ax = octahedron[a].vertices[0];
    float ay = octahedron[a].vertices[1];
    float az = octahedron[a].vertices[2];
    
    float bx = octahedron[b].vertices[0];
    float by = octahedron[b].vertices[1];
    float bz = octahedron[b].vertices[2];

    float cx = octahedron[c].vertices[0];
    float cy = octahedron[c].vertices[1];
    float cz = octahedron[c].vertices[2];    
/*        
    //translation
    ax = ax + tx;
    ay = ay + ty;
    az = az + tz;

    bx = bx + tx;
    by = by + ty;
    bz = bz + tz;
    
    cx = cx + tx;
    cy = cy + ty;
    cz = cz + tz;
    
    //Scale
    ax = ax * scale;
    ay = ay * scale;
    az = az * scale;

    bx = bx * scale;
    by = by * scale;
    bz = bz * scale;

    cx = cx * scale;
    cy = cy * scale;
    cz = cz * scale;

    //rotation
    ax = (ax * cos(rotation_angle)) + (az * sin(rotation_angle));
    az = (az * cos(rotation_angle)) - (ax * sin(rotation_angle));

    bx = (bx * cos(rotation_angle)) + (bz * sin(rotation_angle));
    bz = (bz * cos(rotation_angle)) - (bx * sin(rotation_angle));

    cx = (cx * cos(rotation_angle)) + (cz * sin(rotation_angle));
    cz = (cz * cos(rotation_angle)) - (cx * sin(rotation_angle));
    */
  
    //draw
    glVertex3f(ax, ay, az);
    glVertex3f(bx, by, bz);
    glVertex3f(cx, cy, cz);
    
    
    
    glEnd();
}

void drawOctahedron()
{
    drawTriangle(4, 0, 1);
    drawTriangle(4, 1, 2);
    drawTriangle(4, 2, 3);
    drawTriangle(4, 3, 0);
    drawTriangle(5, 0, 1);
    drawTriangle(5, 1, 2);
    drawTriangle(5, 2, 3);
    drawTriangle(5, 3, 0);
}

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);    // drawing color is black

    glMatrixMode(GL_PROJECTION);    // set "camera shape"
    glLoadIdentity();

    // notice that this is not gluOrtho2D() anymore
    glOrtho(-10.0, 10.0, -10.0, 10.0, 10.0, 40.0);

    // Assign points for octahedron
    genOctahedron();
}

void myKeyboard(unsigned char key, int x, int y)
{

    switch(key)
    {
        case '+':
        {// do what you need to do for up-scale here
            scale += 1.0f * 0.05f;
        }break;
        case '-':
        {// do what you need to do for down-scale  here
            scale -= 1.0f * 0.05f;
        }break;
        case 'r':
        {// do what you need to do for rotation here
            rotation_angle += (2 * PI) * 0.05f;
        }break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mySpecialKeyboard(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_UP:
        {// do what you need to do for translation in one direction here
            ty += 1.0f * 0.10f;
        }break;
        case GLUT_KEY_DOWN:
        {// do what you need to do for translation in the opposite direction of UP KEY here
            ty -= 1.0f * 0.10f;
        }break;
        case GLUT_KEY_LEFT:
        {// do what you need to do for translation in one direction here
            tx -= 1.0f * 0.10f;
        }break;
        case GLUT_KEY_RIGHT:
        {// do what you need to do for translation in the opposite direction of LEFT KEY here
            tx += 1.0f * 0.10f;
        }break;
        case GLUT_KEY_HOME:
        {// do what you need to do for initialization here
            tx = ty = tz = 0.0f;
            scale = 1.0f;
            rotation_angle = 0.0f;
        }break;
        default:
            break;
    }
    glutPostRedisplay();
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // set the camera location and orientation
    // for Lab5, do not touch this line
    gluLookAt(10.0, 10.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // apply your own transformations accordingly here


      
    //NOTE: called the glscale-translate-rotate before you called glbegin()
    glScalef(scale, scale, scale);
    glTranslatef(tx, ty, tz);
    glRotatef(rotation_angle, 0, 1, 0);
    
    // draw octahedron
    drawOctahedron();
    glFlush();         // send all output to display

}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Lab-Wireframe Octahedron"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    myInit();
    glutMainLoop();              // go into a perpetual loop
}
