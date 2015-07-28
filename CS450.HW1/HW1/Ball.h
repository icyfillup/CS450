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
    inline void increaseSpeed(void){speedScalar += 0.02f;}
    inline void decreaseSpeed(void){speedScalar = ((speedScalar - 0.02f) > 0) ? speedScalar - 0.02f  : 0.0f;}

    inline float getRadius(void){return radius;}
    void update(void);

    inline bool isFill(void){return fillToggle;}
    inline GLfloatPoint2D getPosition(void){return ballPosition;}
    inline GLfloatColor3f getColor(void){return ballColor;}
    
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
