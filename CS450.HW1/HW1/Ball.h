#if !defined(BALL_H)
#include "settings.h"

class Ball
{
public:
    Ball();
    void resetBall(void);
    void setColor3f(GLfloatColor3f&);
    void setRandomVecterSpeed2f(GLfloatPoint2D&);
    inline void toggleMovement(){stopBall = !stopBall;}
    inline void toggleFill(){fillToggle = !fillToggle;}
    inline void increaseRadius(){radius += 0.02f;}
    inline void decreaseRadius(){radius = ((radius - 0.02f) > 0) ? radius - 0.02f  : 0.0f;}
    inline void increaseSpeed(){speedScalar += 0.02f;}
    inline void decreaseSpeed(){speedScalar = ((speedScalar - 0.02f) > 0) ? speedScalar - 0.02f  : 0.0f;}
    inline float getRadius(){return radius;}
    void update(void);

    inline bool isFill(){return fillToggle;}
    inline GLfloatPoint2D getPosition(){return ballPosition;}
    inline GLfloatColor3f getColor(){return ballColor;}
    
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
