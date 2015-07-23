#include <windows.h>
#include <math.h>   // included for random number generation
#include <ctime>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <iostream>

#include "settings.h"
 
GLfloatPoint2D ballPosition;
GLfloatColor3f ballColor;
GLfloatPoint2D ballSpeed;

float speedScalar;

float radius;

bool fillToggle;
bool stopBall;

void setWindow(float left, float right, float bottom, float top);
void setColor3f(GLfloatColor3f&);
void resetBall(void);
void setRandomVecterSpeed2f(GLfloatPoint2D&);

void myInit(void)
{
    
    lt = -WORLD_WIDTH / 2;
    rt = WORLD_WIDTH / 2;
    bt = -WORLD_HEIGHT / 2;
    tp = WORLD_HEIGHT / 2;

    resetBall();
    
    glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
    glMatrixMode(GL_PROJECTION);       // set "camera shape"
    glLoadIdentity();
    gluOrtho2D(lt, rt, bt, tp); // set the world window
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case 'a':
        {//TODO:(philip): add another ball with different color onto window
            #if DEBUG
            debugPrint("a");
            #endif
            
        }break;
        
        case 'r':
        {//TODO(philip): remove recently added ball. NOTE: key cannot remove first ball 
            #if DEBUG
            debugPrint("r");
            #endif
            
        }break;

        case 's':
        {//TODO(philip): toggle between moving and stopping ALL balls on screen
            #if DEBUG
            debugPrint("s");
            #endif

            stopBall = !stopBall;
        }break;

        case 'n':
        {//TODO(philip): reset the program to the starting state
            #if DEBUG
            debugPrint("n");
            #endif

            resetBall();
        }break;
        
        case 'q':
        {//TODO(philip): Quit the program
            #if DEBUG
            debugPrint("q");
            #endif
            
            exit(0);
        }break;

        case 'p':
        {//TODO(phiilp): toggle the display of the first ball between filled ball and non-filled ball. 
            #if DEBUG
            debugPrint("p");
            #endif

            fillToggle = !fillToggle;
        }break;
        
        default:
           break;
    }
    glutPostRedisplay(); // implicitly call myDisplay
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case GLUT_KEY_PAGE_UP:
        {//TODO(philip): increment the radius of the first ball

            radius += 0.02f;

#if DEBUG
            debugPrint("GLUT_KEY_PAGE_UP");
#endif

            
        }break;

        case GLUT_KEY_PAGE_DOWN:
        {//TODO(philip): decrement the radius of the first ball

            radius = (radius > 0) ? radius -= 0.02f  : 0.0f;

#if DEBUG
            debugPrint("GLUT_KEY_PAGE_DOWN");
#endif

        }break;
        
        case GLUT_KEY_UP:
        {//TODO(philip): increase the speed of the first ball

            speedScalar += 0.02f;
            
#if DEBUG
            debugPrint("GLUT_KEY_UP");
            debugPrint(speedScalar < 1);
            debugPrint(speedScalar);
            debugPrint("");            
#endif
            
        }break;

        case GLUT_KEY_DOWN:
        {//TODO(philip): decrease the speed of the first ball NOTE(philip): check when speedScalar is 0

            speedScalar = (speedScalar > 0) ? speedScalar -= 0.02f  : 0.0f;

#if DEBUG
            debugPrint("GLUT_KEY_DOWN");
            debugPrint(speedScalar > 0);
            debugPrint(speedScalar);
            debugPrint("");
#endif
            
        }break;
      
        default:
            break;
    }

    glutPostRedisplay(); // implicitly call myDisplay
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    Sleep(1);
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    glColor3f(ballColor.r, ballColor.g, ballColor.b);
    
    (fillToggle) ? glBegin(GL_POLYGON) : glBegin(GL_LINE_LOOP);
    {
        for(float i = 0; i < 1; i += 0.01)
        {
            float x = (radius * cos(i * (2 * PI))) + ballPosition.x;
            float y = (radius * sin(i * (2 * PI))) + ballPosition.y;

            glVertex2f(x, y);
        }
    }
    glEnd();
    
    //glFlush();
    glutSwapBuffers();
}

//--------------myIdle---------------------------
void myIdle(void)
{
    if((ballPosition.x + radius) > rt ||
       (ballPosition.x - radius) < lt)
    {
        ballSpeed.x = -ballSpeed.x;
    }

    if((ballPosition.y + radius) > tp ||
       (ballPosition.y - radius) < bt)
    {
        ballSpeed.y = -ballSpeed.y;
    }
    
    if(!stopBall)
    {
        ballPosition.x += ballSpeed.x * speedScalar;
        ballPosition.y += ballSpeed.y * speedScalar;    
    }
    
    glutPostRedisplay();
}

//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}

void resetBall(void)
{
    fillToggle = true;
    stopBall = false;
    
    ballPosition.x = 0;
    ballPosition.y = 0;

    radius = 2.5f;

    setRandomVecterSpeed2f(ballSpeed);
    speedScalar = 0.2;
    
    setColor3f(ballColor);
}

void setColor3f(GLfloatColor3f& color)
{
    color.r = (GLfloat)rand() / RAND_MAX;
    color.g = (GLfloat)rand() / RAND_MAX;
    color.b = (GLfloat)rand() / RAND_MAX;

    #if DEBUG
    debugPrint(color.r);
    debugPrint(color.g);
    debugPrint(color.b);
    #endif
}

void setRandomVecterSpeed2f(GLfloatPoint2D& speed)
{
    speed.x = 2 * ((GLfloat)rand() / RAND_MAX) - 1;
    speed.y = 2 * ((GLfloat)rand() / RAND_MAX) - 1;
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    srand((unsigned)time(0));

    glutInit(&argc, argv);          // initialize the toolkit
    //glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // set display mode

    glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen

    glutCreateWindow("Computer Graphics - Bouncing Ball Program"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw function
    glutIdleFunc(myIdle);

    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);

    myInit();

    glutMainLoop();              // go into a perpetual loop
}
