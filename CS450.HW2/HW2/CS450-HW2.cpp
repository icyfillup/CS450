#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <cmath>
#include <iostream>


#include "CS450-HW2.h"

//platform
GLfloatPoint3f platform_pos;
GLfloatPoint3f platform_dim;
float platform_size;

//shoulder joint
GLfloatPoint3f shoulder_joint_pos;
float shoulder_joint_radius;
float shoulder_joint_rotate_y;
float shoulder_joint_rotate_x;

//upper arm
GLfloatPoint3f upper_arm_pos;
float upper_arm_height;
float upper_arm_radius;

//elbow joint
GLfloatPoint3f elbow_joint_pos;
float elbow_joint_radius;
float elbow_joint_rotate_x;

//lower arm
GLfloatPoint3f lower_arm_pos;
float lower_arm_height;
float lower_arm_radius;

//wrist joint
GLfloatPoint3f wrist_joint_pos;
float wrist_joint_radius;
float wrist_joint_rotate_x;

//hand
GLfloatPoint3f hand_pos;
GLfloatPoint3f hand_dim;
float hand_size;

//fingers - knuckles
GLfloatPoint3f knuckle_joint_pos[4];
float knuckle_joint_rotate_x[4];
float knuckle_joint_radius;

//fingers - upper finger
GLfloatPoint3f upper_finger_pos[4];
float upper_finger_radius;
float upper_finger_height;

//fingers - middle knuckles
GLfloatPoint3f middle_knuckle_joint_pos[4];
float middle_knuckle_joint_rotate_x[4];
float middle_knuckle_joint_radius;

//fingers - lower finger
GLfloatPoint3f lower_finger_pos[4];
float lower_finger_radius;
float lower_finger_height;

//finger nails
GLfloatPoint3f fingerNail_pos[4];
float fingerNail_radius;


void myInit(int shadingChoice, int colorChoice)
{
    //platform
    platform_pos = GLfloatPoint3f{0, 0, 0};
    platform_dim = GLfloatPoint3f{0.65, 0.115f, 0.65};
    platform_size = 1;

    //shoulder joint
    shoulder_joint_pos = GLfloatPoint3f{0, platform_size * platform_dim.height, 0};
    shoulder_joint_radius = 0.175f;
    shoulder_joint_rotate_y = 0.0f;
    shoulder_joint_rotate_x = 0.0f;

    //upper arm
    upper_arm_pos = GLfloatPoint3f{0, 0, 0};
    upper_arm_height = 1.75f;
    upper_arm_radius = shoulder_joint_radius - 0.03f;

    //elbow joint
    elbow_joint_pos = GLfloatPoint3f{0, 0, upper_arm_height};
    elbow_joint_radius = shoulder_joint_radius;
    elbow_joint_rotate_x = 0.0f;

    //lower arm
    lower_arm_pos = GLfloatPoint3f{0, 0, 0};
    lower_arm_height = 1.5f;
    lower_arm_radius = upper_arm_radius;

    //wrist joint
    wrist_joint_pos = GLfloatPoint3f{0, 0, lower_arm_height};
    wrist_joint_radius = lower_arm_radius;
    wrist_joint_rotate_x = 0.0f;

    //hand
    hand_pos = GLfloatPoint3f{0, 0, 0.75/2};
    hand_dim = GLfloatPoint3f{0.5, wrist_joint_radius, 0.75};
    hand_size = 1;

    //fingers - knuckles
    knuckle_joint_radius = (hand_dim.width / 2) * 0.25;
    for(int i = 0; i < 4; i++)
    {
        knuckle_joint_pos[i] = GLfloatPoint3f{(hand_dim.width / 2) * (0.75 - (0.50 * i)), 0, (hand_dim.length / 2) * 0.75};
        knuckle_joint_rotate_x[i] = 0.0f;
    }

    //fingers - upper finger
    upper_finger_radius = knuckle_joint_radius * 0.8;
    upper_finger_height = hand_dim.length / 2;
    for(int i = 0; i < 4; i++)
    {
        upper_finger_pos[i] = GLfloatPoint3f{0, 0, 0};
    }
    
    //fingers - middle knuckles
    middle_knuckle_joint_radius = (hand_dim.width / 2) * 0.25;
    for(int i = 0; i < 4; i++)
    {
        middle_knuckle_joint_pos[i] = GLfloatPoint3f{0, 0, upper_finger_height};
        middle_knuckle_joint_rotate_x[i] = 0.0f;
    }

    //fingers - lower finger
    lower_finger_radius = upper_finger_radius;
    lower_finger_height = hand_dim.length / 2;
    for(int i = 0; i < 4; i++)
    {
        lower_finger_pos[i] = GLfloatPoint3f{0, 0, 0};
    }

    //fingernails
    fingerNail_radius = middle_knuckle_joint_radius;
    for(int i = 0; i < 4; i++)
    {
        fingerNail_pos[i] = GLfloatPoint3f{0, 0, lower_finger_height};
    }

    
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

void drawPlatform()
{
    glColor3f(0.0f, 1.0f, 0.0f); // earth is green
    glTranslatef(platform_pos.x, platform_pos.y, platform_pos.z);

    glPushMatrix();
    glScalef(platform_dim.width, platform_dim.height, platform_dim.length);
    glutSolidCube(platform_size);
    glPopMatrix();
}

void drawShoulderJoint()
{
    glColor3f(0.0f, 0.0f, 1.0f);
    glRotatef(shoulder_joint_rotate_y, 0, 1, 0);
    glTranslatef(shoulder_joint_pos.x, shoulder_joint_pos.y, shoulder_joint_pos.z);
    glRotatef(shoulder_joint_rotate_x, 1, 0, 0);
    
    glPushMatrix();
    glutSolidSphere(shoulder_joint_radius, 20, 8);
    glPopMatrix();    
}

void drawUpperArm()
{
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(upper_arm_pos.x, upper_arm_pos.y, upper_arm_pos.z);

    GLUquadricObj *qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluCylinder(qobj, upper_arm_radius, upper_arm_radius, upper_arm_height, 20, 10);
}


void drawElbowJoint()
{
    glColor3f(1.0f, 1.0f, 0.0f);
    glTranslatef(elbow_joint_pos.x, elbow_joint_pos.y, elbow_joint_pos.z);
    glRotatef(elbow_joint_rotate_x, 1, 0, 0);
    glutSolidSphere(elbow_joint_radius, 20, 8);
}

void drawLowerArm()
{
    glColor3f(1.0f, 0.0f, 1.0f);
    glTranslatef(lower_arm_pos.x, lower_arm_pos.y, lower_arm_pos.z);

    GLUquadricObj *qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluCylinder(qobj, lower_arm_radius, lower_arm_radius, lower_arm_height, 20, 10);
}


void drawWristJoint()
{
    glColor3f(0.0f, 1.0f, 1.0f);
    glTranslatef(wrist_joint_pos.x, wrist_joint_pos.y, wrist_joint_pos.z);
    glRotatef(wrist_joint_rotate_x, 1, 0, 0);
    glutSolidSphere(wrist_joint_radius, 20, 8);
}

void drawHand()
{
    glColor3f(1.0f, 1.0f, 1.0f); // earth is green
    glTranslatef(hand_pos.x, hand_pos.y, hand_pos.z);

    glPushMatrix();
    glScalef(hand_dim.width, hand_dim.height, hand_dim.length);
    glutSolidCube(hand_size);
    glPopMatrix();
}

void drawFingers()
{
    for(int i = 0; i < 4; i++) 
    {
        glColor3f(0.25f, 0.75f, 0.5f);
        glPushMatrix();

        glTranslatef(knuckle_joint_pos[i].x, knuckle_joint_pos[i].y, knuckle_joint_pos[i].z);
        glRotatef(knuckle_joint_rotate_x[i], 1, 0, 0);
        glutSolidSphere(knuckle_joint_radius, 20, 8);
        
        glTranslatef(upper_finger_pos[i].x, upper_finger_pos[i].y, upper_finger_pos[i].z);
        GLUquadricObj *qobj = gluNewQuadric();
        gluQuadricDrawStyle(qobj, GLU_FILL);
        gluCylinder(qobj, upper_finger_radius, upper_finger_radius, upper_finger_height, 20, 10);        

        
        glTranslatef(middle_knuckle_joint_pos[i].x, middle_knuckle_joint_pos[i].y, middle_knuckle_joint_pos[i].z);
        glRotatef(middle_knuckle_joint_rotate_x[i], 1, 0, 0);
        glutSolidSphere(middle_knuckle_joint_radius, 20, 8);
        
        glTranslatef(lower_finger_pos[i].x, lower_finger_pos[i].y, lower_finger_pos[i].z);
        qobj = gluNewQuadric();
        gluQuadricDrawStyle(qobj, GLU_FILL);
        gluCylinder(qobj, lower_finger_radius, lower_finger_radius, lower_finger_height, 20, 10);        

        
        glTranslatef(fingerNail_pos[i].x, fingerNail_pos[i].y, fingerNail_pos[i].z);
        glutSolidSphere(fingerNail_radius, 20, 8);
        
        glPopMatrix();
    }
}

void DEBUG_drawLine()
{
    //glTranslatef(0, 0, 0);
    glRotatef(270, 1, 0, 0);
    GLUquadricObj *qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluCylinder(qobj, 0.01, 0.01, 50, 20, 10);
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displaySolarSystem()
{
    Sleep(1);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
    glMatrixMode(GL_MODELVIEW); // position and aim the camera
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);

    drawAxes();

    drawPlatform();
    drawShoulderJoint();
    drawUpperArm();
    drawElbowJoint();
    drawLowerArm();
    drawWristJoint();
    drawHand();
    drawFingers();
    
    glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'v':
            view++;
            view %= 3;
            if(view == 0)
            {
                eyex = 25;
                eyey = 25;
                eyez = 25;
            }
            else if(view == 1)
            {
                eyex = 25;
                eyey = 0;
                eyez = 0;
            }
            else if(view == 2)
            {
                eyex = 0;
                eyey = 25;
                eyez = 25;
            }
            break;
        case 'i':
            shoulder_joint_rotate_x -= 10.0f;
            if(shoulder_joint_rotate_x < -90){shoulder_joint_rotate_x = -90;}
            break;
        case 'I':
            shoulder_joint_rotate_x += 10.0f;
            if(shoulder_joint_rotate_x > 180){shoulder_joint_rotate_x = 180;}
            break;
        case 'j':
            elbow_joint_rotate_x -= 10.0f;
            if(elbow_joint_rotate_x < -140){elbow_joint_rotate_x = -140;}
            break;
        case 'J':
            elbow_joint_rotate_x += 10.0f;
            if(elbow_joint_rotate_x > 0){elbow_joint_rotate_x = 0;}
            break;
        case 'r':
            shoulder_joint_rotate_y -= 10.0f;
            break;
        case 'R':
            shoulder_joint_rotate_y += 10.0f;
            break;
        case 'n':
            for(int i = 0; i < 4; i++)
            {
                knuckle_joint_rotate_x[i] -= 10.0f;
                if(knuckle_joint_rotate_x[i] < -90){knuckle_joint_rotate_x[i] = -90;}
            }
            break;
        case 'N':
            for(int i = 0; i < 4; i++)
            {
                knuckle_joint_rotate_x[i] += 10.0f;
                if(knuckle_joint_rotate_x[i] > 0){knuckle_joint_rotate_x[i] = 0;}
            }
            break;
        case 'm':
            for(int i = 0; i < 4; i++)
            {
                middle_knuckle_joint_rotate_x[i] -= 10.0f;
                if(middle_knuckle_joint_rotate_x[i] < -90){middle_knuckle_joint_rotate_x[i] = -90;}
            }
            break;
        case 'M':
            for(int i = 0; i < 4; i++)
            {
                middle_knuckle_joint_rotate_x[i] += 10.0f;
                if(middle_knuckle_joint_rotate_x[i] > 0){middle_knuckle_joint_rotate_x[i] = 0;}
            }
            break;
        case 'q':
        case 'Q':
            exit(1);
            break;
            
        case 'o':
            break;
        case 'u':
            break;
        case 'c':
            break;
        case 'a':
            break;
        case 's':
            break;
        case 27:
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
            break;
        case GLUT_KEY_DOWN:
            break;
    }
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
    
    glutMainLoop();

    return(0);
}
