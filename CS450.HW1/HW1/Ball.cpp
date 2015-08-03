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
    setMovement();
    
    (stopBall) ?
        ballSpeed.x = ballSpeed.y = 0 :
        setRandomVecterSpeed2f(ballSpeed);
}

void Ball::increaseSpeed(void)
{
    speedScalar += 0.02f;

    float tempX = speedScalar * ballSpeed.x; 
    float tempY = speedScalar * ballSpeed.y;

    if(tempX > 0.0f || tempY > 0.0f)
        stopBall = false;

    #if 1
    debugPrint(tempX);
    debugPrint(tempY);
    debugPrint(stopBall);
    debugPrint("");
    #endif
}
    

void Ball::decreaseSpeed(void)
{
    speedScalar = ((speedScalar - 0.02f) > 0) ? speedScalar - 0.02f  : 0.0f;

    float tempX = speedScalar * ballSpeed.x; 
    float tempY = speedScalar * ballSpeed.y;

    if(tempX <= 0.0f && tempY <= 0.0f)
        stopBall = true;

    #if 1
    debugPrint(tempX);
    debugPrint(tempY);
    debugPrint(stopBall);
    debugPrint("");
    #endif
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
        GLfloatPoint2D n{-1, 0};
        float magOfSpeed = sqrt((ballSpeed.x * ballSpeed.x) + (ballSpeed.y * ballSpeed.y));
        GLfloatPoint2D a{(ballSpeed.x / magOfSpeed), (ballSpeed.y / magOfSpeed)};

        float dotA_N = 2 * ((a.x * n.x) + (a.y * n.y));
        GLfloatPoint2D reflect = {a.x - (dotA_N * n.x), a.y - (dotA_N * n.y)};
        setSpeed(reflect);

        tempX = (WORLD_WIDTH / 2) - radius;
    }
    else if((tempX - radius) < (-WORLD_WIDTH / 2)) // hit the left side of the world//window 
    {
        GLfloatPoint2D n{1, 0};
        float magOfSpeed = sqrt((ballSpeed.x * ballSpeed.x) + (ballSpeed.y * ballSpeed.y));
        GLfloatPoint2D a{(ballSpeed.x / magOfSpeed), (ballSpeed.y / magOfSpeed)};

        float dotA_N = 2 * ((a.x * n.x) + (a.y * n.y));
        GLfloatPoint2D reflect = {a.x - (dotA_N * n.x), a.y - (dotA_N * n.y)};
        setSpeed(reflect);

        tempX = (-WORLD_WIDTH / 2) + radius;
    }
    
    if((tempY + radius) > (WORLD_HEIGHT / 2)) // hit the top side of the world/window
    {
        GLfloatPoint2D n{0, -1};
        float magOfSpeed = sqrt((ballSpeed.x * ballSpeed.x) + (ballSpeed.y * ballSpeed.y));
        GLfloatPoint2D a{(ballSpeed.x / magOfSpeed), (ballSpeed.y / magOfSpeed)};

        float dotA_N = 2 * ((a.x * n.x) + (a.y * n.y));
        GLfloatPoint2D reflect = {a.x - (dotA_N * n.x), a.y - (dotA_N * n.y)};
        setSpeed(reflect);
        
        tempY = (WORLD_HEIGHT / 2) - radius;
    }
    else if((tempY - radius) < (-WORLD_HEIGHT / 2)) // hit the bottom side of the world/window
    {
        GLfloatPoint2D n{0, 1};
        float magOfSpeed = sqrt((ballSpeed.x * ballSpeed.x) + (ballSpeed.y * ballSpeed.y));
        GLfloatPoint2D a{(ballSpeed.x / magOfSpeed), (ballSpeed.y / magOfSpeed)};

        float dotA_N = 2 * ((a.x * n.x) + (a.y * n.y));
        GLfloatPoint2D reflect = {a.x - (dotA_N * n.x), a.y - (dotA_N * n.y)};
        setSpeed(reflect);
        
        tempY = (-WORLD_WIDTH / 2) + radius;
    }
    
    ballPosition.x = tempX;
    ballPosition.y = tempY;
}

void Ball::collidedWith(Ball& other)
{
    if(this->stopBall && other.hasBallStop())
        return;
    
    if(this->hasCollided(other))
    {
        if(this->stopBall)
            this->toggleMovement();
        else
        {
            this->ballSpeed.x = -this->ballSpeed.x;
            this->ballSpeed.y = -this->ballSpeed.y;
        }

        if(other.hasBallStop())
            other.toggleMovement();
        else
            other.setSpeed(GLfloatPoint2D{-other.getSpeed().x, -other.getSpeed().y});
    
        this->update();
        other.update();
    }
}

bool Ball::hasCollided(GLfloatPoint2D& pos, float range)
{
    GLfloatPoint2D distance{pos.x - this->ballPosition.x, pos.y - this->ballPosition.y};

    float actualDistFromPts = (distance.x * distance.x) + (distance.y * distance.y);
    float detectingDistFromPts = (range + this->radius) * (range + this->radius);

    return actualDistFromPts <= detectingDistFromPts;
}
