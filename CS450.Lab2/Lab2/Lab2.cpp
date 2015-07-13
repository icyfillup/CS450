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

// circle properties
float radius = 5;

// ellipse properties
float E_width = 10;
float E_height = 5;

// center of the drawing
float centerX = 0;
float centerY = 0;

// toggle between circle and ellipse
bool isCircle = false, usingLine = true;


// control how fast to move the camera
float movingRate = 0.1f;

// increasing or decreasing circle or ellipse size and thickness
float scalar = 0;
float thickness = 0;

void setWindow(float left, float right, float bottom, float top);

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
}

void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case 'z':
        {// zoom-in
            std::cout << "zoom-in" << std::endl;
            lt += movingRate;
            rt += -movingRate;
            bt += movingRate;
            tp += -movingRate;
        }break;
        case 'Z':
        {// zoom-out
            std::cout << "zoom-out" << std::endl;
            lt += -movingRate;
            rt += movingRate;
            bt += -movingRate;
            tp += movingRate;
        }break;
        case 't':
        case 'T':
        {
            usingLine = !usingLine;
        }break;
        case '-':
        {
            scalar -= 0.1;
        }break;
        case '+':
        {
            scalar += 0.1;
        }break;
        case 'b':
        {
            thickness -= 2.0f;
        }break;
        case 'B':
        {
            thickness += 2.0f;
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
            tp += -movingRate;
            bt += -movingRate;
        }break;
        case GLUT_KEY_DOWN:
        {// move the object to the bottom in a small amount
            tp += movingRate;
            bt += movingRate;
        }break;
        case GLUT_KEY_LEFT:
        {// move the object to the left in a small amount
            lt += movingRate;
            rt += movingRate;
        }break;
        case GLUT_KEY_RIGHT:
        {// move the object to the right in a small amount
            lt += -movingRate;
            rt += -movingRate;
        }break;
        default:
            break;            // do nothing
    }

    glutPostRedisplay(); // implicitly call myDisplay
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
    setWindow(lt, rt, bt, tp);
    
    float x = 0;
    float y = 0;
        
    glClear(GL_COLOR_BUFFER_BIT);     // clear the screen

    glPointSize(thickness);

    if(usingLine)
        glBegin(GL_LINE_LOOP);
    else
        glBegin(GL_POINTS);
    // draw a shape

    if(isCircle)
    {
        for(float t = 0; t < 1; t += 0.01)
        {
            x = centerX + ((radius + scalar) * cos(2 * PI * t));
            y = centerY + ((radius + scalar) * sin(2 * PI * t));

            glVertex2f(x, y);
        }
    }
    else
    {
        for(float t = 0; t < 1; t += 0.01)
        {
            x = centerX + ((E_width + scalar) * cos(2 * PI * t));
            y = centerY + ((E_height + scalar) * sin(2 * PI * t));

            glVertex2f(x, y);
        }
    }
        
    glEnd();
    //glFlush();
    glutSwapBuffers();
}


//--------------- setWindow ---------------------
void setWindow(float left, float right, float bottom, float top)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(left, right, bottom, top);
}

//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char** argv)
{
    short choose = -1;
    
    do
    {
        std::cout << "1.\tDrawing a circle\n2.\tDrawing an ellipse\nChoose 1 or 2:\t" << std::endl;

        std::cin >> choose;
    }
    while(!(choose < 3 && choose > 0));

    isCircle = (choose == 1) ? true : false;



    
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
