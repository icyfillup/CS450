#include <windows.h>
#include <gl/Gl.h>
#include <gl/glut.h>
#include <vector>

#include "settings.h"
#include "Ball.h"

float lt, rt, bt, tp;

bool isMouseOnBall;
bool isMouseDown;
Ball *mouseOnBall;

std::vector<Ball> balls;

void setWindow(float left, float right, float bottom, float top);
GLfloatPoint2D getRandomPosition2f(void);
GLfloatPoint2D screenToWorldPos(GLfloatPoint2D& currentScreenPos,
                                GLfloatPoint2D& screenCornerPos,
                                GLfloatPoint2D& worldCornerPos);


void myInit(void)
{
    isMouseDown = false;
    isMouseOnBall = false;
    
    balls.push_back(Ball());
        
    lt = -WORLD_WIDTH / 2;
    rt = WORLD_WIDTH / 2;
    bt = -WORLD_HEIGHT / 2;
    tp = WORLD_HEIGHT / 2;

    glClearColor(1.0, 1.0, 1.0, 0.0);       // background color is white
    glColor3f(0.0f, 0.0f, 0.0f);         // drawing color is black
    glMatrixMode(GL_PROJECTION);       // set "camera shape"
    glLoadIdentity();
    gluOrtho2D(lt, rt, bt, tp); // set the world window
}

void myMouse(int button, int state, int x, int y)
{
    if(button != GLUT_LEFT_BUTTON) return;
    
    if(state == GLUT_DOWN)
    {
        GLfloatPoint2D worldPos = screenToWorldPos(GLfloatPoint2D{x, SCREEN_HEIGHT - y}, GLfloatPoint2D{0, 0}, GLfloatPoint2D{lt, bt});

        for(int i = 0; i < balls.size(); i++)
        {
            if(balls[i].hasCollided(worldPos, 0) && balls[i].hasBallStop())
            {
                mouseOnBall = &balls[i];
                isMouseDown = true;
                break;
            }
        }
    }
    else if(state == GLUT_UP && isMouseDown)
    {
        isMouseDown = false;
        GLfloatPoint2D lastWorldPos = screenToWorldPos(GLfloatPoint2D{x, SCREEN_HEIGHT - y}, GLfloatPoint2D{0, 0}, GLfloatPoint2D{lt, bt});

        GLfloatPoint2D newSpeed{lastWorldPos.x - mouseOnBall->getPosition().x, lastWorldPos.y - mouseOnBall->getPosition().y};

        newSpeed.x *= (2.0f / WORLD_WIDTH);
        newSpeed.y *= (2.0f / WORLD_HEIGHT);

        mouseOnBall->setSpeed(newSpeed);
        mouseOnBall->setMovement();
    }
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
            if(balls.size() < 128)
                balls.push_back(Ball(getRandomPosition2f()));
            else
                std::cout << "adding too much ball onto the window" << std::endl;
        }break;
        
        case 'r':
        {//TODO(philip): remove recently added ball. NOTE: key cannot remove first ball 
            #if DEBUG
            debugPrint("r");
            #endif

            if(balls.size() > 1)
                balls.pop_back();
                
        }break;

        case 's':
        {//TODO(philip): toggle between moving and stopping ALL balls on screen
            #if DEBUG
            debugPrint("s");
            #endif

            for(unsigned int i = 0; i < balls.size(); i++)
                balls[i].toggleMovement();
        }break;

        case 'n':
        {//TODO(philip): reset the program to the starting state
            #if DEBUG
            debugPrint("n");
            #endif

            balls.clear();
            balls.push_back(Ball());
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

            balls[0].toggleFill();
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
            balls[0].increaseRadius();
        }break;

        case GLUT_KEY_PAGE_DOWN:
        {//TODO(philip): decrement the radius of the first ball
            balls[0].decreaseRadius();
        }break;
        
        case GLUT_KEY_UP:
        {//TODO(philip): increase the speed of the first ball
            balls[0].increaseSpeed();
        }break;

        case GLUT_KEY_DOWN:
        {//TODO(philip): decrease the speed of the first ball NOTE(philip): check when speedScalar is 0
            balls[0].decreaseSpeed();
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

    for(float i = 0; i < balls.size(); i++)
    {
        (balls[i].isFill()) ? glBegin(GL_POLYGON) : glBegin(GL_LINE_LOOP);
        {
            GLfloatColor3f color = balls[i].getColor();
            glColor3f(color.r, color.g, color.b);        
        
            GLfloatPoint2D pos = balls[i].getPosition();
            for(float j = 0; j < 1; j += 0.01)
            {
       
                float x = (balls[i].getRadius() * cos(j * (2 * PI))) + pos.x;
                float y = (balls[i].getRadius() * sin(j * (2 * PI))) + pos.y;

                glVertex2f(x, y);
            }
        }
        glEnd();
    }
    //glFlush();
    glutSwapBuffers();
}

//--------------myIdle---------------------------
void myIdle(void)
{    
    for(unsigned int i = 0; i < balls.size(); i++)
        balls[i].update();

    for(int i = 0; i < balls.size() - 1; i++)
    {
        for(int j = i + 1; j < balls.size(); j++)
        {
            balls[i].collidedWith(balls[j]);
        }
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
    glutMouseFunc(myMouse);

    myInit();

    glutMainLoop();              // go into a perpetual loop
}

GLfloatPoint2D getRandomPosition2f(void)
{
    bool isPtTaken = false;
    GLfloatPoint2D pos;    
    
    do
    {
        isPtTaken = false;

        pos.x = (((float)rand() / RAND_MAX) * (WORLD_WIDTH - (2 * RADIUS))) + (RADIUS - (WORLD_WIDTH / 2));
        pos.y = (((float)rand() / RAND_MAX) * (WORLD_HEIGHT - (2 * RADIUS))) + (RADIUS - (WORLD_HEIGHT / 2));

        for(int i = 0; i < balls.size(); i++)
        {
            if(balls[i].hasCollided(pos, RADIUS))
            {
                isPtTaken = true;
                break;
            }
        }

    }
    while(isPtTaken);
    
        
    #if DEBUG
    debugPrint(pos.x);
    debugPrint(pos.y);
    debugPrint("");
    #endif

    return pos;
}

GLfloatPoint2D screenToWorldPos(GLfloatPoint2D& currentScreenPos,
                                GLfloatPoint2D& screenCornerPos,
                                GLfloatPoint2D& worldCornerPos)
{
    float x = ((WORLD_WIDTH / SCREEN_WIDTH) * (currentScreenPos.x - screenCornerPos.x)) + worldCornerPos.x;
    float y = ((WORLD_HEIGHT / SCREEN_HEIGHT) * (currentScreenPos.y - screenCornerPos.y)) + worldCornerPos.y;

    return GLfloatPoint2D{x, y};
}
