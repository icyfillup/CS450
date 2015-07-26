#include "Ball.h"

Ball::Ball()
{
    resetBall();
}

void Ball::resetBall(void)
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

void Ball::setColor3f(GLfloatColor3f& color)
{
    color.r = (GLfloat)rand() / RAND_MAX;
    color.g = (GLfloat)rand() / RAND_MAX;
    color.b = (GLfloat)rand() / RAND_MAX;
}

void Ball::setRandomVecterSpeed2f(GLfloatPoint2D& speed)
{
    speed.x = 2 * ((GLfloat)rand() / RAND_MAX) - 1;
    speed.y = 2 * ((GLfloat)rand() / RAND_MAX) - 1;
}

void Ball::toggleMovement(void) {stopBall = !stopBall;}

void Ball::toggleFill(void) {fillToggle = !fillToggle;}

void Ball::decreaseSpeed(void)
{
    speedScalar = (speedScalar > 0) ? speedScalar -= 0.02f  : 0.0f;
}

void Ball::increaseSpeed(void)
{
    speedScalar += 0.02f;
}

void Ball::decreaseRadius(void)
{
    radius = (radius > 0) ? radius -= 0.02f  : 0.0f;            
}

void Ball::increaseRadius(void)
{
    radius += 0.02f;
}


void Ball::update(void)
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

}

void Ball::renderBall(void)
{    
    (fillToggle) ? glBegin(GL_POLYGON) : glBegin(GL_LINE_LOOP);
    {
        glColor3f(ballColor.r, ballColor.g, ballColor.b);
  
        for(float i = 0; i < 1; i += 0.01)
        {
            float x = (radius * cos(i * (2 * PI))) + ballPosition.x;
            float y = (radius * sin(i * (2 * PI))) + ballPosition.y;

            glVertex2f(x, y);
        }
        
    }
    glEnd();
}
