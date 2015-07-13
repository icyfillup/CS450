//Computer Graphics Lab : Drawing an object and changing world view

#include <windows.h>
#include <math.h>   // included for random number generation
#include <gl/Gl.h>
#include <gl/glut.h>
#include <iostream>

const int screenWidth = 500;
const int screenHeight = 500;
const double PI = 4.0 * atan(1.0);

// left, right, bottom, top
float lt, rt, bt, tp;

int n_gon = 45;
int radius = 8;
float rate = 0.08;
void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
    glMatrixMode(GL_PROJECTION);       // set "camera shape"
    glLoadIdentity();
    lt = -10;
    rt = 10;
    bt = -10;
    tp = 10;
    gluOrtho2D(lt, rt, bt, tp); // set the world window
    //gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case 'z':
        {// zoom-in
            std::cout << "zoom-in" << std::endl;
            lt += rate;
            rt += -rate;
            bt += rate;
            tp += -rate;
        } break;
        case 'Z':
        {// zoom-out
            std::cout << "zoom-out" << std::endl;
            lt += -rate;
            rt += rate;
            bt += -rate;
            tp += rate;
        }break;
        default:
            break;            // do nothing
    }
    glutPostRedisplay(); // implicitly call myDisplay
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case GLUT_KEY_UP:
        {// move the object to the top in a small amount
            bt += rate;
            tp += rate;
            
        }break;
        case GLUT_KEY_DOWN:
        {// move the object to the bottom in a small amount
            bt += -rate;
            tp += -rate;
        }break;
        case GLUT_KEY_LEFT:
        {// move the object to the left in a small amount
            lt += -rate;
            rt += -rate;            
        }break;
        case GLUT_KEY_RIGHT:
        {// move the object to the right in a small amount
            lt += rate;
            rt += rate;
        }break;
        default:
            break;            // do nothing
    }
    
    glutPostRedisplay(); // implicitly call myDisplay
}

//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    setWindow(lt, rt, bt, tp); // set the world window    
    
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    glColor3f(0.0f, 0.0f, 1.0f);
    
    glBegin(GL_LINE_LOOP);
    {// draw a shape
        for(int i = 0; i < n_gon; i++)
        {
            float currAngle = i * ((PI * 2) / n_gon);
            float currX = radius * cos(currAngle);
            float currY = radius * sin(currAngle);

            glVertex2f(currX, currY);
        }
    }
    glEnd();

    //glFlush();
    glutSwapBuffers();
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    glutInit(&argc, argv);          // initialize the toolkit
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Computer Graphics - Lab"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw function
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);

    myInit();

    glutMainLoop();              // go into a perpetual loop
}
