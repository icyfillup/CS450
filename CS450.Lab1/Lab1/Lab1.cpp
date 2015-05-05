// Computer Graphics
#include <windows.h>
#include <math.h>   // included for random number generation
#include <gl/Gl.h>
#include <gl/glut.h>
#include <ctime>


const int screenWidth = 500;
const int screenHeight = 500;

struct GLintPoint
{
    GLint x, y;
};

GLintPoint pts[4];
int NoOfPts = 0;

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


}

void randomScreenColor(void)
{
    
    float r = (float)rand()/RAND_MAX;
    float g = (float)rand()/RAND_MAX;
    float b = (float)rand()/RAND_MAX;
    
    glClearColor(r, g, b, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glFlush();
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case 'c':
        {// change the current background color into a new one
            randomScreenColor();
        }break;
        case 'p':
            // indicate that the display function needs to draw a graph
            break;
        default:
            break;            // do nothing
    }

    glutPostRedisplay(); // implicitly call myDisplay
}


//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    // draw either a polygon(rectangle) using the points in pts[] or a cosine graph
    // To access a point in pts[], use the syntax like pts[index].x or pts[index].y

    glFlush();
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
