/*
Benjamin Isani Evans
302396593 :)

*/
#include <windows.h>  //suitable when using Windows 95/98/NT
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <iostream>
#include "hw2.h"
#include "robot_arm.h"
bool showAxis = true;
bool rotateCam = false;
float t = 0;
RobotArm arm = RobotArm();

void myIdle(){

	if (rotateCam)t += .0001;
	arm.updateAnimation();
	glutPostRedisplay();
}

void myInit(int shadingChoice, int colorChoice)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);

	//set rot speeds 
	rotateEarth  = 0;
	rotateMoon = 0;
	rotateSun = 0;
	rotateMars = 0;

	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);

	if(shadingChoice == 0) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	}
	else if(shadingChoice == 1) {
		glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
		glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	}

	if(colorChoice == 1) {
		glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glEnable(GL_COLOR_MATERIAL);
	}


	glClearColor(1.0f, 1.0f, 1.0f,0.0f);  // background is white

	glMatrixMode(GL_PROJECTION); // set the view volume shape
	glLoadIdentity();
	glOrtho(-3.5*worldWidth/worldHeight, 3.5*worldWidth/worldHeight, -3.5, 3.5, 0.1, 100);
}


void drawAxes()
{
	glBegin(GL_LINES);
		//x
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(0,0,0);
		glVertex3f(100,0,0);
		//y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(0,0,0);
		glVertex3f(0,100,0);
		//z
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(0,0,0);
		glVertex3f(0,0,100);
	glEnd();
}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< displayWire >>>>>>>>>>>>>>>>>>>>>>
void displayArm()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     // clear the screen
	glMatrixMode(GL_MODELVIEW); // position and aim the camera
	glLoadIdentity();
	float camRadiusx = 20;
	float camRadiusz = 35;
	eyex = (2 * camRadiusx)*cos(2 * PI*t);
	eyez = (2 * camRadiusz)*sin(2 * PI*t);
	Position pos = arm.getPosition();
	gluLookAt(eyex, eyey, eyez, pos.x, pos.y, pos.z, 0.0, 1.0, 0.0);
	//gluLookAt(eyex, eyey, eyez, lookx, looky, lookz, 0.0, 1.0, 0.0);
	
	if(showAxis)drawAxes();
	arm.draw();
	glutSwapBuffers();
}

void myKeyboard(unsigned char key, int x, int y)
{
	switch(key) {
		case 'v':
			view++;
			view %= 3;
			if(view == 0) {
				eyex=25;
				eyey=25;
				eyez=25;
			}
			else if(view == 1) {
				eyex=25;
				eyey=0;
				eyez=0;
			}
			else if(view == 2) {
				eyex=0;
				eyey=25;
				eyez=25;
			}
			break;

		case 'N':
			if (!arm.isActivated())return;
			arm.liftHand(-ROTATE_RATE);
			break;
		case 'n':
			if (!arm.isActivated())return;
			arm.liftHand(ROTATE_RATE);
			break;
		case 's':
			rotateCam = !rotateCam;
			break;
		case 'u':
			arm.setWireFrame(!arm.isWireFrame());
			break;
		case 'o':
			arm.setActive(!arm.isActivated());
			break;
		case 'J':
			if (!arm.isActivated())return;
			arm.raiseLowerArm(-ROTATE_RATE);
			break;
		case 'j':
			if (!arm.isActivated())return;
			arm.raiseLowerArm(ROTATE_RATE);
			break;
		case 'I':
			if (!arm.isActivated())return;
			arm.raiseUpperArm(-ROTATE_RATE);
			break;
		case 'i':
			if (!arm.isActivated())return;
			arm.raiseUpperArm(ROTATE_RATE);
			break;
		case 'r':
			if (!arm.isActivated())return;
			arm.rotateShoulder(-ROTATE_RATE);
			break;
		case 'R':
			if (!arm.isActivated())return;
			arm.rotateShoulder(ROTATE_RATE);
			break;
		case'c':
			showAxis = !showAxis;
			break;

		case 'm':
			//open hand 
			arm.openHand();
			break;

		case 'M':
			//close hand 
			arm.closeHand();
			break;
		case 27:
			arm.reset();
			showAxis = true;
			rotateCam = false;
			t = 0;
			break;
		case 'a':
			arm.animate();
			break;
		case 'q':
		case 'Q':
			exit(1);
			break;
		default:
			break;
	}

	glutPostRedisplay();

}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	if (!arm.isActivated())return;
	float dz = .5;
	switch (theKey) {
	case GLUT_KEY_UP:
		// move the object to the top in a small amount
		arm.incrementZ(dz);
		break;
	case GLUT_KEY_DOWN:
		arm.incrementZ(-1 * dz);
		break;
	case GLUT_KEY_LEFT:
		
		break;
	case GLUT_KEY_RIGHT:
		
		break;
	default:
		break;		      // do nothing
	}

	glutPostRedisplay(); // implicitly call myDisplay
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);          // initialize the toolkit
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // set display mode
	glutInitWindowSize(screenWidth, screenHeight); // set window size
	glutInitWindowPosition(100, 100); // set window position on screen
	glutCreateWindow("Robot Arm"); // open the screen window
	myInit(1, 1);
	glutDisplayFunc(displayArm);
	glutKeyboardFunc(myKeyboard);
	glutIdleFunc(myIdle);
	glutSpecialFunc(mySpecialKeyboard);
	glutMainLoop();
	return( 0 );
}
