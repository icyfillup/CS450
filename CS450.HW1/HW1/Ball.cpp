#include "Ball.h"

Ball::Ball(void) : ballPosition(GLfloatPoint2D{0, 0})
{
    resetBall();
}

Ball::Ball(GLfloatPoint2D pos) : ballPosition(pos)
{
    resetBall();
}

void Ball::resetBall(void)
{
    fillToggle = true;
    stopBall = false;
 
    radius = RADIUS;
    speedScalar = 0.2f;
    
    setRandomVecterSpeed2f(ballSpeed);
    setColor3f(ballColor);
}

void Ball::setColor3f(GLfloatColor3f& color)
{
    color.r = (float)rand() / RAND_MAX;
    color.g = (float)rand() / RAND_MAX;
    color.b = (float)rand() / RAND_MAX;

    #if DEBUG
    debugPrint(color.r);
    debugPrint(color.g);
    debugPrint(color.b);
    #endif
}

void Ball::setRandomVecterSpeed2f(GLfloatPoint2D& speed)
{
    speed.x = 2 * ((float)rand() / RAND_MAX) - 1;
    speed.y = 2 * ((float)rand() / RAND_MAX) - 1;

    #if DEBUG
    debugPrint(speed.x);
    debugPrint(speed.y);
    #endif
}

void Ball::toggleMovement(void)
{
    stopBall = !stopBall;

    (stopBall) ?
        ballSpeed.x = ballSpeed.y = 0 :
        setRandomVecterSpeed2f(ballSpeed);
}

void Ball::update(void)
{
    if(stopBall) {return;}

    float tempX = ballPosition.x;
    float tempY = ballPosition.y;

    tempX += ballSpeed.x * speedScalar;
    tempY += ballSpeed.y * speedScalar;    
    
    if((tempX + radius) > (WORLD_WIDTH / 2)) // hit the right side of the world/window
    {
        ballSpeed.x *= -1;
        tempX = (WORLD_WIDTH / 2) - radius;
    }
    else if((tempX - radius) < (-WORLD_WIDTH / 2)) // hit the left side of the world//window 
    {
        ballSpeed.x *= -1;
        tempX = (-WORLD_WIDTH / 2) + radius;
    }
    
    if((tempY + radius) > (WORLD_HEIGHT / 2)) // hit the top side of the world/window
    {
        ballSpeed.y *= -1;
        tempY = (WORLD_HEIGHT / 2) - radius;
    }
    else if((tempY - radius) < (-WORLD_HEIGHT / 2)) // hit the bottom side of the world/window
    {
        ballSpeed.y *= -1;
        tempY = (-WORLD_WIDTH / 2) + radius;
    }
    
    ballPosition.x = tempX;
    ballPosition.y = tempY;
}

