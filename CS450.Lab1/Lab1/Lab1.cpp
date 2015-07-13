// Computer Graphics
#include <windows.h>
#include <math.h>   // included for random number generation
#include <gl/Gl.h>
#include <gl/glut.h>
#include <ctime>
#include <iostream>

const int screenWidth = 500;
const int screenHeight = 500;
const double PI = 4.0 * atan(1.0);
const int num_of_points = 500;

struct GLintPoint
{
    GLint x, y;
};

GLintPoint pts[4];
int NoOfPts = 0;
bool isC_down = false, isP_down = false;

bool isLastMouseInput = false;
short recPts = 0;

void myInit(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
    glMatrixMode(GL_PROJECTION);       // set "camera shape"
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)screenWidth, 0.0, (GLdouble)screenHeight);
}

void myMouse(int button, int state, int x, int y)
{
    // if the left button was pressed,
    // store the mouse location into the pts[],
    // and increment # of points

    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(recPts < 3)
        {
            pts[recPts] = GLintPoint{x, screenHeight - y};
            recPts++;
            isLastMouseInput = false;
        }
    }
    
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        if(recPts > 2)
        {
            pts[recPts] = GLintPoint{x, screenHeight - y};
            recPts = 0;
            isLastMouseInput = true;
        }
    }
    
    isP_down = false;
    isC_down = false;
    glutPostRedisplay();
    
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // clear the screen

    // draw either a polygon(rectangle) using the points in pts[] or a cosine graph
    // To access a point in pts[], use the syntax like pts[index].x or pts[index].y

    if(isC_down)
    {
        float r = (float)rand()/RAND_MAX;
        float g = (float)rand()/RAND_MAX;
        float b = (float)rand()/RAND_MAX;
    
        glClearColor(r, g, b, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

    }

    if(isP_down)
    {
        int scalar = 75;

        GLfloat sin_pts_x[num_of_points];
        
        GLfloat dx = (2 * PI) / num_of_points;
         
        
        for(int i = 0; i < num_of_points; i++)
        {
            sin_pts_x[i] = dx * i;
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
        {
            for(int i = 0; i < num_of_points; i++)
            {
                glVertex2f((sin_pts_x[i] * scalar), (scalar * cos(sin_pts_x[i]) + 250));
            }     
        }
        glEnd();
    }

    if(isLastMouseInput)
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(1.0, 0.0, 0.0);
        
        glBegin(GL_POLYGON);
        {
            glVertex2i(pts[3].x, pts[3].y);
            glVertex2i(pts[0].x, pts[0].y);
            glVertex2i(pts[1].x, pts[1].y);
            glVertex2i(pts[2].x, pts[2].y);
           
        }
        glEnd();
    }
    
    glFlush();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case 'c':
        {// change the current background color into a new one
            isC_down = true;
            isP_down = false;
            isLastMouseInput = false;
        }break;
        case 'p':
        {// indicate that the display function needs to draw a graph
            isP_down = true;
            isC_down = false;
            isLastMouseInput = false;
        }break;
        default:
            break;            // do nothing
    }

    glutPostRedisplay(); // implicitly call myDisplay
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    srand((unsigned)time(0));
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 150); // set window position on screen
    glutCreateWindow("Computer Graphics - Lab1"); // open the screen window

    glutDisplayFunc(myDisplay);     // register redraw function
    glutMouseFunc(myMouse);
    glutKeyboardFunc(myKeyboard);

    myInit();

    glutMainLoop();              // go into a perpetual loop
}


/* C++ code segment to generate random numbers:

#include <ctime>

...

srand((unsigned)time(0)); 
int randomInt = rand()%50 + 1; 
float randomFloat = (float)rand()/RAND_MAX; 
cout << "Random Integer between 1 and 50 = " << randomInt << endl; 
cout << "Random Float between 0 and 1 = " << randomFloat << endl;
*/
