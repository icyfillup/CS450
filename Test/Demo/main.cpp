//Computer Graphics Lab : Drawing an object and changing world view

#include <windows.h>
#include <math.h>	// included for random number generation
#include <gl/Gl.h>
#include <gl/glut.h>
#include <iostream>

const int screenWidth = 500;
const int screenHeight = 500;
const float pi = 3.1415;
float pointSize = 4.0;
int radius, height, width;
float centerx = 0;
float centery = 0;
bool drawCircle, loop;
void setWindow(float left, float right, float bottom, float top);
// left, right, bottom, top
float lt, rt, bt, tp;

void myInit(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
	glColor3f(0.0f, 0.0f, 0.0f);   // drawing color is black
	glPointSize(pointSize);
	glMatrixMode(GL_PROJECTION); 	   // set "camera shape"
	glLoadIdentity();
	lt = 0;
	rt = screenWidth;
	tp = screenHeight;
	bt = 0;
	centerx = screenWidth / 2;
	centery = screenHeight / 2;
	loop = true;
	/*lt = -10;
	rt = 10;
	bt = -10;
	tp = 10;*/
	//	gluOrtho2D(lt, rt, bt, tp);	// set the world window
	gluOrtho2D(0.0, screenWidth, 0.0, screenHeight);
}
void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
{
	float zoomfactor = 2;
	switch(theKey)
	{
		case 'z':
			// zoom-in
			std::cout << "zoom-in" << std::endl;
			lt += 1;
			rt -= 1;
			tp -= 1;
			bt += 1;
			break;
		case 'Z':
			// zoom-out
			std::cout << "zoom-out" << std::endl;
			lt -= 1;
			rt += 1;
			tp += 1;
			bt -= 1;
			break;

		case 'T':
		case 't':
			loop = !loop;
			break;

		case '+':
			radius += 5;
			height += 5;
			width += 5;
			break;

		case '-':
			radius -= 5;
			height -= 5;
			width -= 5;
			break;

		case 'b':
		case 'B':
			pointSize += 2.0f;
			break;
		default:
			break;		      // do nothing
	}
	glutPostRedisplay(); // implicitly call myDisplay
}

void mySpecialKeyboard(int theKey, int mouseX, int mouseY)
{
	switch(theKey)
	{
		case GLUT_KEY_UP:
			// move the object to the top in a small amount
			tp -= 1;
			bt -= 1;
			break;
		case GLUT_KEY_DOWN:
			// move the object to the bottom in a small amount
			tp += 1;
			bt += 1;
			break;
		case GLUT_KEY_LEFT:
			// move the object to the left in a small amount
			lt += 1;
			rt += 1;
			break;
		case GLUT_KEY_RIGHT:
			// move the object to the right in a small amount
			lt -= 1;
			rt -= 1;
			break;
		default:
			break;		      // do nothing
	}

	glutPostRedisplay(); // implicitly call myDisplay
}

//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);     // clear the screen
	setWindow(lt, rt, bt, tp);
	if(loop)glBegin(GL_LINE_LOOP);
	else glBegin(GL_POINTS);
	glPointSize(pointSize);
	//	glBegin(GL_POINTS);
	// draw a shape

	if(drawCircle)
	{
		for(float t = 0; t < 1; t += .001)
		{
			float x = centerx + radius*cos(2 * pi*t);
			float y = centery + radius*sin(2 * pi*t);
			glVertex2f(x, y);
		}
	}
	else
	{
		for(float t = 0; t < 1; t += .001)
		{
			float x = centerx + width*cos(2 * pi*t);
			float y = centery + height*sin(2 * pi*t);
			glVertex2f(x, y);
		}
	}

	glEnd();
	//	setWindow(lt, rt, bt, tp);
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
	std::cout << "1. Drawing a circle\n" << "2. Drawing an ellipse\n" << "Choose 1 or 2: ";
	int choice;
	std::cin >> choice;
	if(choice == 1)
	{
		drawCircle = true;
		std::cout << "Enter a radius or the circle: ";
		std::cin >> radius;

	}
	else if(choice == 2)
	{
		drawCircle = false;
		std::cout << "Enter a height: ";
		std::cin >> height;
		std::cout << "\nEnter a width: ";
		std::cin >> width;
	}
	else
	{
		std::cout << "Invalid input.. program will now exit";
		std::exit(1);
	}

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

	glutMainLoop(); 		     // go into a perpetual loop
}