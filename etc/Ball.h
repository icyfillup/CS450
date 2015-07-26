#if !defined(BALL_H)


class Ball
{
private:
    GLfloatPoint2D ballPosition;
    GLfloatColor3f ballColor;
    GLfloatPoint2D ballSpeed;

    float speedScalar;

    float radius;

    bool fillToggle;
    bool stopBall;

public:
    Ball(void);
    void resetBall(void);
    void setColor3f(GLfloatColor3f&);
    void setRandomVectorSpeed2f(GLfloatPoint2D&);

    void toggleMovement(void);
    void toggleFill(void);

    void decreaseRadius(void);
    void increaseRadius(void);

    void decreaseSpeed(void);
    void increaseSpeed(void);
    
    void update(void);
    void renderBall(void);
    
};

#define BALL_H
#endif
