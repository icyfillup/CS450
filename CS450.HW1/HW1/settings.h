#ifndef SETTING_H
#define SETTING_H

#define SCREEN_WIDTH 500
#define SCREEN_HEIGHT 500

#define WORLD_WIDTH 100
#define WORLD_HEIGHT 100

#define PI 3.141592f

#define DEBUG 0
#define debugPrint(word) (std::cout << (word) << std::endl)


// world corners: left, right, bottom, top
float lt, rt, bt, tp;

struct GLfloatPoint2D
{
    GLfloat x, y;
};

struct GLfloatColor3f
{
    GLfloat r, g, b;
};

#endif
