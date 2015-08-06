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
	glVertex3fv(octahedron[a].vertices);
	glVertex3fv(octahedron[b].vertices);
	glVertex3fv(octahedron[c].vertices);
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
			// do what you need to do for up-scale here

			break;
		case '-':
			// do what you need to do for down-scale  here

			break;
		case 'r':
			// do what you need to do for rotation here

			break;
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
			// do what you need to do for translation in one direction here

			break;
		case GLUT_KEY_DOWN:
			// do what you need to do for translation in the opposite direction of UP KEY here

			break;
		case GLUT_KEY_LEFT:
			// do what you need to do for translation in one direction here

			break;
		case GLUT_KEY_RIGHT:
			// do what you need to do for translation in the opposite direction of LEFT KEY here

			break;
		case GLUT_KEY_HOME:
			// do what you need to do for initialization here

			break;
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



	// draw octahedron
	drawOctahedron();
	glFlush();		   // send all output to display

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
	glutMainLoop(); 		     // go into a perpetual loop
}
