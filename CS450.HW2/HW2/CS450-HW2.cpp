#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>


#include "CS450-HW2.h"
#include "myMath.h"
#include "Arm.cpp"

float time;
bool isCoorOn;
bool camMovement;
Arm arm;



void moveCam(void)
{
    time += 0.001f;
    if(time > 1){time = 0;}
    
    eyex = lookx + (length * sin(2 * PI * time));
    eyez = lookz + (length * cos(2 * PI * time));
}

void start()
{
    time = 0;
    camMovement = false;
    isCoorOn = true;
    initArm(arm);

    v3f arm_location = arm.platform.pos + arm.shoulder_joint.pos;
    lookx = arm_location.x;
    looky = arm_location.y;
    lookz = arm_location.z;

    eyey = eyey + looky;
    moveCam();
}

void myInit(int shadingChoice, int colorChoice)
{
    start();
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

    if(shadingChoice == 0)
    {
        glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    }
    else if(shadingChoice == 1)
    {
        glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    }

    if(colorChoice == 1)
    {
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
        glEnable(GL_COLOR_MATERIAL);
    }

    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);  // background is white
    
    glMatrixMode(GL_PROJECTION); // set the view volume shape
    glLoadIdentity();
    glOrtho(-3.5*worldWidth / worldHeight, 3.5*worldWidth / worldHeight, -3.5, 3.5, 0.1, 100);
}

void drawAxes()
{
    glBegin(GL_LINES);
    //x
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);
    //y
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);
    //z
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);
    glEnd();
}

void DEBUG_drawLine()
{
    glTranslatef(arm.thumb_knuckle_joint.pos.x, arm.thumb_knuckle_joint.pos.y, arm.thumb_knuckle_joint.pos.z);
    glRotatef(270, 1, 0, 0);
    GLUquadricObj *qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluCylinder(qobj, 0.01, 0.01, 50, 20, 10);
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolarSystem()
{
    Sleep(1);

    v3f arm_location = arm.platform.pos + arm.shoulder_joint.pos;
    lookx = arm_location.x;
    looky = arm_location.y;
    lookz = arm_location.z;
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);


    if(camMovement){moveCam();}    
    if(isCoorOn){drawAxes();}

    drawArm(arm);
    //DEBUG_drawLine();
    
    glutSwapBuffers();
}

void drawAnimation()
{
    
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'i':
            rotateShoulder(arm, -10.0f, 0);
            break;
        case 'I':
            rotateShoulder(arm, 10.0f, 0);
            break;
        case 'j':
            rotateElbow(arm, -10.0f);
            break;
        case 'J':
            rotateElbow(arm, 10.0f);
            break;
        case 'r':
            rotateShoulder(arm, -10.0f, 1);
            break;
        case 'R':
            rotateShoulder(arm, 10.0f, 1);
            break;
        case 'n':
            rotateKnuckle(arm, -10.0f);
            break;
        case 'N':
            rotateKnuckle(arm, 10.0f);
            break;
        case 'm':
            rotateMiddleKnuckle(arm, -10);
            break;
        case 'M':
            rotateMiddleKnuckle(arm, 10);
            break;
        case 'q':
        case 'Q':
            exit(1);
            break;
            
        case 'o':
            toggleOnOff(arm);
            break;
        case 'u':
            toggleSolidWired(arm);
            break;
        case 'c':
            isCoorOn = !isCoorOn;
            break;
        case 'a':
            if(arm.animationComplete) initArm(arm);
            toggleAnimation(arm);
            break;
        case 's':
            camMovement = !camMovement;
            break;
        case 27:
            start();
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
    switch(theKey)
    {
        case GLUT_KEY_UP:
            moveArm(arm, 0.25);
            break;

        case GLUT_KEY_DOWN:
            moveArm(arm, -0.25);
            break;            
    }

    glutPostRedisplay();
}

void myIdle()
{
    if(arm.isAnimating)
    {drawAnimation(arm);}
    
    glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{    
    glutInit(&argc, argv);          // initialize the toolkit
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
    glutInitWindowSize(screenWidth, screenHeight); // set window size
    glutInitWindowPosition(100, 100); // set window position on screen
    glutCreateWindow("Inner Solar System"); // open the screen window

    int shadingChoice = 0;
    int colorChoice = 0;
    std::cout << "Enter Shading Choice (0 for Diffuse, 1 for Specular):\n";
    std::cin >> shadingChoice;

    std::cout << "Enter Color Option (0 for No Color, 1 for Color):\n";
    std::cin >> colorChoice;

    myInit(shadingChoice, colorChoice);

    glutDisplayFunc(displaySolarSystem);
    glutKeyboardFunc(myKeyboard);
    glutSpecialFunc(mySpecialKeyboard);
    glutIdleFunc(myIdle);

    
    glutMainLoop();

    return(0);
}
