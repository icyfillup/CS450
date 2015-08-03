#if !defined(BALL_H)
#include "settings.h"

class Ball
{
public:
    Ball();
    Ball(GLfloatPoint2D pos);
    void resetBall(void);
    void setColor3f(GLfloatColor3f&);
    void setRandomVecterSpeed2f(GLfloatPoint2D&);
    
    void toggleMovement(void);
    inline void toggleFill(void){fillToggle = !fillToggle;}

    inline void increaseRadius(void){radius += 0.02f;}
    inline void decreaseRadius(void){radius = ((radius - 0.02f) > 0) ? radius - 0.02f  : 0.0f;}
    void increaseSpeed(void);
    void decreaseSpeed(void);
    
    inline void setSpeed(GLfloatPoint2D newSpeed){ballSpeed = newSpeed;}
    
    inline float getRadius(void){return radius;}
    void update(void);
    void collidedWith(Ball&);
    inline bool hasCollided(Ball& other){return hasCollided(other.getPosition(), other.getRadius());}
    bool hasCollided(GLfloatPoint2D&, float);

    inline bool hasBallStop(void){return stopBall;}
    inline bool isFill(void){return fillToggle;}
    inline GLfloatPoint2D getPosition(void){return ballPosition;}
    inline GLfloatPoint2D getSpeed(void){return ballSpeed;}
    inline GLfloatColor3f getColor(void){return ballColor;}

    inline void setMovement(void){stopBall = !stopBall;}
    
private:
    GLfloatPoint2D ballPosition;
    GLfloatColor3f ballColor;
    GLfloatPoint2D ballSpeed;

    float speedScalar;
    
    float radius;

    bool fillToggle;
    bool stopBall;

};


#define BALL_H
#endif
